# Compiler Design (CD) Lab Viva Examination & Comprehensive Reference Guide

A complete, high-yield preparation manual for the **Compiler Design Laboratory Viva-Voce**. This guide covers core theoretical concepts, in-depth questions and answers for all **16 lab programs across 4 Cycles**, all **inbuilt library functions & system variables**, and exact **compilation/execution commands**.

---

## Table of Contents
1. [Core Compiler Design Theory Viva Questions](#1-core-compiler-design-theory-viva-questions)
2. [Experiment-Wise Deep Dive (Cycle I - IV)](#2-experiment-wise-deep-dive-cycle-i---iv)
   - [Cycle I: Automata & Lexical Analysis](#cycle-i-automata--lexical-analysis)
   - [Cycle II: Lex & Yacc Utilities](#cycle-ii-lex--yacc-utilities)
   - [Cycle III: Parsers (Syntax Analysis)](#cycle-iii-parsers-syntax-analysis)
   - [Cycle IV: Intermediate Code & Backend Code Generation](#cycle-iv-intermediate-code--backend-code-generation)
3. [Inbuilt Functions, System Variables & Directives Reference](#3-inbuilt-functions-system-variables--directives-reference)
   - [C Standard Library (`<string.h>`, `<ctype.h>`, `<stdio.h>`, `<stdlib.h>`)](#c-standard-library-functions)
   - [Lex / Flex Engine Variables & Routines](#lex--flex-inbuilt-variables--routines)
   - [Yacc / Bison Variables, Directives & Error Handlers](#yacc--bison-variables-directives--macros)
   - [8086 Assembly Registers & Instruction Set](#8086-microprocessor-registers--instructions)
4. [Compilation, Linking & Execution Commands](#4-compilation-linking--execution-commands)
5. [Examiner Rapid-Fire Questions & Traps](#5-examiner-rapid-fire-questions--traps)

---

## 1. Core Compiler Design Theory Viva Questions

### Q1: What is a Compiler? How does it differ from an Interpreter and an Assembler?
- **Compiler**: A translator that converts a high-level source program (e.g., C, C++) in its entirety into low-level machine code or assembly language at once. Execution occurs separately after compilation.
- **Interpreter**: Translates and executes source code line-by-line (e.g., Python, Ruby). It reports errors immediately on encountering them and does not produce an independent binary executable.
- **Assembler**: Translates assembly language mnemonics (symbolic low-level code like `MOV AX, BX`) into machine language binary opcodes.

### Q2: What are the phases of a modern Compiler?
A compiler operates in **6 analytical and synthesis phases**, supported by two cross-cutting components:
1. **Lexical Analysis (Scanner)**: Reads characters, strips whitespace/comments, and groups characters into **Tokens**.
2. **Syntax Analysis (Parser)**: Validates token sequences against the grammar rules (Context-Free Grammar) and constructs a **Parse Tree** or **Abstract Syntax Tree (AST)**.
3. **Semantic Analysis**: Checks static semantics, type consistency, array bound validity, scope resolution, and operator compatibility.
4. **Intermediate Code Generation (ICG)**: Produces an explicit, machine-independent low-level intermediate representation (e.g., Three Address Code, Quadruples, Postfix).
5. **Code Optimization**: Improves intermediate code for faster execution and smaller code size without altering program output (e.g., constant folding, dead-code elimination).
6. **Target Code Generation**: Maps optimized intermediate representation to target machine instructions (e.g., 8086 assembly, x86-64, MIPS).
- **Symbol Table Management**: Central data store holding identifier attributes (name, type, scope, memory address, size).
- **Error Handling Routine**: Detects, reports, and recovers from errors encountered at each phase.

```
Source Code ──> [Lexical Analyzer] ──> Tokens
                      │
                      ▼
               [Syntax Analyzer] ──> Parse Tree / AST
                      │
                      ▼
              [Semantic Analyzer] ──> Annotated AST
                      │
                      ▼
             [Intermediate Code Gen] ──> Three Address Code (TAC)
                      │
                      ▼
              [Code Optimizer] ──> Optimized TAC
                      │
                      ▼
             [Target Code Gen] ──> 8086 Assembly Code

        [ Symbol Table ] <====== Across All Phases ======> [ Error Handler ]
```

### Q3: What is the difference between a Phase and a Pass?
- **Phase**: A logical step in the compilation process (e.g., Lexical, Syntax, Code Gen).
- **Pass**: A physical traversal through the entire source program or its intermediate representation.
  - *Single-Pass Compiler*: Processes the source file from start to finish in one scan (e.g., Pascal). Extremely fast, but limited optimization.
  - *Multi-Pass Compiler*: Scans the program or intermediate representation multiple times (e.g., C/C++ modern compilers like GCC/Clang). Allows modularity and machine-independent global optimizations.

### Q4: What is the Front-End vs Back-End of a compiler?
- **Front-End**: Machine-independent. Includes Lexical, Syntax, Semantic analysis, and Intermediate Code Generation. Depends only on the source language.
- **Back-End**: Machine-dependent. Includes Target Machine Optimization, Instruction Selection, Register Allocation, and Assembly/Machine code generation. Depends only on target machine architecture.
- *Advantage of separation*: To support $N$ source languages on $M$ target architectures, we only need $N$ front-ends and $M$ back-ends ($N + M$) instead of $N \times M$ separate compilers.

### Q5: What is a Token, a Lexeme, and a Pattern?
- **Token**: An abstract symbol representing a category of lexical units (e.g., `KEYWORD`, `IDENTIFIER`, `NUMBER`, `OPERATOR`).
- **Lexeme**: The actual instance of source characters matching a pattern (e.g., `int`, `totalSum`, `3.1415`, `+`).
- **Pattern**: The formal rule (usually expressed as a Regular Expression) describing what characters form a token.

### Q6: What is a Context-Free Grammar (CFG)?
A CFG is a 4-tuple: $G = (V_N, V_T, P, S)$ where:
- $V_N$: Set of non-terminal symbols.
- $V_T$: Set of terminal symbols (tokens).
- $P$: Set of production rules of the form $A \to \alpha$ where $A \in V_N$ and $\alpha \in (V_N \cup V_T)^*$.
- $S$: Start symbol ($S \in V_N$).

### Q7: What is Ambiguity in a Grammar? Why is it problematic?
- A grammar is **ambiguous** if there exists at least one string that yields **two or more distinct parse trees** (or two distinct leftmost/rightmost derivations).
- *Problem*: The compiler cannot determine which semantic meaning or operator precedence to execute (e.g., `2 + 3 * 4` could evaluate to 20 instead of 14).
- *Solution*: Rewrite the grammar with explicit precedence levels or use precedence/associativity declarations in parser generators like Yacc (`%left`, `%right`).

### Q8: What is Left Recursion and how is it eliminated?
- A grammar rule is left-recursive if $A \Rightarrow^+ A\alpha$.
- In top-down parsers (Recursive Descent / LL(1)), left recursion causes an infinite loop / stack overflow because the parser continuously calls the same rule without consuming any input.
- **Elimination of immediate left recursion**:
  $$A \to A\alpha \mid \beta \quad (\beta \text{ does not start with } A)$$
  is transformed into:
  $$A \to \beta A'$$
  $$A' \to \alpha A' \mid \epsilon$$

### Q9: What is Left Factoring?
- When two productions for a non-terminal share a common prefix: $A \to \alpha\beta_1 \mid \alpha\beta_2$.
- The parser cannot decide which production to choose by looking only at the next terminal token.
- **Left Factoring transformation**:
  $$A \to \alpha A'$$
  $$A' \to \beta_1 \mid \beta_2$$

---

## 2. Experiment-Wise Deep Dive (Cycle I - IV)

---

### Cycle I: Automata & Lexical Analysis

#### 1. `LexicalAnalyzer.c`
- **Objective**: Scans a C source snippet, strips redundant spaces, tabs, single-line (`//`) and multi-line (`/* ... */`) comments, and categorizes tokens into Keywords, Identifiers, Constants, Operators, and Special Characters with line numbers.
- **Viva Questions & Answers**:
  - *Q: How does your code distinguish between a Keyword and an Identifier?*
    - **A**: The code first reads a valid alphanumeric token starting with an alphabet or underscore. It then calls `isKeyword()`, which performs `strcmp()` against a predefined lookup table of C keywords (`int`, `float`, `return`, `if`, `while`, etc.). If a match is found, it is tagged as `KEYWORD`; otherwise, it is categorized as `IDENTIFIER`.
  - *Q: How do you handle buffer lookahead in lexical analysis?*
    - **A**: Lexical analyzers use two pointers (`lexeme_begin` and `forward`). When matching operators like `==` vs `=`, or `++` vs `+`, the scanner reads one extra character ahead. If the next character does not form a compound token, the forward pointer retracts or ungets the character.
  - *Q: What data structures are used for token recognition?*
    - **A**: Constant string arrays for keywords and boolean lookup functions (`isOperator`, `isSpecialChar`, `isalpha`, `isdigit`).

#### 2. `EpsilonClosure.c`
- **Objective**: Determines the $\epsilon$-closure ($\epsilon$-reachability) of all states in an NFA with $\epsilon$-transitions.
- **Viva Questions & Answers**:
  - *Q: What is the formal definition of $\epsilon$-closure of a state $q$?*
    - **A**: $\epsilon\text{-closure}(q)$ is the set of all states reachable from state $q$ via zero or more $\epsilon$-transitions ($\delta^*(q, \epsilon)$). It always includes the state $q$ itself because of the zero-transition path.
  - *Q: What algorithm is used to compute the $\epsilon$-closure in your program?*
    - **A**: A Depth-First Search (DFS) or Stack-based traversal. For each state $i$, we push $i$ onto a stack, mark it visited, and while the stack is non-empty, pop state $u$ and inspect all states $v$ reachable by an $\epsilon$-transition. Any unvisited $v$ is added to the closure set and pushed onto the stack.
  - *Q: What is the time complexity of computing $\epsilon$-closure?*
    - **A**: $O(|V| + |E_\epsilon|)$ for each state, where $V$ is the number of states and $E_\epsilon$ is the count of $\epsilon$-transitions. For all states, it is $O(|V| \cdot (|V| + |E_\epsilon|))$.

#### 3. `EpsilonNFA_to_NFA.c`
- **Objective**: Converts an $\epsilon$-NFA into an equivalent standard NFA without $\epsilon$-transitions.
- **Viva Questions & Answers**:
  - *Q: What mathematical formula governs this conversion?*
    - **A**: For state $q$ and input symbol $a \in \Sigma$:
      $$\delta'(q, a) = \hat{\delta}(q, a) = \epsilon\text{-closure}(\delta(\epsilon\text{-closure}(q), a))$$
  - *Q: Under what condition does a state become a final state in the resulting NFA?*
    - **A**: A state $q$ is an accepting (final) state in the new NFA if and only if $\epsilon\text{-closure}(q)$ contains at least one final state of the original $\epsilon$-NFA.
  - *Q: Does the set of states or input alphabet change in this conversion?*
    - **A**: The state set $Q$ and alphabet $\Sigma$ remain identical; only the transition relation $\delta'$ is recomputed and the accepting states $F'$ may expand.

#### 4. `NFA_to_DFA.c`
- **Objective**: Converts an NFA to an equivalent DFA using the **Subset Construction Algorithm** (Powerset Construction).
- **Viva Questions & Answers**:
  - *Q: Why is an NFA converted to a DFA before implementation in a scanner?*
    - **A**: An NFA can have multiple transitions for the same input symbol and $\epsilon$-transitions, requiring non-deterministic backtracking. A DFA has exactly one unique deterministic transition per input symbol, running in deterministic $O(n)$ time for an input of length $n$.
  - *Q: What is the maximum number of states in the converted DFA?*
    - **A**: If the NFA has $n$ states, the powerset has $2^n$ possible subsets. Hence, the resulting DFA has at most $2^n$ states (though in practice, only reachable states are generated).
  - *Q: How does the algorithm detect when no new DFA states need to be generated?*
    - **A**: A queue / worklist of undiscovered state subsets is maintained. When transition computations for all existing subsets produce state sets that are already in the DFA state table, the algorithm terminates.

#### 5. `MinimiseDFA.c`
- **Objective**: Minimizes a DFA using the **Equivalence Partitioning Method** ($k$-equivalence / Myhill-Nerode theorem).
- **Viva Questions & Answers**:
  - *Q: What are 0-equivalent states?*
    - **A**: Two states $p$ and $q$ are 0-equivalent if they cannot be distinguished by the empty string $\epsilon$. This divides the state set into two initial partitions: $P_0 = \{F, Q \setminus F\}$ (Accepting states vs Non-accepting states).
  - *Q: When are two states $p$ and $q$ in partition $P_k$ deemed $(k+1)$-equivalent?*
    - **A**: If for every input symbol $a \in \Sigma$, both transitions $\delta(p, a)$ and $\delta(q, a)$ land in the same partition group of $P_k$.
  - *Q: When does the iterative partitioning stop?*
    - **A**: When $P_{k+1} = P_k$ (no groups are split in a complete pass).
  - *Q: Is the minimized DFA unique?*
    - **A**: Yes, by the **Myhill-Nerode Theorem**, the minimal DFA recognizing a given regular language is unique up to state renaming (isomorphism).

---

### Cycle II: Lex & Yacc Utilities

#### Architecture of Lex and Yacc
- **Lex (Lexical Analyzer Generator)**: Converts regular expressions into a deterministic finite automaton in C (`lex.yy.c`).
- **Yacc (Yet Another Compiler-Compiler)**: An **LALR(1)** bottom-up parser generator. Converts grammar specifications into an LALR(1) state machine in C (`y.tab.c`, `y.tab.h`).
- **Interaction**:
  1. `yyparse()` is called in `main()`.
  2. Whenever `yyparse()` needs the next token, it calls `yylex()`.
  3. `yylex()` reads the input buffer (`yyin`), matches the longest lexeme, places semantic values in `yylval`, and returns the integer token code to `yyparse()`.
  4. `yyparse()` applies shift and reduce operations against its internal parsing stack.

```
+------------+       +-------------------+       +---------------------+
| program.l  | ===>  | lex / flex        | ===>  | lex.yy.c            | --+
+------------+       +-------------------+       +---------------------+   |
                                                                           |--> [ gcc ] ==> Executable
+------------+       +-------------------+       +---------------------+   |
| program.y  | ===>  | yacc -d / bison -d| ===>  | y.tab.c & y.tab.h   | --+
+------------+       +-------------------+       +---------------------+
```

#### 6. `NameSubstring.l`
- **Objective**: Recognizes all strings that do **not** contain the first 4 characters of your name (`AJAY`) as a substring.
- **Viva Questions & Answers**:
  - *Q: How does Lex prioritize conflicting rules?*
    - **A**:
      1. **Longest Match**: The rule matching the greatest number of characters wins.
      2. **First Rule Priority**: If two rules match the exact same number of characters, the rule listed higher up in the `.l` file is executed.
  - *Q: How is substring rejection achieved in Lex?*
    - **A**: An explicit rule matching `.*AJAY.*` triggers a flag `contains = 1;` or prints "Rejected". The rule for other valid strings or characters checks this flag at newline `\n`.

#### 7. `ValidVariable.l` & `ValidVariable.y`
- **Objective**: Validates variable identifiers in C (starts with a letter or underscore, followed by letters, digits, or underscores).
- **Viva Questions & Answers**:
  - *Q: What regular expression in Lex matches a valid C variable?*
    - **A**: `[a-zA-Z_][a-zA-Z0-9_]*`
  - *Q: Why validate variables in Yacc if Lex can match them with a regex?*
    - **A**: Demonstrates the separation of lexical tokens (Lex yields `LETTER`, `DIGIT`, `UNDERSCORE`) and grammatical syntax rules (Yacc validates whether the structural composition satisfies the identifier grammar rule).

#### 8. `Calculator.l` & `Calculator.y`
- **Objective**: Arithmetic calculator supporting `+`, `-`, `*`, `/`, `%`, unary minus, and parentheses with division-by-zero checks.
- **Viva Questions & Answers**:
  - *Q: How are operator precedence and associativity declared in Yacc?*
    - **A**: Using directives in the definition section:
      ```yacc
      %left ADD SUB
      %left MUL DIV MOD
      %right UMINUS
      ```
      - `%left`: Left-associative (evaluated left to right: `a - b - c` is `(a - b) - c`).
      - `%right`: Right-associative (evaluated right to left: `a = b = c`).
      - Rules listed **lower down** have **higher precedence** (`MUL` has higher precedence than `ADD`).
  - *Q: What is `yylval`?*
    - **A**: A global variable used to pass semantic values from `yylex()` to `yyparse()`. By default it is an `int`, but can be customized using `%union` (e.g., to pass `double`, `char*`, or AST node pointers).
  - *Q: How is division by zero handled?*
    - **A**: In the semantic action block for division:
      ```c
      if ($3 == 0) { yyerror("Division by zero"); $$ = 0; }
      else { $$ = $1 / $3; }
      ```
  - *Q: What does `yyerrok` do?*
    - **A**: Tells Yacc that error recovery is complete, resetting the parser's internal error status so subsequent errors are reported immediately.

#### 9. `AST_Generator.l` & `AST_Generator.y`
- **Objective**: Generates an Abstract Syntax Tree (AST) for expressions and outputs Preorder and Postorder traversals.
- **Viva Questions & Answers**:
  - *Q: What is the difference between a Parse Tree and an Abstract Syntax Tree (AST)?*
    - **A**:
      - **Parse Tree (Concrete Syntax Tree)**: Retains every grammar derivation step, including punctuation, parentheses, and single-production chains ($E \to T \to F \to \text{id}$).
      - **Abstract Syntax Tree (AST)**: A dense, semantic representation where internal nodes represent **operators** and leaf nodes represent **operands**. Parentheses and redundant chain nodes are omitted.
  - *Q: How are AST nodes created dynamically in Yacc actions?*
    - **A**: A C struct `ASTNode` with operator/value string and `left`/`right` child pointers is allocated using `malloc()`:
      ```c
      expr: expr '+' term { $$ = createNode("+", $1, $3); }
      ```
  - *Q: What do Preorder and Postorder traversals of an arithmetic AST represent?*
    - **A**:
      - **Preorder** (Root, Left, Right): Yields **Prefix Notation** (Polish notation: `+ a b`).
      - **Inorder** (Left, Root, Right): Yields standard **Infix Notation** (`a + b`).
      - **Postorder** (Left, Right, Root): Yields **Postfix Notation** (Reverse Polish notation: `a b +`), which is directly usable for stack-machine evaluation.

#### 10. `ForSyntax.l` & `ForSyntax.y`
- **Objective**: Validates the syntax of C `for` loops, including initialization, condition, increment/decrement, and loop body.
- **Viva Questions & Answers**:
  - *Q: Can a `for` loop have empty expressions like `for(;;)`?*
    - **A**: Yes. In the grammar, each of the three clauses (initialization, condition, and increment) must be defined with nullable (empty) alternative rules:
      ```yacc
      for_stmt: FOR '(' init_opt ';' cond_opt ';' incr_opt ')' body ;
      init_opt: /* empty */ | expr ;
      ```
  - *Q: How does Yacc distinguish compound statements from single statements in loop bodies?*
    - **A**: By defining rules where `body` can expand to either `{ stmt_list }` (enclosed in braces) or a single `stmt;` terminated by a semicolon.

---

### Cycle III: Parsers (Syntax Analysis)

#### 11. `OperatorPrecedence.c`
- **Objective**: Implements an operator precedence parser using a precedence relation matrix (`<`, `>`, `=`).
- **Viva Questions & Answers**:
  - *Q: What constitutes an Operator Grammar?*
    - **A**: A context-free grammar with two strict properties:
      1. No production has an $\epsilon$ (empty string) on its right-hand side.
      2. No two non-terminals appear consecutively on the right-hand side ($A \to \alpha B C \beta$ is forbidden).
  - *Q: What do the three precedence relations mean?*
    - **A**:
      - $a \lessdot b$: Terminal $a$ "yields precedence" to terminal $b$ (triggers a **Shift**).
      - $a \doteq b$: Terminal $a$ has the "same precedence" as $b$ (e.g., matching parentheses `(` $\doteq$ `)`).
      - $a \gtrdot b$: Terminal $a$ "takes precedence" over terminal $b$ (triggers a **Reduce** of the handle).
  - *Q: What are the advantages and disadvantages of Operator Precedence parsing?*
    - **A**:
      - *Advantage*: Very simple to write and fast for arithmetic expression parsing.
      - *Disadvantage*: Cannot handle unary minus easily, cannot handle $\epsilon$-productions, and handles only a restricted subset of CFGs.

#### 12. `FirstAndFollow.c`
- **Objective**: Simulates the computation of FIRST and FOLLOW sets for any CFG.
- **Viva Questions & Answers**:
  - *Q: What are the rules to compute $\text{FIRST}(X)$?*
    - **A**:
      1. If $X$ is a terminal, $\text{FIRST}(X) = \{X\}$.
      2. If $X \to \epsilon$ is a production, add $\epsilon$ to $\text{FIRST}(X)$.
      3. If $X \to Y_1 Y_2 \dots Y_k$ is a production:
         - Add all non-$\epsilon$ symbols of $\text{FIRST}(Y_1)$ to $\text{FIRST}(X)$.
         - If $\text{FIRST}(Y_1)$ contains $\epsilon$, add non-$\epsilon$ symbols of $\text{FIRST}(Y_2)$, and so on.
         - If all $Y_1 \dots Y_k$ contain $\epsilon$, add $\epsilon$ to $\text{FIRST}(X)$.
  - *Q: What are the rules to compute $\text{FOLLOW}(A)$?*
    - **A**:
      1. Place `$` (input end-marker) in $\text{FOLLOW}(S)$, where $S$ is the start symbol.
      2. If there is a production $A \to \alpha B \beta$, everything in $\text{FIRST}(\beta)$ (except $\epsilon$) is in $\text{FOLLOW}(B)$.
      3. If there is a production $A \to \alpha B$, or $A \to \alpha B \beta$ where $\text{FIRST}(\beta)$ contains $\epsilon$, everything in $\text{FOLLOW}(A)$ is in $\text{FOLLOW}(B)$.
  - *Q: Can $\epsilon$ ever be in a $\text{FOLLOW}$ set?*
    - **A**: **Never**. FOLLOW sets contain only terminal symbols and the end-marker `$`. They indicate what terminals can legally appear immediately following a non-terminal in a sentential form.

#### 13. `RecursiveDescentParser.c`
- **Objective**: Implements a top-down predictive recursive descent parser for arithmetic expressions with step tracing.
- **Viva Questions & Answers**:
  - *Q: How does Recursive Descent parsing work?*
    - **A**: Each non-terminal symbol in the grammar corresponds to a distinct C function (`E()`, `Eprime()`, `T()`, `Tprime()`, `F()`). The parser begins at the start symbol function and parses tokens recursively using a global lookahead pointer.
  - *Q: What happens if a grammar has left recursion in a recursive descent parser?*
    - **A**: Calling `E()` immediately invokes `E()` before any token is consumed, producing an infinite recursive loop resulting in a **Segmentation Fault (stack overflow)**.
  - *Q: How does the parser handle backtracking?*
    - **A**: A general recursive descent parser requires backtracking. However, an **LL(1) Predictive Parser** eliminates backtracking by using a 1-token lookahead to uniquely choose the correct production branch.

#### 14. `ShiftReduceParser.c`
- **Objective**: Implements a bottom-up Shift-Reduce parser displaying stack, input buffer, and actions.
- **Viva Questions & Answers**:
  - *Q: What are the 4 fundamental actions in a Shift-Reduce parser?*
    - **A**:
      1. **Shift**: Push the next input token from the buffer onto the stack.
      2. **Reduce**: When the top of the stack matches the RHS of a production rule (a *handle*), replace that substring with the rule's LHS non-terminal.
      3. **Accept**: Successfully parsing finishes when the stack contains only the start symbol and the input buffer is empty (`$`).
      4. **Error**: Syntax error state where neither shift nor reduce can proceed.
  - *Q: What is a "Handle"?*
    - **A**: A substring of a right-sentential form that matches the right-hand side of a production rule, and whose reduction represents one step along the reverse of a rightmost derivation.
  - *Q: What are the two common parsing conflicts in bottom-up parsing?*
    - **A**:
      - **Shift-Reduce (S/R) Conflict**: The parser cannot decide whether to shift the next input symbol or reduce the current stack contents (e.g., the dangling-else ambiguity).
      - **Reduce-Reduce (R/R) Conflict**: The parser cannot decide which of two distinct production rules to reduce by, because the stack contents match both right-hand sides.

---

### Cycle IV: Intermediate Code & Backend Code Generation

#### 15. `IntermediateCodeGen.c`
- **Objective**: Generates Three Address Code (TAC), Quadruples, and Triples from infix arithmetic expressions.
- **Viva Questions & Answers**:
  - *Q: What is Three Address Code (TAC)?*
    - **A**: A sequence of instructions of the general form $x = y \text{ op } z$, where each instruction contains at most one operator and at most three memory addresses/variables.
  - *Q: Compare Quadruples, Triples, and Indirect Triples.*
    - **A**:
      | Format | Fields | Advantages | Disadvantages |
      |---|---|---|---|
      | **Quadruple** | `(op, arg1, arg2, result)` | Explicit result names; easily moved during optimization. | Consumes more memory for explicit temporary variable names. |
      | **Triple** | `(op, arg1, arg2)` | Compact; references previous results by instruction index `(i)`. | Moving/optimizing instructions requires updating all references. |
      | **Indirect Triple**| An array of pointers to Triples | Easy instruction reordering during optimization without rewriting index pointers. | Extra level of pointer indirection. |
  - *Q: How does your code convert an expression into TAC?*
    - **A**: It uses Dijkstra's **Shunting-Yard algorithm** to convert the infix expression into postfix tokens via an operator stack, and then evaluates the postfix tokens using an operand stack, emitting temporary variables (`t1`, `t2`, etc.) for every binary operator.

#### 16. `CodeGen8086.c`
- **Objective**: Converts Three Address Code statements into assemble-ready 8086 assembly language (`MOV`, `ADD`, `SUB`, `MUL`, `DIV`, `CMP`, jumps).
- **Viva Questions & Answers**:
  - *Q: How are Three Address Code statements mapped to 8086 instructions?*
    - **A**:
      - Addition ($t_1 = a + b$):
        ```assembly
        MOV AX, a
        ADD AX, b
        MOV t1, AX
        ```
      - Multiplication ($t_1 = a * b$):
        ```assembly
        MOV AX, a
        MOV BX, b
        IMUL BX
        MOV t1, AX
        ```
      - Division ($t_1 = a / b$):
        ```assembly
        MOV AX, a
        CWD           ; Sign extend AX into DX:AX
        MOV BX, b
        IDIV BX
        MOV t1, AX
        ```
  - *Q: Why is register allocation necessary?*
    - **A**: Microprocessors have a limited number of high-speed registers (e.g., `AX`, `BX`, `CX`, `DX`). If variables exceed available registers, the compiler must "spill" registers to memory (RAM), which introduces memory latency.
  - *Q: What do `.MODEL SMALL`, `.DATA`, and `.CODE` signify in 8086 assembly?*
    - **A**:
      - `.MODEL SMALL`: Memory model where all code fits in one 64KB segment and all data fits in one 64KB segment.
      - `.DATA`: Segment directive where global and static variables are allocated (`DW` = Define Word = 16 bits).
      - `.CODE`: Segment directive containing executable machine instructions.

---

## 3. Inbuilt Functions, System Variables & Directives Reference

### C Standard Library Functions

#### `<string.h>`
- `strcmp(s1, s2)`: Compares two strings character by character. Returns `0` if identical, negative if $s1 < s2$, positive if $s1 > s2$.
- `strncmp(s1, s2, n)`: Compares at most the first `n` characters of two strings.
- `strcpy(dest, src)`: Copies the null-terminated string `src` into buffer `dest`.
- `strncpy(dest, src, n)`: Copies up to `n` characters from `src` to `dest`.
- `strcat(dest, src)`: Appends the string `src` to the end of `dest`.
- `strlen(s)`: Returns the number of characters in string `s` excluding the terminating null byte `\0`.
- `strchr(s, ch)`: Returns a pointer to the **first occurrence** of character `ch` in string `s`, or `NULL` if not found.
- `strstr(haystack, needle)`: Finds the first occurrence of substring `needle` inside `haystack`.
- `strtok(str, delim)`: Tokenizes string `str` using delimiter characters. Subsequent calls pass `NULL` as the first argument. Modifies original string with `\0`.
- `memmove(dest, src, n)`: Safely copies `n` bytes from `src` to `dest`, handling overlapping memory regions correctly.

#### `<ctype.h>`
- `isalpha(c)`: Checks if character `c` is an alphabetic letter (`A-Z` or `a-z`).
- `isdigit(c)`: Checks if character `c` is a decimal digit (`0-9`).
- `isalnum(c)`: Checks if character `c` is alphanumeric (`isalpha(c) || isdigit(c)`).
- `isspace(c)`: Checks for whitespace characters (space, `\t`, `\n`, `\v`, `\f`, `\r`).
- `isupper(c)` / `islower(c)`: Checks for uppercase or lowercase characters.

#### `<stdio.h>`
- `printf(format, ...)` / `scanf(format, ...)`: Standard formatted console output and input.
- `sprintf(str, format, ...)`: Formats and stores text into character buffer `str`.
- `sscanf(str, format, ...)`: Reads formatted input directly from a string buffer.
- `fopen(path, mode)`: Opens a file stream (modes: `"r"`, `"w"`, `"a"`).
- `fclose(stream)`: Closes an open file stream.
- `fgetc(stream)`: Reads the next single character from a file stream.
- `fgets(str, n, stream)`: Reads a line up to `n-1` characters from a file stream into `str`.
- `feof(stream)`: Tests the end-of-file indicator for the given stream.

#### `<stdlib.h>`
- `malloc(size)`: Dynamically allocates `size` uninitialized bytes from the heap; returns `void*`.
- `calloc(num, size)`: Allocates zero-initialized memory for an array of `num` elements.
- `free(ptr)`: Releases dynamically allocated heap memory back to the operating system.
- `exit(status)`: Immediately terminates process execution with exit code `status`.
- `atoi(str)`: Converts ASCII string to `int`.
- `atof(str)`: Converts ASCII string to `double`.

---

### Lex / Flex Inbuilt Variables & Routines

| Identifier | Type | Role & Significance |
|---|---|---|
| `yylex()` | Function `int yylex(void)` | Main scanning routine generated by Lex. Scans input and returns token integer codes. |
| `yytext` | `char*` or `char[]` | Pointer to the null-terminated matched lexeme currently read from input. |
| `yyleng` | `int` | Length of the matched string in `yytext`. |
| `yyin` | `FILE*` | Input stream pointer. Defaults to `stdin`, but can be redirected to read files via `fopen()`. |
| `yyout` | `FILE*` | Output stream pointer. Defaults to `stdout`. |
| `yywrap()` | Function `int yywrap(void)` | Called by `yylex()` at EOF. Returning `1` terminates scanning; returning `0` allows chaining another file. |
| `%option noyywrap`| Directive | Instructs Flex not to call `yywrap()`, eliminating the need to link with `-lfl`. |
| `ECHO` | Macro | Default Lex fallback action: writes `yytext` to `yyout` (`fwrite(yytext, yyleng, 1, yyout)`). |
| `REJECT` | Macro | Directs scanner to pass on current match and attempt the next best rule matching the input. |
| `yymore()` | Function | Tells Lex that the next matched token should be appended to `yytext` rather than overwriting it. |
| `yyless(n)` | Function | Returns all but the first `n` characters of the current token back to the input stream. |

---

### Yacc / Bison Variables, Directives & Macros

| Identifier | Purpose & Usage |
|---|---|
| `yyparse()` | Main parsing function. Returns `0` if parsing succeeds (input valid) and `1` on syntax error. |
| `yyerror(const char *s)`| User-supplied error callback function invoked when a syntax error is discovered. |
| `yylval` | Global variable carrying the semantic value associated with the token returned by `yylex()`. |
| `yychar` | Stores the integer code of the current lookahead token. |
| `yynerrs` | Counter holding the total number of syntax errors encountered during parsing. |
| `$$` | Represents the semantic value of the Left-Hand Side (LHS) non-terminal in a production rule. |
| `$1, $2, $3, ...` | Represents the semantic value of the 1st, 2nd, 3rd symbol on the Right-Hand Side (RHS). |
| `%token` | Declares terminal tokens returned by `yylex()`. |
| `%type <field>` | Declares the type of a non-terminal symbol mapped to a `%union` field. |
| `%union { ... }` | Declares possible C data types that semantic values (`yylval` and symbols) can hold. |
| `%left` / `%right` | Declares operator associativity and precedence. Later lines have higher precedence. |
| `%nonassoc` | Declares binary operators that cannot be chained (e.g., `x < y < z` is illegal). |
| `%start` | Explicitly specifies the start non-terminal symbol of the grammar (defaults to first rule). |
| `yyerrok` | Macro that clears the parser error state, allowing subsequent error reporting. |
| `yyclearin` | Discards the current lookahead token after an error. |

---

### 8086 Microprocessor Registers & Instructions

#### 16-Bit General Purpose Registers
- `AX` (**Accumulator Register**): Primary register for arithmetic, logic, and I/O operations. Multiplicand/product and dividend/quotient destination.
- `BX` (**Base Register**): Can be used as a pointer for indirect base memory addressing.
- `CX` (**Count Register**): Used as a loop counter in string iterations and shift/rotate instructions.
- `DX` (**Data Register**): Holds the high 16 bits of 32-bit products/dividends (`DX:AX`), and I/O port addresses.

#### Segment Registers & Pointer Registers
- `CS` (Code Segment), `DS` (Data Segment), `SS` (Stack Segment), `ES` (Extra Segment).
- `IP` (Instruction Pointer): Holds offset of the next machine instruction to execute.
- `SP` (Stack Pointer), `BP` (Base Pointer), `SI` (Source Index), `DI` (Destination Index).

#### Instructions Used in Compiler Code Generation
- `MOV dest, src`: Copies data from source operand to destination operand.
- `ADD dest, src`: Computes `dest = dest + src`.
- `SUB dest, src`: Computes `dest = dest - src`.
- `IMUL reg/mem`: Signed multiplication. Multiplies `AX` by operand; result stored in `DX:AX`.
- `IDIV reg/mem`: Signed division. Divides `DX:AX` by operand; quotient in `AX`, remainder in `DX`.
- `CMP op1, op2`: Subtracts `op2` from `op1` without altering values, setting CPU status flags (`ZF`, `SF`, `OF`).
- `JMP label`: Unconditional jump to `label`.
- `JE` / `JNE`: Jump if Equal (`ZF=1`) / Jump if Not Equal (`ZF=0`).
- `JG` / `JL` / `JGE` / `JLE`: Conditional jumps for signed numbers (Greater, Less, Greater-Equal, Less-Equal).

---

## 4. Compilation, Linking & Execution Commands

### A. Pure C Programs (Cycles I, III, IV)
Use GCC with `-Wall` (all warnings) and output binary flag `-o`:

```bash
# 1. Lexical Analyzer
gcc LexicalAnalyzer.c -o LexicalAnalyzer
./LexicalAnalyzer

# 2. Epsilon Closure
gcc EpsilonClosure.c -o EpsilonClosure
./EpsilonClosure

# 3. Epsilon NFA to NFA
gcc EpsilonNFA_to_NFA.c -o EpsilonNFA_to_NFA
./EpsilonNFA_to_NFA

# 4. NFA to DFA (Subset Construction)
gcc NFA_to_DFA.c -o NFA_to_DFA
./NFA_to_DFA

# 5. DFA Minimization
gcc MinimiseDFA.c -o MinimiseDFA
./MinimiseDFA

# 6. Operator Precedence Parser
gcc OperatorPrecedence.c -o OperatorPrecedence
./OperatorPrecedence

# 7. First and Follow Sets
gcc FirstAndFollow.c -o FirstAndFollow
./FirstAndFollow

# 8. Recursive Descent Parser
gcc RecursiveDescentParser.c -o RecursiveDescentParser
./RecursiveDescentParser

# 9. Shift-Reduce Parser
gcc ShiftReduceParser.c -o ShiftReduceParser
./ShiftReduceParser

# 10. Intermediate Code Generator (TAC & Quadruples)
gcc IntermediateCodeGen.c -o IntermediateCodeGen
./IntermediateCodeGen

# 11. 8086 Backend Target Code Generator
gcc CodeGen8086.c -o CodeGen8086
./CodeGen8086
```

---

### B. Standalone Lex Program (Cycle II)
```bash
# Generate C scanner from Lex source:
lex NameSubstring.l          # Creates lex.yy.c (or flex NameSubstring.l)

# Compile generated C scanner:
gcc lex.yy.c -o NameSubstring

# Execute:
./NameSubstring
```

---

### C. Combined Lex & Yacc Programs (Cycle II)
The exact 4-step sequence to compile Yacc with Lex:

#### Valid Variable Identifier:
```bash
yacc -d ValidVariable.y       # Generates y.tab.c and y.tab.h (-d flag emits header)
lex ValidVariable.l           # Generates lex.yy.c
gcc y.tab.c lex.yy.c -o ValidVariable
./ValidVariable
```

#### Arithmetic Calculator:
```bash
yacc -d Calculator.y          # Emits y.tab.c and y.tab.h
lex Calculator.l              # Emits lex.yy.c
gcc y.tab.c lex.yy.c -o Calculator -lm   # -lm links math library if pow/sqrt used
./Calculator
```

#### Abstract Syntax Tree (AST) Generator:
```bash
yacc -d AST_Generator.y
lex AST_Generator.l
gcc y.tab.c lex.yy.c -o AST_Generator
./AST_Generator
```

#### For Loop Syntax Validator:
```bash
yacc -d ForSyntax.y
lex ForSyntax.l
gcc y.tab.c lex.yy.c -o ForSyntax
./ForSyntax
```

---

### D. Crucial Flags & Troubleshooting
- **`yacc -d` / `bison -d`**: The `-d` flag is **mandatory**; it generates `y.tab.h` (or `<file>.tab.h`), defining the token constants needed by `yylex()` in `lex.yy.c`.
- **`yacc -v` / `bison -v`**: Generates a detailed verbose report file (`y.output`), listing every LR(0) state, transition table, and any Shift/Reduce or Reduce/Reduce conflicts.
- **`-lfl` or `-ly`**: If you do not supply custom `main()` or `yywrap()` functions, linking flags `-lfl` (Flex library) or `-ly` (Yacc library) supply default stubs. When `%option noyywrap` and custom `main()` are provided, `-lfl` is not needed.

---

## 5. Examiner Rapid-Fire Questions & Traps

1. **Can Yacc handle ambiguous grammars?**
   - *Answer*: By default, Yacc reports Shift-Reduce and Reduce-Reduce conflicts on ambiguous grammars. However, it can resolve them if precedence and associativity directives (`%left`, `%right`, `%nonassoc`) are specified. In the absence of declarations, Yacc defaults to shifting on Shift-Reduce conflicts and picking the earlier rule on Reduce-Reduce conflicts.
2. **Why does Lexical Analysis exist as a separate phase from Syntax Analysis?**
   - *Answer*:
     - *Simplicity*: Regular expressions are simpler and cleaner for token specs than full CFGs.
     - *Efficiency*: Specialized finite state automata run significantly faster than pushdown automata / parsing stacks.
     - *Portability*: Character encoding discrepancies and stream buffering are isolated from the parser.
3. **What is the difference between Top-Down and Bottom-Up parsing?**
   - *Answer*:
     - Top-Down: Constructs parse tree starting from the Start Symbol down to the terminals (derivation-based, e.g., LL(1)).
     - Bottom-Up: Starts from the input terminal string and reduces back up to the Start Symbol (reduction-based, e.g., LR(0), SLR(1), LALR(1)).
4. **Why is LALR(1) preferred over CLR(1)?**
   - *Answer*: CLR(1) has identical power but generates huge numbers of states (often thousands). LALR(1) merges states with identical LR(0) cores having compatible lookahead sets, reducing the table size to that of SLR(1) while retaining almost all of CLR(1)'s parsing power.
5. **What is a "Dangling Else" problem? How is it resolved?**
   - *Answer*: In `if expr then if expr then stmt else stmt`, the grammar is ambiguous regarding which `if` the `else` binds to. Solved by shifting `else` so that it matches with the closest unmatched `if`.
6. **What is Constant Folding vs Constant Propagation?**
   - *Answer*:
     - *Constant Folding*: Evaluating constant operations at compile-time (e.g., replacing `3 + 4` with `7`).
     - *Constant Propagation*: Replacing variable occurrences with known constant values assigned earlier (e.g., `x = 10; y = x + 2;` becomes `y = 10 + 2;`).
7. **What is Dead Code Elimination?**
   - *Answer*: Removing instructions whose computed results are never subsequently read or reachable (e.g., code following an unconditional `return` or `goto`).
8. **What is Peephole Optimization?**
   - *Answer*: A local code optimization technique examining a short sliding window ("peephole") of target instructions to eliminate redundant loads/stores, simplify algebraic expressions, and remove unreachable jumps.
9. **What is a Cross-Compiler?**
   - *Answer*: A compiler that runs on one machine architecture (the host) but generates executable target code for a different architecture (the target), common in embedded systems development.
10. **What is Bootstrapping?**
    - *Answer*: The process of compiling a compiler in the very programming language it is intended to compile (e.g., writing a C compiler in C).
