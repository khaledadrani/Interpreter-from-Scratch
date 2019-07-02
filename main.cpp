#include <iostream>
#include "token.h"
#include "lexer.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// the version of this parser is good for simple cases, not complex cases, we have to revise it again


string express(int n){
/*	string cmd4="3+4*2/(1-5)^2^3";

	string cmd7="5*4+6+7";// we have a problem here
	string cmd8="main(x,y)+((5*4)/2+2)";
	string cmd="main(9/10*3,10)+1";
	string cmd1="1*2+3";
	string cmd2="7+2+3/5+1";
	string cmd3="max(10,10)+min(10)";
	//string text="max(10+fun(1)*2,1000,5000)";
	string text="max(10,10)^2+1";*/
	switch(n){
		case 0: {
			return "3+4*2/(1-5)^2^3";
			break;
		}
		case 1:{
			return "main(x): return x;";
			break;
		}
	default:
		{
			return "This is an empty expression";
			break;
		}
	}
	
	
}
int main(int argc, char** argv) {

   
    string text=express(0);
	lexer lex;
	
	lex.lexing(text);
	lex.show_result();
	lex.parse1();
	lex.show_output();
	
	

	return 0;
}
