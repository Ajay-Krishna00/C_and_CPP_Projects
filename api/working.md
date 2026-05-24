“When I run this curl command, what EXACTLY happens step-by-step, and what does the data look like at every stage?”

Let’s trace the entire lifecycle.

Your Command
curl -X POST "https://c-and-cpp-projects.vercel.app/ask" \
  -H "Content-Type: application/json" \
  -d '{"code":"int main(){return 0;}","question":"What does this do?"}'
  
BIG PICTURE FLOW
Your Terminal
    │
    ▼
Internet
    │
    ▼
Vercel Serverless Function
    │
    ▼
Your handler(req, res)
    │
    ▼
Gemini API
    │
    ▼
Gemini Response
    │
    ▼
Your API formats response
    │
    ▼
curl prints final JSON

Now let’s zoom into EVERY stage.

STEP 1 — You run curl

You type:

curl -X POST ...

curl is an HTTP client.

Its job:

create HTTP request
send over internet
display response
STEP 2 — curl builds raw HTTP request

Internally curl converts your command into something like:

POST /ask HTTP/1.1
Host: c-and-cpp-projects.vercel.app
Content-Type: application/json
Content-Length: 74

{"code":"int main(){return 0;}","question":"What does this do?"}

This is REAL HTTP data.

Understanding the structure
Request Line
POST /ask HTTP/1.1

Means:

method = POST
path = /ask
protocol = HTTP/1.1
Headers
Content-Type: application/json

Tells server:

"The body is JSON."
Body
{"code":"int main(){return 0;}","question":"What does this do?"}

Actual payload.

STEP 3 — DNS lookup

Your machine sees:

c-and-cpp-projects.vercel.app

It must find:

actual IP address

So OS asks DNS servers:

"What IP belongs to this domain?"

Gets something like:

76.xxx.xxx.xxx

(Not exact.)

STEP 4 — TCP connection

Your computer opens network connection to Vercel server.

Usually:

HTTPS on port 443

So:

Your PC ───── TCP connection ─────► Vercel
STEP 5 — TLS/HTTPS encryption

Because URL uses:

https://

browser/curl performs TLS handshake.

This:

encrypts data
prevents snooping

After handshake:

✅ secure encrypted tunnel established

STEP 6 — HTTP request sent over internet

The raw HTTP request travels through:

routers
ISPs
backbone networks
cloud edge servers

Eventually reaches Vercel infrastructure.

STEP 7 — Vercel receives request

Vercel sees:

POST /ask

Now routing happens.

Vercel checks deployment config and finds:

This route maps to your serverless function.
STEP 8 — Serverless function starts

Vercel spins up runtime.

Something like:

Node.js runtime starts
Your function code loads

This may happen:

instantly if warm
slower if cold start
STEP 9 — req object created

Vercel converts raw HTTP request into JavaScript object:

req = {
  method: "POST",
  headers: {
    "content-type": "application/json"
  },
  body: '{"code":"int main(){return 0;}","question":"What does this do?"}'
}

IMPORTANT:

The body initially may still be a STRING.

STEP 10 — Your handler starts

Execution enters:

module.exports = async function handler(req, res)

Now your code runs line-by-line.

STEP 11 — CORS headers added

Your code:

res.setHeader(...)

adds response headers.

At this point response is NOT sent yet.

Only prepared internally.

STEP 12 — Method check

Your code checks:

if (req.method !== "POST")

Your request IS POST.

So execution continues.

STEP 13 — API key loaded
const apiKey = process.env.GEMINI_API_KEY;

Node reads environment variables stored securely on Vercel.

Suppose:

AIza....

returned.

STEP 14 — Parse body

Your code:

let body = req.body;

At this moment:

body = '{"code":"int main(){return 0;}","question":"What does this do?"}'

STRING.

Then:

JSON.parse(body)

converts it into REAL JS object:

{
  code: "int main(){return 0;}",
  question: "What does this do?"
}
STEP 15 — Extract variables
const code = body.code;
const question = body.question;

Now:

code = "int main(){return 0;}"
question = "What does this do?"
STEP 16 — Prompt creation

Your code builds:

You are a helpful programming assistant.
Answer the question about the code. Be concise and precise.

Code:
int main(){return 0;}

Question:
What does this do?

Stored in memory as giant string.

STEP 17 — Gemini URL built
https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-flash:generateContent?key=AIza...
STEP 18 — fetch() creates second HTTP request

NOW your backend becomes a CLIENT.

Important concept:

Your backend is both:
- server (to curl)
- client (to Gemini)
STEP 19 — Backend sends request to Gemini

fetch sends:

POST /v1beta/models/gemini-2.5-flash:generateContent HTTP/1.1
Host: generativelanguage.googleapis.com
Content-Type: application/json

Body:

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
STEP 20 — Google receives request

Google infrastructure:

authenticates API key
validates request
sends prompt into Gemini model
STEP 21 — Gemini processes prompt

Internally:

tokenization
neural inference
generation

Model predicts answer.

Maybe:

"This is a simple C program where main returns 0, indicating successful execution."
STEP 22 — Gemini returns HTTP response

Google sends back:

HTTP/1.1 200 OK
Content-Type: application/json

Body:

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
STEP 23 — Your backend receives response
const data = await response.json();

Now:

data = {
  candidates: [...]
}

JavaScript object in memory.

STEP 24 — Extract answer text

Your code:

const text = ...

extracts:

"This is a simple C program where main returns 0, indicating successful execution."
STEP 25 — Your backend creates final response
json(res, 200, {
  answer: text,
  model
});

Creates HTTP response:

HTTP/1.1 200 OK
Content-Type: application/json

Body:

{
  "answer": "This is a simple C program where main returns 0, indicating successful execution.",
  "model": "gemini-2.5-flash"
}
STEP 26 — Response travels back through internet

Back through:

Google → Vercel
Vercel → your computer

Encrypted over HTTPS.

STEP 27 — curl receives response

curl prints:

{
  "answer": "This is a simple C program where main returns 0, indicating successful execution.",
  "model": "gemini-2.5-flash"
}

to your terminal.

DONE.

FULL DATA EVOLUTION
A. Your curl command
curl ...

↓

B. Raw HTTP request
POST /ask HTTP/1.1
...

↓

C. req.body string
'{"code":"int main(){return 0;}","question":"What does this do?"}'

↓

D. Parsed JS object
{
  code: "...",
  question: "..."
}

↓

E. Prompt string
You are a helpful programming assistant...

↓

F. Gemini JSON request
{
  "contents": [...]
}

↓

G. Gemini JSON response
{
  "candidates": [...]
}

↓

H. Final response object
{
  "answer": "...",
  "model": "..."
}
Most important backend concept here

Your server acts as:

1. HTTP Server

Receives request from curl.

AND simultaneously:

2. HTTP Client

Makes request to Gemini.

This dual role is central to backend engineering.