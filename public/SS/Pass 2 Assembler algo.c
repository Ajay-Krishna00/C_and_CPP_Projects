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
  char machinecode[10];
};

// Predefined opcode table with dummy machine codes for illustration
struct optab OPTAB[] = {
    {"LDA", "00"}, {"STA", "0C"}, {"LDCH", "50"}, {"STCH", "54"}, {"ADD", "18"}, {"SUB", "1C"}, {"MUL", "20"}, {"DIV", "24"}, {"COMP", "28"}, {"J", "3C"}, {"JEQ", "30"}, {"JGT", "34"}, {"JLT", "38"}, {"JSUB", "48"}, {"RSUB", "4C"}};

struct symtab SYMTAB[50];
int symCount = 0;

char *searchOptab(char opcode[])
{
  for (int i = 0; i < sizeof(OPTAB) / sizeof(OPTAB[0]); i++)
  {
    if (strcmp(OPTAB[i].opcode, opcode) == 0)
      return OPTAB[i].machinecode;
  }
  return NULL;
}

int searchSymtab(char label[])
{
  for (int i = 0; i < symCount; i++)
  {
    if (strcmp(SYMTAB[i].label, label) == 0)
      return SYMTAB[i].addr;
  }
  return -1;
}

void loadSymtab()
{
  FILE *fp = fopen("symtab.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening symtab.txt\n");
    exit(1);
  }
  while (fscanf(fp, "%s%d", SYMTAB[symCount].label, &SYMTAB[symCount].addr) != EOF)
  {
    symCount++;
  }
  fclose(fp);
}

int main()
{
  FILE *intermediate, *output, *objectcode;
  char label[20], opcode[20], operand[20];
  int loc = 0, startAddr = 0, firstExecAddr = 0, lastAddr = 0;
  int progLen = 0;
  char programName[20] = "------";

  intermediate = fopen("intermediate.txt", "r");
  output = fopen("output.txt", "w");
  objectcode = fopen("objectcode.txt", "w");

  if (intermediate == NULL || output == NULL || objectcode == NULL)
  {
    printf("File error.\n");
    return 1;
  }

  loadSymtab();

  char textRecord[1000] = ""; // Buffer to hold object codes for current text record
  int textStart = -1;         // Start address of current text record
  int textLen = 0;            // Length in bytes of current text record

  // Because we need to write header at top, we will buffer text records to write after header
  // But for simplicity here, we will write header at start with dummy length, then update at end

  // Write dummy header record (will overwrite later)
  fprintf(objectcode, "H^%-6s^%06X^%06X\n", programName, 0, 0);

  while (fscanf(intermediate, "%d%s%s%s", &loc, label, opcode, operand) != EOF)
  {
    // Track last address for program length calculation
    if (loc > lastAddr)
      lastAddr = loc;

    if (strcmp(opcode, "START") == 0)
    {
      strcpy(programName, label);
      startAddr = loc; // use loc field for starting address (decimal)
      firstExecAddr = startAddr;

      fprintf(output, "%d\t%s\t%s\t%s\n", loc, label, opcode, operand);
      continue;
    }

    if (strcmp(opcode, "END") == 0)
    {
      fprintf(output, "%d\t%s\t%s\t%s\n", loc, label, opcode, operand);

      // Write any remaining text record before ending
      if (textLen > 0)
      {
        fprintf(objectcode, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
        textLen = 0;
        textRecord[0] = '\0';
      }

      // Write END record with first executable address (in hex)
      fprintf(objectcode, "E^%06X\n", firstExecAddr);

      break;
    }

    char *mc = searchOptab(opcode);
    char objCode[20] = "";

    if (mc != NULL)
    {
      int addr = searchSymtab(operand);
      if (addr == -1 && strcmp(operand, "**") != 0)
      {
        printf("Undefined symbol: %s\n", operand);
        continue;
      }

      sprintf(objCode, "%s%04X", mc, addr);

      fprintf(output, "%d\t%s\t%s\t%s\t%s\n", loc, label, opcode, operand, objCode);

      // Start new text record if empty
      if (textLen == 0)
      {
        textStart = loc;
        if (firstExecAddr == 0)
          firstExecAddr = loc;
      }

      // If adding this objCode exceeds 30 bytes, write current text record and start new
      if ((textLen + strlen(objCode) / 2) > 30)
      {
        fprintf(objectcode, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
        strcpy(textRecord, "");
        textStart = loc;
        textLen = 0;
      }

      // Append caret + objCode to text record
      strcat(textRecord, "^");
      strcat(textRecord, objCode);
      textLen += strlen(objCode) / 2;
    }
    else if (strcmp(opcode, "BYTE") == 0)
    {
      if (operand[0] == 'C')
      {
        for (int i = 2; i < strlen(operand) - 1; i++)
        {
          char temp[3];
          sprintf(temp, "%02X", operand[i]);
          strcat(objCode, temp);
        }
      }
      else if (operand[0] == 'X')
      {
        strncpy(objCode, operand + 2, strlen(operand) - 3);
        objCode[strlen(operand) - 3] = '\0';
      }

      fprintf(output, "%d\t%s\t%s\t%s\t%s\n", loc, label, opcode, operand, objCode);

      if (textLen == 0)
        textStart = loc;

      if ((textLen + strlen(objCode) / 2) > 30)
      {
        fprintf(objectcode, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
        strcpy(textRecord, "");
        textStart = loc;
        textLen = 0;
      }

      strcat(textRecord, "^");
      strcat(textRecord, objCode);
      textLen += strlen(objCode) / 2;
    }
    else if (strcmp(opcode, "WORD") == 0)
    {
      int val = atoi(operand);
      sprintf(objCode, "%06X", val);
      fprintf(output, "%d\t%s\t%s\t%s\t%s\n", loc, label, opcode, operand, objCode);

      if (textLen == 0)
        textStart = loc;

      if ((textLen + 3) > 30)
      {
        fprintf(objectcode, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
        strcpy(textRecord, "");
        textStart = loc;
        textLen = 0;
      }

      strcat(textRecord, "^");
      strcat(textRecord, objCode);
      textLen += 3;
    }
    else
    {
      // RESW / RESB or unknown opcode - write as no object code

      fprintf(output, "%d\t%s\t%s\t%s\t---\n", loc, label, opcode, operand);

      // If we have object codes accumulated, write text record before the gap
      if (textLen > 0)
      {
        fprintf(objectcode, "T^%06X^%02X%s\n", textStart, textLen, textRecord);
        strcpy(textRecord, "");
        textLen = 0;
      }
    }
  }

  // Calculate program length in bytes (lastAddr - startAddr + size of last instruction)
  // Assuming last instruction size 3 bytes for safety, adjust if needed
  progLen = (lastAddr - startAddr) + 3;

  // Now rewind objectcode to update header record (at the start)
  rewind(objectcode);
  fprintf(objectcode, "H^%-6s^%06X^%06X\n", programName, startAddr, progLen);

  fclose(intermediate);
  fclose(output);
  fclose(objectcode);

  printf("Pass 2 completed. Listing written to output.txt and object code to objectcode.txt\n");
  return 0;
}
