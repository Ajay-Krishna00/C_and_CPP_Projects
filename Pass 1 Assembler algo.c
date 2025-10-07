// Input- assembler.asm

// COPY    START   1000
// FIRST   LDA     ALPHA
// **      ADD     ONE
// **      STA     BETA
// ALPHA   WORD    5
// ONE     RESW    1
// BETA    RESB    10
// **      BYTE    C'EOF'
// **      END     FIRST

// Output: Program length = 28

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symtab
{
  char label[20];
  int addr;
};

struct optab
{
  char opcode[10];
  int length;
};

struct symtab SYMTAB[50];
struct optab OPTAB[] = {{"LDA", 3}, {"STA", 3}, {"LDCH", 3}, {"STCH", 3}, {"ADD", 3}, {"SUB", 3}, {"MUL", 3}, {"DIV", 3}, {"COMP", 3}, {"J", 3}, {"JEQ", 3}, {"JGT", 3}, {"JLT", 3}, {"JSUB", 3}, {"RSUB", 3}};

int syscnt = 0;

int searchOpcode(char code[])
{
  for (int i = 0; i < sizeof(OPTAB) / sizeof(OPTAB[0]); i++)
  {
    if (strcmp(OPTAB[i].opcode, code) == 0)
    {
      return OPTAB[i].length;
    }
  }
  return -1;
}

void insertSymtab(char label[], int addr)
{
  strcpy(SYMTAB[syscnt].label, label);
  SYMTAB[syscnt].addr = addr;
  syscnt++;
}

int main()
{
  FILE *fp1, *fp2, *fp3;

  char label[20], opcode[20], operand[20];
  int startAddr, locCnt, length;

  fp1 = fopen("assembly.asm", "r");
  fp2 = fopen("symtab.txt", "w");
  fp3 = fopen("intermediate.txt", "w");

  if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }

  fscanf(fp1, "%s%s%s", label, opcode, operand);

  if (strcmp("START", opcode) == 0)
  {
    startAddr = atoi(operand); // standard C library function declared in <stdlib.h> that converts a string (array of characters) containing digits into an integer value.
    locCnt = startAddr;
    fprintf(fp3, "%d\t%s\t%s\t%s\n", locCnt, label, opcode, operand);
    fscanf(fp1, "%s%s%s", label, opcode, operand);
  }
  else
  {
    locCnt = 0;
  }

  while (strcmp(opcode, "END") != 0)
  {
    if (strcmp(label, "**") != 0)
    {
      insertSymtab(label, locCnt);
      fprintf(fp2, "%s\t%d\n", label, locCnt);
    }
    int len = searchOpcode(opcode);
    if (len != -1)
    {
      locCnt += len;
    }
    else if (strcmp(opcode, "WORD") == 0)
    {
      locCnt += 3;
    }
    else if (strcmp(opcode, "RESW") == 0)
    {
      locCnt += 3 * atoi(operand);
    }
    else if (strcmp(opcode, "RESB") == 0)
    {
      locCnt += atoi(operand);
    }
    else if (strcmp(opcode, "BYTE") == 0)
    {
      locCnt += strlen(operand) - 3; // C'EOF' -> 3 chars inside quotes
    }
    else
    {
      printf("Error: Invalid Code %s\n", opcode);
    }
    fprintf(fp3, "%d\t%s\t%s\t%s\n", locCnt, label, opcode, operand);
    fscanf(fp1, "%s %s %s", label, opcode, operand);
  }
  fprintf(fp3, "%d\t%s\t%s\t%s\n", locCnt, label, opcode, operand);
  length = locCnt - startAddr;
  printf("Program length = %d\n", length);

  fclose(fp1);
  fclose(fp2);
  fclose(fp3);
  return 0;
}