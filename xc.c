#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

int token;  //current token
char *src, *old_src; //pointer to source code
int poolsize;	//default size of text/data/slack
int line;	//line number

int *text,
	*old_text,
	*stack;
char *data;

int *pc, *bp, *sp, ax, cycle;//virtual machine registers


//tokens and classes
enum {
	Num = 128, Fun, Sys, Glo, Loc, Id,
	Char, Else, Enum, If, Int, Return, Sizeof, While,
	Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

int token_val;
int *current_id,
	*symbols;

struct identifier {
	int token;
	int hash;
	char *name;
	int class;
	int type;
	int value;
	int Bclass;
	int Btype;
	int Bvalue;
}

void next(){

	char *last_pos;
	int hash;
	
	while(token = *src){
		++src	
		if(token = '\n'){
			++line;
		} else if (token == '#') {
			while(*src != 0 && *src != '\n'){
				src++;
			}
		}
	}
	return;
}

void expression(int level) {
	//TODO
}

void program() {
	next(); //get next token
	while(token >0) {
		printf("token is :%c\n", token);
		next();
	}
}

int eval() {
	int op, *tmp;
    while (1) {
        if (op == IMM)       {ax = *pc++;}                                     // load immediate value to ax
        else if (op == LC)   {ax = *(char *)ax;}                               // load character to ax, address in ax
        else if (op == LI)   {ax = *(int *)ax;}                                // load integer to ax, address in ax
        else if (op == SC)   {ax = *(char *)*sp++ = ax;}                       // save character to address, value in ax, address on stack
        else if (op == SI)   {*(int *)*sp++ = ax;}                             // save integer to address, value in ax, address on stack
		else if (op == PUSH) {*--sp = ax;}  								   //push
		else if (op == JMP)	 {pc = (int *)*pc;}							   // jump to the address
		
		else if (op == JZ)   {pc = ax ? pc + 1 : (int *)*pc;}
		else if (op == JNZ)	 {pc = ax ? (int *)*pc: pc + 1;}
		
		else if (op == CALL) {;}
		else if (op == RET) {;}
	}
	
	
	return 0;
}

int main(int argc, char **argv) {
	int i, fd;
	
	argc--;
	argv++;
	
	poolsize = 256*1024;
	line = 1;
	
	if((fd = open(*argv,0) < 0){
		printf("could not open open(%s)\n", *argv);
		return -1
	}
	
	if(!(src = old_src = malloc(poolsize))) {
		printf("could not malloc(%d) for source area\n"), poolsize);
	}
	
	//read the source file
	if((i = read(fd, src, poolsize-1)) <= 0){
		printf("read() returned %d\n", i);
		return -1;
	}
	
	src[i] = 0; //add EOF character
	close(fd);
	
	//allocate memory for virtual machine
	if(!(text = old_text = malloc(poolsize))) {
		printf("could not malloc(%d) for text area\n", poolsize);
	}
	if(!(data = malloc(poolsize))) {
		printf("could not malloc(%d) for data area\n", poolsize);
	}
	if(!(stack = malloc(poolsize))) {
		printf("could not malloc(%d) for stack area\n", poolsize);
		return -1;
	}
	
	memset(text, 0, poolsize);
	memset(data, 0, poolsize);
	memset(stack, 0, poolsize);
	
	bp = sp = (int *)((int)stack + poolsize);
	ax = 0;
	
	//instructions
	enum { LEA ,IMM ,JMP ,CALL,JZ  ,JNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PUSH,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };
	
	
	program();
	return eval();
}
