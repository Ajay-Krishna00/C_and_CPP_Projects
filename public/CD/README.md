# Compiler Design (CD) Lab Programs

This directory contains implementations for all 4 Cycles of the Compiler Design laboratory curriculum.

## Table of Contents

### Cycle I: Automata & Lexical Analysis (in C)
1. **[LexicalAnalyzer.c](./LexicalAnalyzer.c)**: Lexical analyzer ignoring redundant spaces, tabs, and newlines; categorizes keywords, identifiers, constants, operators, and special characters.
2. **[EpsilonClosure.c](./EpsilonClosure.c)**: Finds the $\epsilon$-closure of all states of any given NFA with $\epsilon$-transitions.
3. **[EpsilonNFA_to_NFA.c](./EpsilonNFA_to_NFA.c)**: Converts an NFA with $\epsilon$-transitions to an equivalent NFA without $\epsilon$-transitions.
4. **[NFA_to_DFA.c](./NFA_to_DFA.c)**: Converts an NFA to a DFA using the subset construction algorithm.
5. **[MinimiseDFA.c](./MinimiseDFA.c)**: Minimizes any given DFA using the equivalence partitioning method.

---

### Cycle II: Lex & Yacc
1. **[NameSubstring.l](./NameSubstring.l)**: Lex program recognizing all strings that do **not** contain the first 4 characters of your name (`AJAY`) as a substring.
2. **[ValidVariable.l](./ValidVariable.l)** & **[ValidVariable.y](./ValidVariable.y)**: YACC program to validate identifiers starting with a letter followed by letters or digits.
3. **[Calculator.l](./Calculator.l)** & **[Calculator.y](./Calculator.y)**: Arithmetic calculator supporting `+`, `-`, `*`, `/`, `%`, unary minus, and parentheses with division-by-zero checks.
4. **[AST_Generator.l](./AST_Generator.l)** & **[AST_Generator.y](./AST_Generator.y)**: BNF rules in Yacc to generate and print an Abstract Syntax Tree (AST), preorder traversal, and postorder traversal.
5. **[ForSyntax.l](./ForSyntax.l)** & **[ForSyntax.y](./ForSyntax.y)**: YACC program checking the syntax of C `for` loops (initialization, condition, increment/decrement, and body).

---

### Cycle III: Parsers (in C)
1. **[OperatorPrecedence.c](./OperatorPrecedence.c)**: Operator precedence parsing using a precedence relation matrix (`<`, `>`, `=`).
2. **[FirstAndFollow.c](./FirstAndFollow.c)**: Simulates FIRST and FOLLOW sets for any given context-free grammar.
3. **[RecursiveDescentParser.c](./RecursiveDescentParser.c)**: LL(1) recursive descent parser for arithmetic expressions with step tracing.
4. **[ShiftReduceParser.c](./ShiftReduceParser.c)**: Bottom-up Shift-Reduce parser with stack, input buffer, and reduction actions display.

---

### Cycle IV: Intermediate Code & Backend Code Generation (in C)
1. **[IntermediateCodeGen.c](./IntermediateCodeGen.c)**: Generates Three Address Code (TAC), Quadruples, and Triples from infix expressions.
2. **[CodeGen8086.c](./CodeGen8086.c)**: Compiler backend converting Three Address Code into complete, assemble-ready 8086 assembly instructions (`MOV`, `ADD`, `SUB`, `MUL`, `DIV`, `CMP`, jumps).

---

## Compilation Commands

### C Programs
```bash
gcc LexicalAnalyzer.c -o LexicalAnalyzer
./LexicalAnalyzer
```

### Lex & Yacc Programs
```bash
# Example: Valid Variable
yacc -d ValidVariable.y
lex ValidVariable.l
gcc y.tab.c lex.yy.c -o ValidVariable
./ValidVariable
```
