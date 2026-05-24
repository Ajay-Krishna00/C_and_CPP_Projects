# curl Request Lifecycle (Step-by-step)

"When I run this curl command, what EXACTLY happens step-by-step, and what does the data look like at every stage?"

Let's trace the entire lifecycle.

## Your command

```bash
curl -X POST "https://c-and-cpp-projects.vercel.app/ask" \
  -H "Content-Type: application/json" \
  -d '{"code":"int main(){return 0;}","question":"What does this do?"}'
```

## Big picture flow

```mermaid
flowchart TD
  A[Your Terminal] --> B[Internet]
  B --> C[Vercel Serverless Function]
  C --> D[Your handler(req, res)]
  D --> E[Gemini API]
  E --> F[Gemini Response]
  F --> G[Your API formats response]
  G --> H[curl prints final JSON]
```

Now let's zoom into every stage.

## Step 1 - You run curl

You type:

```bash
curl -X POST ...
```

`curl` is an HTTP client. Its job is to:

- Create an HTTP request
- Send it over the internet
- Display the response

## Step 2 - curl builds the raw HTTP request

Internally, `curl` converts your command into something like:

```http
POST /ask HTTP/1.1
Host: c-and-cpp-projects.vercel.app
Content-Type: application/json
Content-Length: 74

{"code":"int main(){return 0;}","question":"What does this do?"}
```

### Understanding the structure

**Request line**

```text
POST /ask HTTP/1.1
```

Means:

- `method = POST`
- `path = /ask`
- `protocol = HTTP/1.1`

**Headers**

```text
Content-Type: application/json
```

Tells the server: "The body is JSON."

**Body**

```json
{"code":"int main(){return 0;}","question":"What does this do?"}
```

Actual payload.

## Step 3 - DNS lookup

Your machine sees `c-and-cpp-projects.vercel.app`. It must find the actual IP address, so the OS asks DNS servers:

"What IP belongs to this domain?"

Gets something like: `76.xxx.xxx.xxx` (not exact).

## Step 4 - TCP connection

Your computer opens a network connection to the Vercel server, usually HTTPS on port 443.

```text
Your PC ----- TCP connection ----- Vercel
```

## Step 5 - TLS/HTTPS encryption

Because the URL uses `https://`, the client performs a TLS handshake.

This:

- Encrypts data
- Prevents snooping

After the handshake: secure encrypted tunnel established.

## Step 6 - HTTP request sent over the internet

The raw HTTP request travels through routers, ISPs, backbone networks, and cloud edge servers, eventually reaching Vercel infrastructure.

## Step 7 - Vercel receives the request

Vercel sees `POST /ask`. It checks the deployment config and finds this route maps to your serverless function.

## Step 8 - Serverless function starts

Vercel spins up a runtime.

Something like:

- Node.js runtime starts
- Your function code loads

This may happen instantly if warm, slower if cold start.

## Step 9 - `req` object created

Vercel converts the raw HTTP request into a JavaScript object:

```js
req = {
  method: "POST",
  headers: {
    "content-type": "application/json"
  },
  body: '{"code":"int main(){return 0;}","question":"What does this do?"}'
};
```

Important: the body may still be a string at this point.

## Step 10 - Your handler starts

Execution enters:

```js
module.exports = async function handler(req, res)
```

Now your code runs line by line.

## Step 11 - CORS headers added

Your code:

```js
res.setHeader(...)
```

Adds response headers. The response is not sent yet, only prepared.

## Step 12 - Method check

Your code checks:

```js
if (req.method !== "POST")
```

Your request is POST, so execution continues.

## Step 13 - API key loaded

```js
const apiKey = process.env.GEMINI_API_KEY;
```

Node reads environment variables stored securely on Vercel, returning something like `AIza....`.

## Step 14 - Parse body

Your code:

```js
let body = req.body;
```

At this moment:

```text
body = '{"code":"int main(){return 0;}","question":"What does this do?"}'
```

Then:

```js
JSON.parse(body)
```

Converts it into a real JS object:

```js
{
  code: "int main(){return 0;}",
  question: "What does this do?"
}
```

## Step 15 - Extract variables

```js
const code = body.code;
const question = body.question;
```

Now:

```text
code = "int main(){return 0;}"
question = "What does this do?"
```

## Step 16 - Prompt creation

Your code builds a prompt like:

```text
You are a helpful programming assistant.
Answer the question about the code. Be concise and precise.

Code:
int main(){return 0;}

Question:
What does this do?
```

Stored in memory as a single string.

## Step 17 - Gemini URL built

```text
https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=AIza...
```

## Step 18 - `fetch()` creates a second HTTP request

Now your backend becomes a client. It is both:

- A server (to `curl`)
- A client (to Gemini)

## Step 19 - Backend sends request to Gemini

`fetch` sends:

```http
POST /v1beta/models/gemini-2.5-flash:generateContent HTTP/1.1
Host: generativelanguage.googleapis.com
Content-Type: application/json

{
  "contents": [
    {
      "role": "user",
      "parts": [
        {
          "text": "You are a helpful programming assistant..."
        }
      ]
    }
  ],
  "generationConfig": {
    "temperature": 0.2,
    "maxOutputTokens": 1024
  }
}
```

## Step 20 - Google receives request

Google infrastructure:

- Authenticates the API key
- Validates the request
- Sends the prompt into the Gemini model

## Step 21 - Gemini processes the prompt

Internally:

- Tokenization
- Neural inference
- Generation

The model predicts an answer, for example:

```text
"This is a simple C program where main returns 0, indicating successful execution."
```

## Step 22 - Gemini returns HTTP response

Google sends back:

```http
HTTP/1.1 200 OK
Content-Type: application/json

{
  "candidates": [
    {
      "content": {
        "parts": [
          {
            "text": "This is a simple C program..."
          }
        ]
      }
    }
  ]
}
```

## Step 23 - Your backend receives response

```js
const data = await response.json();
```

Now:

```js
data = {
  candidates: [...]
}
```

JavaScript object in memory.

## Step 24 - Extract answer text

Your code:

```js
const text = ...
```

Extracts:

```text
"This is a simple C program where main returns 0, indicating successful execution."
```

## Step 25 - Your backend creates final response

```js
json(res, 200, {
  answer: text,
  model
});
```

Creates the HTTP response:

```http
HTTP/1.1 200 OK
Content-Type: application/json

{
  "answer": "This is a simple C program where main returns 0, indicating successful execution.",
  "model": "gemini-2.5-flash"
}
```

## Step 26 - Response travels back through the internet

Back through Google to Vercel, then Vercel to your computer, encrypted over HTTPS.

## Step 27 - curl receives response

`curl` prints:

```json
{
  "answer": "This is a simple C program where main returns 0, indicating successful execution.",
  "model": "gemini-2.5-flash"
}
```

---

## Full data evolution (quick trace)

1. **curl command**
2. **Raw HTTP request**
3. **`req.body` string**
4. **Parsed JS object**
5. **Prompt string**
6. **Gemini JSON request**
7. **Gemini JSON response**
8. **Final response object**

## Key backend concept

Your server acts as both:

1. HTTP server (receives request from `curl`)
2. HTTP client (makes request to Gemini)