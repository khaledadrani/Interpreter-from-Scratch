#ifndef LEXER_H
#define LEXER_H
#include "token.h"

// the lexer class will be expanded later on.
class lexer
{
	public:
		lexer();    
		~lexer();
	    bool tokenize(string);
	    bool lexing(string);
	    void parse();
	    void parse1();
	    void show_result();
	    void show_output();
	    
	    
	protected:
		vector<token*> result;
		token Literal_Buffer; //nb buffer
		token Variable_Buffer; //letter buffer
		token Left_Buffer; //right parathenses buffer
		token Right_Buffer; //left parante buffer
		stack<token*> stac; // stac for postfix expressions during parsing
	
		queue<token*> output; // the result of the parsing is supposedly here
	        // these are various parameters I will be using during lexical analysis
		int nb_var;
		int nb_lit; 
		int nb_para;
		int nb_paraL;
		int nb_paraR;
		int nb_comma;
		int nb_func;
		int nb_op;
		int nb_sep;
		bool scope_call;
		
		
		
		
		
		// necessary functions for lexical analysis
		bool inline isComma(char ch){ return(ch==',');}
		bool inline isOperator(char ch){return(ch=='+' || ch=='*' || ch=='^' || ch=='-' || ch=='/');	}
		bool inline isLeftP(char ch){return(ch=='(');}
		bool inline isRightP(char ch){return (ch==')');}
		bool inline isDecim(char ch){return (ch=='.');	}
	
		
};

#endif
