# mips-parser
A parser written in C that takes in a text file containing hexadecimal instructions and parses the outputted processed instructions in a .csv file.

# *Keynotes*:
-uses bit shifting, pointers, and command line arguments

-takes in text file of hexadecimal values delimited by the newline character

-To use run the executable from a cmd prompt, import hex instructions text file as an argument in command line

-not all instructions are supported in this build

-decoded.csv is an the output of hexInstructions.txt

# *Supported instructions* (from main.c):
#define ADD 0X20
#define ADDI 0X8
#define ADDIU 0X9
#define ANDI 0XC
#define BEQ 0X4
#define BNE 0X5
#define J 0X2
#define JAL 0X3
#define LBU 0X24
#define LHU 0X25
#define LL 0X30
#define LUI 0XF
#define LW 0X23
#define ORI 0XD
#define SLTI 0XA
#define SLTIU 0XB
#define SB 0X28
#define SC 0X38
#define SH 0X29
#define SW 0X2B
#define ADDU 0X21
#define AND 0X24
#define JR 0X8
#define NOR 0X27
#define OR 0X25
#define SLT 0X2A
#define SLTU 0X2B
#define SLL 0X0
#define SRL 0X2
#define SUB 0X22
#define SUBU 0X23
