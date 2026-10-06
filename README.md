# C_and_CPP_Projects
## ⚝ Welcome to my C and C++ Projects repository! 😎

This repository showcases various projects, lab curricula, and experiments in C and C++. Feel free to explore, learn, and use them as inspiration for your own projects.

---

## Repository Structure

The `public/` directory contains complete academic lab programs:

- **[public/CD](./public/CD)**: **Compiler Design (CD)** (Cycles I – IV: Lexical analysis, $\epsilon$-NFA, DFA minimization, Lex & Yacc, AST generator, Operator Precedence, First & Follow, Recursive Descent, Shift-Reduce, Intermediate Code Gen, and 8086 Assembly backend).
- **[public/CN](./public/CN)**: Computer Networks (Client-Server sockets, TCP/UDP, routing algorithms, stop-and-wait, selective repeat).
- **[public/OS](./public/OS)**: Operating Systems (CPU scheduling, Banker's algorithm, memory allocation, page replacement).
- **[public/SS](./public/SS)**: System Software (Two-pass Assembler algorithms).
- **[public/DSA](./public/DSA)**: Data Structures & Algorithms (Linked lists, sorting, trees, stacks, queues).

---

## Static Index and File Access

This repository is deployed on Vercel:

- `https://c-and-cpp-projects.vercel.app/index.json` returns a JSON tree of all files in `public/`.
- Any file can be downloaded directly by path, for example:
  `https://c-and-cpp-projects.vercel.app/CD/LexicalAnalyzer.c`
  `https://c-and-cpp-projects.vercel.app/CN/TCP_Server.c`

---

## Gemini AI `/ask` Endpoint

The backend provides a serverless `/ask` endpoint powered by Gemini to ask programming and concept questions from any system or terminal.

### Quick Usage (Simple GET Request)

From **any computer or terminal**, you can query Gemini without needing local files, JSON formatting, or `-X POST` headers:

```bash
curl "https://c-and-cpp-projects.vercel.app/ask?q=What is an epsilon closure in NFA"
```

### Save Directly to a Markdown File (`-o`)

To save Gemini's answer directly to a file without displaying it in the terminal:

```bash
curl "https://c-and-cpp-projects.vercel.app/ask?q=Explain Lex and Yacc workflow" -o answer.md
```
*(The endpoint directly returns clean Markdown text, so `answer.md` will contain formatted markdown ready to read without raw JSON envelopes).*

### Optional: 1-Word Command Shortcut

You can make it a simple 1-word command on any machine:

**On Linux / macOS / WSL (add to `~/.bashrc` or `~/.zshrc`):**
```bash
ask() {
  curl -s "https://c-and-cpp-projects.vercel.app/ask?q=$*" -o answer.md
  echo "Saved answer to answer.md"
}
```
*Usage:*
```bash
ask What is DFA minimization
```

**On Windows PowerShell (add to your `$PROFILE`):**
```powershell
function ask($q) {
  curl.exe -s "https://c-and-cpp-projects.vercel.app/ask?q=$q" -o answer.md
  Write-Host "Saved answer to answer.md"
}
```
*Usage:*
```powershell
ask "What is DFA minimization"
```

---

## Setup & Deployment

1. Set the `GEMINI_API_KEY` environment variable in Vercel.
2. Vercel automatically runs `npm run build` (`node generate-index.js`) to generate `public/index.json`.

---

## Contributing

- Feel free to submit pull requests with new projects, exercises, or examples!
- Open an issue to report bugs or suggest ideas.

## License

This repository is licensed under the MIT License.

## Author

**Ajay Krishna D**
- Email: enthusiastajay00@gmail.com
