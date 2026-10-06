#!/usr/bin/env node
/**
 * CLI helper to ask Gemini via the /ask endpoint.
 *
 * Usage:
 *   node ask.js "What does Lex yywrap do?"
 *   node ask.js "Explain this" public/CD/ValidVariable.l
 *   node ask.js "Explain this" public/CD/ValidVariable.l -o explanation.md
 */

const fs = require("fs");
const path = require("path");

const API_URL = "https://c-and-cpp-projects.vercel.app/ask";

async function run() {
    const rawArgs = process.argv.slice(2);

    if (rawArgs.length === 0 || rawArgs.includes("-h") || rawArgs.includes("--help")) {
        console.log(`
Usage:
  node ask.js "<question>" [filepath] [-o output_file]

Examples:
  node ask.js "What is an epsilon closure?"
  node ask.js "Explain this code" public/CD/ValidVariable.l
  node ask.js "Explain this" public/CD/ValidVariable.y -o explanation.md
        `);
        process.exit(0);
    }

    let outputFile = null;
    let codeFile = null;
    let question = "";

    const args = [];
    for (let i = 0; i < rawArgs.length; i++) {
        if (rawArgs[i] === "-o" || rawArgs[i] === "--output") {
            outputFile = rawArgs[++i];
        } else {
            args.push(rawArgs[i]);
        }
    }

    if (args.length >= 1) {
        question = args[0];
    }
    if (args.length >= 2) {
        codeFile = args[1];
    }

    let codeContent = "";
    if (codeFile) {
        if (!fs.existsSync(codeFile)) {
            console.error(`Error: File not found: ${codeFile}`);
            process.exit(1);
        }
        codeContent = fs.readFileSync(codeFile, "utf-8");
    }

    const payload = {
        question: question
    };
    if (codeContent) {
        payload.code = codeContent;
    }

    console.log("-> Asking Gemini via /ask endpoint...");

    try {
        const res = await fetch(API_URL, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(payload)
        });

        const data = await res.json();

        if (!res.ok) {
            console.error("API Error:", data.error || res.statusText);
            process.exit(1);
        }

        const answer = data.answer || "";

        if (outputFile) {
            fs.writeFileSync(outputFile, answer, "utf-8");
            console.log(`-> Response successfully saved to: ${outputFile}`);
        } else {
            console.log("\n==================== GEMINI ANSWER ====================\n");
            console.log(answer);
            console.log("\n=======================================================\n");
        }
    } catch (err) {
        console.error("Failed to connect to API:", err.message);
        process.exit(1);
    }
}

run();
