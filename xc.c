#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

int token;  //current token
char *src, *old_src; //pointer to source code
int poolsize;	//default size of text/data/slack
int line;	//line number

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
	
	program();
	return eval();
}