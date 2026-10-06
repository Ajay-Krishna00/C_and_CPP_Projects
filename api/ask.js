const GEMINI_API_URL = "https://generativelanguage.googleapis.com/v1beta/models";
const DEFAULT_MODEL = "gemini-2.5-flash";
const MAX_CODE_CHARS = 80000;

function json(res, statusCode, payload) {
  res.statusCode = statusCode;
  res.setHeader("Content-Type", "application/json; charset=utf-8");
  res.end(JSON.stringify(payload));
}

module.exports = async function handler(req, res) {
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  res.setHeader("Access-Control-Allow-Headers", "Content-Type, Accept");

  if (req.method === "OPTIONS") {
    res.statusCode = 204;
    res.end();
    return;
  }

  if (req.method !== "GET" && req.method !== "POST") {
    json(res, 405, { error: "Method Not Allowed. Use GET or POST." });
    return;
  }

  const apiKey = process.env.GEMINI_API_KEY;
  if (!apiKey) {
    json(res, 500, { error: "GEMINI_API_KEY is not set." });
    return;
  }

  let question = "";
  let model = DEFAULT_MODEL;

  // 1. Support GET query params (e.g. /ask?q=What+is+Lex)
  if (req.method === "GET") {
    const q = (req.query && (req.query.q || req.query.question)) || "";
    question = typeof q === "string" ? q : "";
    if (req.query && req.query.model) {
      model = req.query.model;
    }
  }

  // 2. Support POST body (JSON object, plain text string, or urlencoded)
  if (req.method === "POST") {
    let body = req.body;

    if (typeof body === "string") {
      try {
        body = JSON.parse(body);
      } catch (err) {
        // Keep as raw string
      }
    }

    if (typeof body === "string") {
      question = body;
    } else if (body && typeof body === "object") {
      if (body.code && body.question) {
        question = `Code:\n${body.code}\n\nQuestion:\n${body.question}`;
      } else if (body.question) {
        question = body.question;
      } else if (body.code) {
        question = body.code;
      } else {
        // If curl -d "simple text" without '=' sent, body keys might contain the text
        const keys = Object.keys(body);
        if (keys.length === 1 && body[keys[0]] === "") {
          question = keys[0];
        }
      }
      if (body.model) model = body.model;
    }
  }

  if (!question || !question.trim()) {
    json(res, 400, { error: "The 'question' (or 'q') is required." });
    return;
  }

  if (question.length > MAX_CODE_CHARS) {
    json(res, 413, { error: "Question is too large. Please send a smaller question." });
    return;
  }

  const prompt = [
    "You are a helpful programming assistant.",
    "Answer the question about the code. Be concise and precise.",
    "",
    "Question:",
    question
  ].join("\n");

  const url = `${GEMINI_API_URL}/${encodeURIComponent(model)}:generateContent?key=${encodeURIComponent(apiKey)}`;

  try {
    const response = await fetch(url, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        contents: [{ role: "user", parts: [{ text: prompt }] }],
        generationConfig: { temperature: 0.2, maxOutputTokens: 10024 }
      })
    });

    const data = await response.json();

    if (!response.ok) {
      json(res, response.status, { error: "Gemini API error.", details: data });
      return;
    }

    const text = (data.candidates || [])
      .flatMap((candidate) => (candidate.content && candidate.content.parts) || [])
      .map((part) => part.text || "")
      .join("")
      .trim();

    // Check if client explicitly wants JSON
    const wantsJson = (req.query && req.query.format === "json") ||
                      (req.headers["accept"] && req.headers["accept"].includes("application/json") && !req.headers["user-agent"]?.includes("curl"));

    if (wantsJson) {
      json(res, 200, { answer: text });
    } else {
      // By default for curl and general requests, return clean Markdown directly
      res.statusCode = 200;
      res.setHeader("Content-Type", "text/markdown; charset=utf-8");
      res.end(text + "\n");
    }
  } catch (err) {
    json(res, 500, { error: "Failed to call Gemini API." });
  }
};
