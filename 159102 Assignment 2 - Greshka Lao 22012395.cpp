// Greshka Lao 22012395

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

void instructions();
int converthex(string string);
string convertdec(int decimal);

fstream text;
string filename, line[256];
int memory[256], pc, ir, length, i, reg[16];

int main() {
  for (i = 0; i < 256; i++) {
    memory[i] = 0;
  }
  for (i = 0; i < 16; i++) {
    reg[i] = 0;
  }
  cout << "Enter the file name of the MASSEY machine code: ";
  getline(cin, filename);
  text.open(filename.c_str(), fstream::in);
  i = 0;
  cout << endl;
  while (getline(text, line[i])) {
    memory[i] = converthex(line[i]);
    cout << "Memory[" << hex << uppercase << i << "] = " << line[i] << endl;
    i++;
  }
  text.close();
  length = i;
  cout << endl;
  instructions();
}

int converthex(string string) {
  int strleng, dec, j, digit, k;
  dec = 0;
  strleng = string.length();
  for (k = 0; k < strleng; k++) {
    j = strleng - k - 1;
    if ((string[k] >= '0') && (string[k] <= '9')) {
      digit = string[k] - 48;
      dec = dec + (digit * (pow(16, j)));
    } else if ((string[k] >= 'A') && (string[k] <= 'F')) {
      digit = string[k] - 55;
      dec = dec + (digit * (pow(16, j)));
    }
  }
  return dec;
}

void instructions() {
  string operands[3];
  char opcode;
  bool jump, halt;
  int x, y, z;
  // x is the first number from the instruction(register/memory/value),
  // y is the second, z is the third
  pc = 0;
  jump = false;
  halt = false;
  while (halt == false) {
    ir = memory[pc];
    for (i = 0; i < 4; i++) {
      operands[i] = line[pc][i+1];
    }
    opcode = line[pc][0];
    if (opcode == '1') {
      x = converthex(operands[0]);
      y = converthex(operands[1]+operands[2]);
      reg[x] = y;
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(y);
    } else if (opcode == '2') {
      x = converthex(operands[1]);
      y = converthex(operands[2]);
      reg[x] = reg[y];
      cout << line[pc] << "   " << "R" << operands[1] << " = " << convertdec(reg[y]);
    } else if (opcode == '3') {
      x = converthex(operands[0]);
      y = converthex(operands[1]+operands[2]);
      reg[x] = memory[y];
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(memory[y]);
    } else if (opcode == '4') {
      x = converthex(operands[0]);
      y = converthex(operands[1]+operands[2]);
      memory[y] = reg[x];
      cout << line[pc] << "   " << "Memory[" << (operands[1]+operands[2]);
      cout << "] = " << convertdec(reg[x]);
    } else if (opcode == '6') {
      x = converthex(operands[0]);
      y = converthex(operands[1]);
      z = converthex(operands[2]);
      reg[x] = reg[y] + reg[z];
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == '7') {
      x = converthex(operands[1]);
      reg[x] = (reg[x] ^ 0xFFFF) + 1;
      cout << line[pc] << "   " << "R" << operands[1] << " = " << convertdec(reg[x]);
    } else if (opcode == '8') {
      x = converthex(operands[0]);
      y = converthex(operands[2]);
      reg[x] = reg[x] >> y;
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == '9') {
      x = converthex(operands[0]);
      y = converthex(operands[2]);
      reg[x] = reg[x] << y;
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == 'A') {
      x = converthex(operands[0]);
      y = converthex(operands[1]);
      z = converthex(operands[2]);
      reg[x] = reg[y] & reg[z];
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == 'B') {
      x = converthex(operands[0]);
      y = converthex(operands[1]);
      z = converthex(operands[2]);
      reg[x] = reg[y] | reg[z];
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == 'C') {
      x = converthex(operands[0]);
      y = converthex(operands[1]);
      z = converthex(operands[2]);
      reg[x] = reg[y] ^ reg[z];
      cout << line[pc] << "   " << "R" << operands[0] << " = " << convertdec(reg[x]);
    } else if (opcode == 'E') {
      cout << "Halt" << endl;
      halt = true;
      exit(10);
    } else if (opcode == 'D') {
      x = converthex(operands[0]);
      if (reg[x] == reg[0]) {
        jump = true;
        y = converthex(operands[1]+operands[2]);
        cout << line[pc] << "   " << "R" << operands[0] << " equal to R0";
        pc = y-1;
      } else {
        cout << line[pc] << "   " << "R" << operands[0] << " not equal to R0";
      }
    }
    if ((opcode != '0') && (opcode != 'E')) {
      cout << "   PC = " << hex << uppercase << pc+1 << endl;
    }
    if ((opcode != 'E') || ((opcode == 'D') && (jump == false))) {
      pc++;
    }
    jump = false;
  }
}

string convertdec(int decimal) {
  char byte[4];
  string output;
  int j;
  for (j = 0; j < 4; j++) {
    byte[j] = '0';
  }
  j = 0;
  while (decimal > 0) {
    if ((decimal % 16 >= 0) && (decimal % 16 <= 9)) {
      byte[j] = (decimal % 16) + 48;
    } else if (decimal % 16 >= 10) {
      byte[j] = (decimal % 16) + 55;
    }
    decimal = decimal / 16;
    j++;
  }
  output = "0000";
  for (j = 0; j < 4; j++) {
    if (byte[j] != '0') {
      output[3-j] = byte[j];
    }
  }
  return output;
}
