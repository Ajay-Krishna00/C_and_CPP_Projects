#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int searchOpcode(char code[])
{
  char opcode[][10] = {"JSUB", "LDA", "COMP", "JEQ", "ADD", "J", "MUL", "SUB", "STA", "RSUB", "STL"};
  for (int i = 0; i < 11; i++)
  {
    if (strcmp(code, opcode[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
}

int main()
{
  FILE *f1, *f2, *f3;
  f1 = fopen("sample.asm", "r");
  f2 = fopen("SYMTAB.txt", "w");
  f3 = fopen("intermediate.txt", "w");

  if (!f1 || !f2 || !f3)
  {
    printf("Error opening files.\n");
    exit(1);
  }

  int locctr, start, len;
  char label[20], opcode[20], operand[20];

  fscanf(f1, "%s %s %s", label, opcode, operand);
  if (strcmp(opcode, "START") == 0)
  {
    start = strtol(operand, NULL, 16);
    locctr = start;
    fprintf(f3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    fscanf(f1, "%s %s %s", label, opcode, operand);
  }

  while (strcmp(opcode, "END") != 0)
  {
    fprintf(f3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    if (strcmp(label, "**") != 0)
    {
      fprintf(f2, "%s\t%X\n", label, locctr);
    }
    if (searchOpcode(opcode))
    {
      locctr += 3;
    }
    else if (strcmp(opcode, "WORD") == 0)
    {
      locctr += 3;
    }
    else if (strcmp(opcode, "RESW") == 0)
    {
      locctr += 3 * atoi(operand);
    }
    else if (strcmp(opcode, "RESB") == 0)
    {
      locctr += atoi(operand);
    }
    else if (strcmp(opcode, "BYTE") == 0)
    {
      if (operand[0] == 'C')
      {
        locctr += (strlen(operand) - 3);
      }
      else if (operand[0] == 'X')
      {
        locctr += (strlen(operand) - 3) / 2;
      }
    }
    else
    {
      printf("Invalid opcode: %s\n", opcode);
    }
    fscanf(f1, "%s %s %s", label, opcode, operand);
  }
  fprintf(f3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
  printf("Program length= %X", locctr - start);
  fclose(f1);
  fclose(f2);
  fclose(f3);
  return 0;
}