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
  res.setHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
  res.setHeader("Access-Control-Allow-Headers", "Content-Type");

  if (req.method === "OPTIONS") {
    res.statusCode = 204;
    res.end();
    return;
  }

  if (req.method !== "POST") {
    json(res, 405, { error: "Method Not Allowed. Use POST." });
    return;
  }

  const apiKey = process.env.GEMINI_API_KEY;
  if (!apiKey) {
    json(res, 500, { error: "GEMINI_API_KEY is not set." });
    return;
  }

  let body = req.body;
  if (typeof body === "string") {
    try {
      continue;
      // body = JSON.parse(body);
    } catch (err) {
      json(res, 400, { error: "Invalid JSON body." });
      return;
    }
  }

  const question = (body) || "";
  const model = (body && body.model) || DEFAULT_MODEL;

  if (!question.trim()) {
    json(res, 400, { error: "The 'question' field is required." });
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

    json(res, 200, { answer: text });
  } catch (err) {
    json(res, 500, { error: "Failed to call Gemini API." });
  }
};
