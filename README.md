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

### Quick Usage (GET with auto URL encoding)

On modern Linux/macOS, literal spaces in URLs cause `curl (3) URL rejected`. Use `-G --data-urlencode` so `curl` safely encodes spaces:

```bash
curl -G "https://c-and-cpp-projects.vercel.app/ask" --data-urlencode "q=What is an epsilon closure in NFA"
```

### Save Directly to a Markdown File (`-o`)

To save Gemini's answer directly to a file:

```bash
curl -G "https://c-and-cpp-projects.vercel.app/ask" --data-urlencode "q=Explain Lex and Yacc workflow" -o answer.md
```

Or via simple POST (no URL encoding needed):
```bash
curl -d "q=Explain Lex and Yacc workflow" https://c-and-cpp-projects.vercel.app/ask -o answer.md
```
*(The endpoint directly returns clean Markdown text, so `answer.md` will contain formatted markdown ready to read without raw JSON envelopes).*

### 1-Word Command Shortcut (Recommended for your terminal)

Add this function to your shell to ask questions without typing the URL or flags:

**On Linux / macOS / WSL (add to `~/.bashrc` or `~/.zshrc`):**
```bash
ask() {
  curl -s -G "https://c-and-cpp-projects.vercel.app/ask" --data-urlencode "q=$*" -o answer.md
  echo "Answer saved to answer.md"
}
```
*Usage:*
```bash
ask give me the c code to convert epsilon nfa to nfa
```

**On Windows PowerShell (add to your `$PROFILE`):**
```powershell
function ask($q) {
  curl.exe -s -G "https://c-and-cpp-projects.vercel.app/ask" --data-urlencode "q=$q" -o answer.md
  Write-Host "Answer saved to answer.md"
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
