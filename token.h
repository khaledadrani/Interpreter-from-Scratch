#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <vector>
#include <string>
#include <ctype.h>
#include <cstring>
#include<iomanip>
#include <stack>
#include<queue>
#include <deque>
using namespace std;
 

class token
{
	public:
		token();
		token(string,string);
	    string assoc();
	    int prec();
	   
		void  show();
		
		bool operator==(token&);
		token operator+(token&);
		token operator=(token&);
		
		friend class lexer;
	protected:
		string type;
		string value;
		
		
		
};

#endif
