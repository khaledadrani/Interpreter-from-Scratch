#include "token.h"


token::token()
{
	type="NONE";
	value="";
	
}


token::token(string t,string c)//:type(t),value(c)
{
	type=t;
	value=c;
}

void token::show(){
	
	
	cout<<type<<" "<<setw(5)<<value<<endl;
}

bool token::operator==(token& t){
	if(t.type==type && t.value==value) return true;
	return false;
}

token token::operator+(token& t){
	if(*this==t){
		if(type=="LITERAL" || type=="VARIABLE" )
		   return(token(type,value+t.value));	
		else if(type=="NONE")   return(token(t.type,value+t.value));
		else if(t.type=="NONE") return(token(type,value+t.value));
	}
    return (token("ERROR",""));
}

token token::operator=(token& t){
	
	return(token(t.type,t.value));
	
}

string token::assoc(){
	if(type=="OPERATOR"){
		if(value=="^") return "right";
		else if(value=="+" || value=="*" || value=="/" || value=="-") return "left";
	}
	else if(type=="FUNCTION"){
		return"right";
	}
	
	return "invalid associativity";
}

int token::prec(){
	if(type=="OPERATOR"){
		if(value=="^") return 4;
		else if(value=="*" || value=="/") return 3;
		else return 2;
	}
	else if(type=="FUNCTION" || type=="LEFTP" || type=="RIGHTP"){
		return 5;
	}
	return -1;
}
