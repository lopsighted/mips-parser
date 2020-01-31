// Manuel Loera
// ml0896640@swccd.edu
// 0896640
// Project for Computer Architecture for instructor B.Smith
#include <stdio.h>
#include <stdlib.h>

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

void getOpcode(unsigned int mCode, int* opCode);
void getFuncCode(unsigned int mCode, char** funcCode);
void getInstruction(unsigned int mCode,  int opCode, char* funcCode, char **instruction);
void getFormat( int opCode, char* format);
void getRD(unsigned int mCode, int* rd);
void getRS(unsigned int mCode, int* rs);
void getRT(unsigned int mCode, int* rt);
void getShamt(unsigned int mCode, char format, char **shamt);
void getImmediate(unsigned int mCode, char format, char **imm);
void getEverything(unsigned int mCode, int *opCode, char **funcCode, char **instruction, char *format, int *rd, int *rs, int *rt, char **shamt, char **imm);
int main(int argc, char* argv [])
{
	int opCode, rd, rs, rt, opSum = 0;
	unsigned int mCode;
	char format;
	char *instruction, *shamt, *funcCode, *imm;
	FILE *inFile, *outFile;
	//printf("opening files...\n");
	inFile = fopen(argv[1], "r");
	//inFile = fopen("hexInstructions.txt", "r");
	//inFile == NULL ? printf("infile not opened\n") : printf("infile opened!\n");

	outFile = fopen("decoded.csv", "w");
	//outFile == NULL ? printf("outfile not opened\n") : printf("outfile opened!\n");

	fputs("Machine code,opcode (hex),func (hex),MIPS Inst,Format,rs,rt,rd,shamt,Imm (hex)\n", outFile);
	printf("Machine code,opcode (hex),func (hex),MIPS Inst,Format,rs,rt,rd,shamt,Imm (hex)\n");

	while (feof(inFile) == 0){
		if (outFile != NULL){
			//reads in machine code by line
			fscanf(inFile, "%x", &mCode);

			//calls all functions to set all pieces of MIPS instruction
			getEverything(mCode, &opCode, &funcCode, &instruction, &format, &rs, &rt, &rd, &shamt, &imm);

			//prints to console and writes file
			printf("%08x,%x,%s,%s,%c,%d,%d,%d,%s,%s\n", mCode, opCode, funcCode, instruction, format, rs, rt, rd, shamt, imm);
			fprintf(outFile, "%08x,%x,%s,%s,%c,%d,%d,%d,%s,%s\n", mCode, opCode, funcCode, instruction, format, rs, rt, rd, shamt, imm);
			opSum += opCode;
		}
		else
			printf("outFile wasn't opened.\n");
	}
	printf("OpCode Sum: %d", opSum);
	fclose(inFile);
	fclose(outFile);

	return 0;
}
//sets opcode by bit shift
void getOpcode(unsigned int mCode, int* opCode){
	*opCode = mCode >> 26;
}
//sets funcCode by bit shift,
void getFuncCode(unsigned int mCode, char** funcCode){
	*funcCode = malloc(10);
	if ((mCode >> 26) == 0){
		mCode = mCode << 26;
		mCode = mCode >> 26;
		snprintf(*funcCode, 10, "%x", mCode);
	}
	else {
		*funcCode = "-";
	}
}
//sets instruction using switch/case of const chars set at preprocessor
void getInstruction(unsigned int mCode,  int opCode, char* funcCode, char **instruction){
	char* mnemonic;
	if (opCode != 0){
		//CHECKING OPCODE INSTRUCTS
		switch (opCode){
			case ADDI:
				mnemonic = "addi";
				break;
			case ADDIU:
				mnemonic = "addiu";
				break;
			case ANDI:
				mnemonic = "andi";
				break;
			case BEQ:
				mnemonic = "beq";
				break;
			case BNE:
				mnemonic = "bne";
				break;
			case J:
				mnemonic = "j";
				break;
			case JAL:
				mnemonic = "jal";
				break;
			case LBU:
				mnemonic = "lbu";
				break;
			case LHU:
				mnemonic = "lhu";
				break;
			case LL:
				mnemonic = "ll";
				break;
			case LUI:
				mnemonic = "lui";
				break;
			case LW:
				mnemonic = "lw";
				break;
			case ORI:
				mnemonic = "ori";
				break;
			case SLTI:
				mnemonic = "slti";
				break;
			case SLTIU:
				mnemonic = "sltiu";
			case SB:
				mnemonic = "sb";
				break;
			case SC:
				mnemonic = "sc";
				break;
			case SH:
				mnemonic = "sh";
				break;
			case SW:
				mnemonic = "sw";
				break;
			default:
				mnemonic = "null";
				break;
		}
	}
	else {
		//CHECKING FUNCCODE INSTRUCTS
		int func = (int)strtol(funcCode, NULL, 16);
		switch (func){
			case ADD:
				mnemonic = "add";
				break;
			case ADDU:
				mnemonic = "addu";
				break;
			case AND:
				mnemonic = "and";
				break;
			case JR:
				mnemonic = "jr";
				break;
			case NOR:
				mnemonic = "nor";
				break;
			case OR:
				mnemonic = "or";
				break;
			case SLT:
				mnemonic = "slt";
				break;
			case  SLTU:
				mnemonic = "sltu";
				break;
			case  SLL:
				mnemonic = "sll";
				break;
			case  SRL:
				mnemonic = "srl";
				break;
			case  SUB:
				mnemonic = "sub";
				break;
			case  SUBU:
				mnemonic = "subu";
				break;
			default:
				mnemonic = "null";
				break;
		}
	}
	*instruction = mnemonic;
}
//sets format by checking OpCode
void getFormat(int opCode, char* format){
	if (opCode == 0)
		*format = 'R';
	else if (opCode == J || opCode == JAL)
		*format = 'J';
	else
		*format = 'I';
}
//sets RD by bit-shifting machine code
void getRD(unsigned int mCode, int* rd){
	mCode = mCode << 16;
	mCode = mCode >> 27;
	*rd = mCode;
	if (mCode < 0)
		*rd = ~mCode + 1;
}
//sets RS by bit-shifting machine code
void getRS(unsigned int mCode, int* rs){
	mCode = mCode << 6;
	*rs = mCode >> 27;
	if (*rs < 0)
		*rs = ~*rs + 1;
}
//sets RT by bit-shifting machine code
void getRT(unsigned int mCode, int* rt){
	mCode = mCode << 11;
	mCode = mCode >> 27;
	*rt = mCode;
	if (*rt < 0)
		*rt = (~mCode) + 1;
}
//sets shamt by bit-shifting machine code if format is 'R'
void getShamt(unsigned int mCode, char format, char **shamt){
	*shamt = malloc(5);
	if (format == 'R'){
		mCode = mCode << 21;
		mCode = mCode >> 27;
		snprintf(*shamt, 30, "%d", mCode);
	}
	else {
		*shamt = "-";
	}
}
//sets immediate by bit-shifting machine code if format is 'I'
void getImmediate(unsigned int mCode, char format, char **imm){
	*imm = malloc(10);
	if (format == 'I'){
		mCode = mCode << 16;
		mCode = mCode >> 16;
		sprintf(*imm, "%04x", mCode);
	}
	else
		sprintf(*imm, "-");
}
//calls all functions to set mips pieces in order to keep main function less clunky
void getEverything(unsigned int mCode, int *opCode, char **funcCode, char **instruction, char *format, int *rd, int *rs, int *rt, char **shamt, char **imm){
	getOpcode(mCode, opCode);
	getFuncCode(mCode, funcCode);
	getInstruction(mCode, *opCode, *funcCode, instruction);
	getFormat(*opCode, format);
	getRS(mCode, rs);
	getRT(mCode, rt);
	getRD(mCode, rd);
	getShamt(mCode, *format, shamt);
	getImmediate(mCode, *format, imm);
}
