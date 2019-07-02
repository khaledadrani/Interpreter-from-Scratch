#include "lexer.h"

lexer::lexer()
{
	Literal_Buffer.type="LITERAL";
	Variable_Buffer.type="VARIABLE";
	Literal_Buffer.value="";
	Variable_Buffer.value="";
	Left_Buffer.type="LEFTP";
	Right_Buffer.type="RIGHTP";
	Left_Buffer.value="";
	Right_Buffer.value="";
	nb_var=0;
		nb_lit=0;
	nb_para=0;
		nb_paraL=0;
		nb_paraR=0;
		nb_comma=0;
		nb_func=0;
		bool function_call=false;
		nb_op=0;
		nb_sep=0;

}

lexer::~lexer(){
	for(int i=0;i<result.size();i++) delete result[i];
	
	result.clear();
	
}

bool lexer::tokenize(string cmd){
	
	bool validate=true;
	string text=cmd;
	
	
	
	for(int i=0;i<text.size();i++){
		
	    //char* ch
	    char ch=text[i];
		//strcpy(ch,element.c_str());
		string res=text.substr(i,1);
	    //cout<<"digit"<<endl;
		if(isdigit(ch)){
			result.push_back(new token("LITERAL",res));
			nb_lit++;
		} 
		
		else if(isalpha(ch) ){
			result.push_back(new token("VARIABLE",res));
			nb_var++;
		}

		else if(isOperator(ch)){
			result.push_back(new token("OPERATOR",res));
			nb_op++;
		} 
		else if(isLeftP(ch)) {
			result.push_back(new token("LEFTP",res));
			nb_paraL++;
		}
		else if(isRightP(ch)) {
			result.push_back(new token("RIGHTP",res));
			nb_paraR++;
		}
		else if(isComma(ch)){
			 result.push_back(new token("ARG_SEP",res));
			 nb_sep++;
		}
		else if(isDecim(ch)) result.push_back(new token("DECI_PT",res));

	}	
	
	return validate;
}


bool lexer::lexing(string text){
	
	cout<<"Start Lexing"<<endl;
	cout<<"//////////////////"<<endl;
	for(int i=0;i<text.size();i++){
		char ch=text[i];
		string res=text.substr(i,1);

		
		if(isdigit(ch) || isDecim(ch)) {
		
		Literal_Buffer.value+=res; 
		
        }
        else if(isalpha(ch)) {

        	Variable_Buffer.value+=res;
		}
		else if(isOperator(ch)){
	
			if(Literal_Buffer.value!=""){

				result.push_back(new token(Literal_Buffer));
				Literal_Buffer.value="";
			}
			else if(Variable_Buffer.value!=""){
	
				result.push_back(new token(Variable_Buffer));
				Variable_Buffer.value="";
				
			}
			result.push_back(new token("OPERATOR",res));
		}
		else if(isLeftP(ch)){
		
			if(Variable_Buffer.value!=""){
				
				result.push_back(new token("FUNCTION",Variable_Buffer.value));
				Variable_Buffer.value="";
			}
				result.push_back(new token("LEFTP",res));
			
		}
		
		else if(isRightP(ch)){
			if(Literal_Buffer.value!=""){
				result.push_back(new token(Literal_Buffer));
				Literal_Buffer.value="";
			}
			else if(Variable_Buffer.value!=""){
				result.push_back(new token(Variable_Buffer));
				Literal_Buffer.value="";
			}
			result.push_back(new token("RIGHTP",res));
		}
		else if(isComma(ch)){
			if(Literal_Buffer.value!=""){
				result.push_back(new token(Literal_Buffer));
				Literal_Buffer.value="";
			}
			else if(Variable_Buffer.value!=""){
				result.push_back(new token(Variable_Buffer));
				Variable_Buffer.value="";
				
			}
			result.push_back(new token("ARG_SEP",res));}
	   
		}
		
	
		if(Literal_Buffer.value!=""){
	
			result.push_back(new token(Literal_Buffer));
		}
		else if(Variable_Buffer.value!=""){

			result.push_back(new token(Variable_Buffer));
		}
		
cout<<"////////////"<<endl;
cout<<"END Lexing"<<endl;


}

void lexer::parse1(){
if(result.size()!=0){
		cout<<"Start Parsing--------------"<<endl;
	  for(int i=0;i<result.size();i++){
	  	//cout<<"///////////////////////// i  "<<i<<endl;
	  	if(result[i]->type=="LITERAL" || result[i]->type=="VARIABLE") {
	  		output.push(result[i]);
	  		cout<<" Literal or Variable pushed to the stac ";result[i]->show(); 
		  }
	    
	    
		else if(result[i]->type=="FUNCTION"){
			
			cout<<" Result "<<i<<" "; result[i]->show();
			stac.push(result[i]);
			stac.top()->show();
			scope_call=true;
			cout<<" FUNCTION CALL IS HERE"<<endl;
		}
		
		else if(result[i]->type=="ARG_SEP") {
			
		    //output.push(result[i]);	
	        while( (stac.empty()==false) && stac.top()->type!="LEFTP" ){
	        	cout<<" ARG SEPERATOR HERE CHECK ";stac.top()->show();
	        	
	            output.push(stac.top());
	            stac.pop();
	            if(stac.top()->type=="LEFTP") { 
	            	break;
				} 
			}


			     
		}
		else if(result[i]->type=="OPERATOR" ){
			cout<<"********OPERATOR  CHECK*********"<<endl;
		        
		        if(stac.empty()==false){
				cout<<"stac is not empty"<<endl;
				while((stac.top()->type=="OPERATOR" || stac.top()->type=="FUNCTION") && (result[i]->assoc()=="left" && result[i]->prec()<=stac.top()->prec()) || (result[i]->assoc()=="right" && result[i]->prec()<stac.top()->prec())){
					
					cout<<" Operator is pushed to the output "<<endl; stac.top()->show();
					output.push(stac.top());
					stac.pop();
					if(stac.empty()==true) break;
			     	}
					 	
				
				}
				stac.push(result[i]);
				cout<<" Operator has been pushed to the stac"<<endl; stac.top()->show();
				cout<<" END OPERATOR CHECK "<<endl;
		}
			
			
			
		
		else if(result[i]->type=="LEFTP") {
			stac.push(result[i]);
			cout<<"Left para is pushed to the stac"<<endl;
		}
		
		else if(result[i]->type=="RIGHTP") {
		
		        cout<<" Right para is found "<<endl;
		        cout<<" STAC IS EMPTY OR NO "<<endl; cout<<stac.empty();
		        cout<<" Is it different than left para? "; stac.top()->show();
		    	while( stac.empty()==false  ){
		    	if( stac.top()->type!="LEFTP" ){
		    		cout<<" Right para found"<<endl;
			        stac.top()->show();
				     output.push(stac.top());
				     stac.pop();
				}
			    
			
				else if( stac.top()->type=="LEFTP" ) {
				    
				    cout<<" We found a left para"<<endl;
					if(stac.empty()==false){
						stac.top()->show();
				        stac.pop();
					}
				   
				    if(scope_call==true){
				    	cout<<" We break function call"<<endl;
			    		stac.top()->show();
				        output.push(stac.top());
				        stac.pop();
				        scope_call=false;
				        cout<<" FUNCTION CALL IS DISABLED"<<endl;
				     }
				    break;
				}
				
	
			  }
			
			
		}
		cout<<" STAC EMPTINESS "; cout<<stac.empty();
		
	
	  /*
	  cout<<"Evolution of the stack"<<endl;
	  cout<<"stack emptiness "<<stac.empty()<<endl;
	  if(stac.empty()==false){
	  	cout<<"At the top of the stack we have "<<endl;
	  	stac.top()->show();
	  }
	  */
	  cout<<endl<<"/////////////////////////"<<endl;
      }
      
      cout<<"Check the stack for remaining operators or functions"<<endl;
	  while(stac.size()!=0 ){
	  	cout<<" Pushing the remaing operator or functions"<<stac.top()->type<<endl;
	  	token* t=stac.top();
	  	cout<<"token at the top of the stac "<<&t<<" "; t->show();
	  	stac.pop();
	  	if(t->type=="OPERATOR" || t->type=="FUNCTION") {
	  		cout<<"Token is OPERATOR OR FUNCTION"<<endl;
	  		output.push(t);
	  		cout<<" End Token is Operator or Function"<<endl;
		  }
	  	
	  	if(stac.empty()==true) break;
	  }
	
	
	}
	cout<<"---------------------------------DONE PARSING"<<endl;
	
}
	

/*
void lexer::parse(){
	if(result.size()!=0){
		cout<<"Start Parsing--------------"<<endl;
	  for(int i=0;i<result.size();i++){
	  	cout<<"Element i  "<<i<<endl;
	  	if(result[i]->type=="LITERAL" || result[i]->type=="VARIABLE" || result[i]->type=="ARG_SEP") {
	  		output.push(result[i]);
		  }
		  
		else if(result[i]->type=="LEFTP") {
			stac.push(result[i]);
			
		}
		else if(result[i]->type=="RIGHTP"){
			if(stac2.empty()==false){
				if(stac2.top()->type=="LEFTP"){
				stac2.pop();
			
				output.push(stac.top());
			    }
			}
			else output.push(result[i]);	
		}
		else if(result[i]->type=="OPERATPR" || result[i]->type=="FUNCTION"){
			if(stac.empty()==false){
				if(stac2.empty()==false){
					if(stac.top()->type=="LEFTP"){
						stac.push(result[i]);
					}
					//else don't write the operator or the function
				}
				else{
					while((stac.top()->type=="OPERATOR" || stac.top()->type=="FUNCTION") && (result[i]->assoc()=="left" && result[i]->prec()<=stac.top()->prec()) || (result[i]->assoc()=="right" && result[i]->prec()<stac.top()->prec())){
					
					output.push(stac.top());
					stac.pop();
					if(stac.empty()==true) break;
			     	}		
				}
				stac.push(result[i]);
			}
			
		}
		
    }
    while(stac.empty()==false){
    	cout<<"Read stac"<<endl;
    	output.push(stac.top());
    	stac.pop();
	}
}
}
		
*/		

		
		
		     

void lexer::show_result(){
	for(int i=0;i<result.size();i++) result[i]->show();
	
}

void lexer::show_output(){
	queue<token*> t=output;
	while(!t.empty()){
		t.front()->show();
		t.pop();
		//cout<<"here"<<endl;
	}
	
}

/*
	if(result.size()!=0){
		cout<<"Start Parsing--------------"<<endl;
	  for(int i=0;i<result.size();i++){
	  	cout<<"///////////////////////// i  "<<i<<endl;
	  	if(result[i]->type=="LITERAL" || result[i]->type=="VARIABLE") {
	  		//cout<<" Result "<<i<<" "; result[i]->show();
	  		//cout<<"Literal or variable added to the output"<<endl;
	  		output.push(result[i]);
	  		//cout<<" End add"<<endl;
	  		
	  		//output.front()->show();
		  }
	    
	    
		else if(result[i]->type=="FUNCTION"){
			
			cout<<" Result "<<i<<" "; result[i]->show();
			stac.push(result[i]);
			stac.top()->show();
		}
		
		else if(result[i]->type=="ARG_SEP") {
		    
		    output.push(result[i]);
		   // output.push(result[i]);
	        while(stac.size()!=0 && stac.top()->type=="OPERATOR" ){
	        //	cout<<"We have an arg seperator so we push everything "; result[i]->show();
	        	
	        	stac.top()->show();
	        //	cout<<"Now add operator to the output"<<endl;
	            output.push(stac.top());
	         //   cout<<"Now pop from the stac"<<endl;
	            stac.pop();
	            if(stac.top()->type=="LEFTP" || stac.empty()==true){ 
	           //    cout<<"We break in case stack is empty or left para"<<endl;
	            	break;
				} 
			}
			cout<<"End arg seperator check"<<endl;
			     
		}
		else if(result[i]->type=="OPERATOR" ){
			cout<<"********OPERATOR and Function CHECK*********"<<endl;
		        
		        if(stac.empty()==false){
				cout<<"stac is not empty"<<endl;
				while((stac.top()->type=="OPERATOR" || stac.top()->type=="FUNCTION") && (result[i]->assoc()=="left" && result[i]->prec()<=stac.top()->prec()) || (result[i]->assoc()=="right" && result[i]->prec()<stac.top()->prec())){
					
					cout<<"WHILE LOOP"<<endl;
					cout<<"At the top of the stack "<<endl; stac.top()->show();
					cout<<"In the Result going to the stack "<<result[i]->assoc()<<" "<<result[i]->prec()<<" "; result[i]->show();
					cout<<"In the Stack Going to the output"<<stac.top()->assoc()<<" "<<stac.top()->prec()<<" "; stac.top()->show();
					output.push(stac.top());
					stac.pop();
					if(stac.empty()==true) break;
			     	}
					 	
				//cout<<"If it did not write, then it did not enter"<<endl;
				}
					stac.push(result[i]);
				//	cout<<"This operator is pushed to the stack "<<stac.top()->assoc()<<" "<<stac.top()->prec()<<" "; stac.top()->show();
				//	cout<<"**************End Operator Check***********"	<<endl;		
		}
			
			
			
		
		else if(result[i]->type=="LEFTP") {
			stac.push(result[i]);
			cout<<"Left para is pushed to the stac"<<endl;
		}
		
		else if(result[i]->type=="RIGHTP") {
			cout<<"We have a right parathese"<<endl;
			while( stac.empty()==false && (stac.top()->type=="OPERATOR" || stac.top()->type=="FUNCTION")&& stac.top()->type!="LEFTP"  ){
				cout<<"Operator at the top of the stack"<<stac.top()->type<<endl;
				output.push(stac.top());
				cout<<"Operator pushed"<<endl;
				stac.pop();
				cout<<"What is the problem?"<<endl;
				if( stac.empty()==true || stac.top()->type=="LEFTP" ) {
					cout<<"Get rid of the left paran or exit loop"<<endl;
					if(stac.empty()==false){
						stac.top()->show();
				        stac.pop();
					}
				    break;
				}
				cout<<"Passed the if"<<endl;
			}
		
		}
		
		else if(stac.top()->type=="FUNCTION"){
			output.push(stac.top());
			stac.pop();
		}
	  
	  cout<<"Evolution of the stack"<<endl;
	  cout<<"stack emptiness "<<stac.empty()<<endl;
	  if(stac.empty()==false){
	  	cout<<"At the top of the stack we have "<<endl;
	  	stac.top()->show();
	  }
	  
	  cout<<"/////////////////////////"<<endl;
      }
      
      cout<<"Check the stack for remaining operators or functions"<<endl;
	  while(stac.size()!=0 ){
	  	cout<<" Pushing the remaing operator or functions"<<stac.top()->type<<endl;
	  	token* t=stac.top();
	  	cout<<"token at the top of the stac "<<&t<<" "; t->show();
	  	stac.pop();
	  	if(t->type=="OPERATOR" || t->type=="FUNCTION") {
	  		cout<<"Token is OPERATOR OR FUNCTION"<<endl;
	  		output.push(t);
	  		cout<<" End Token is Operator or Function"<<endl;
		  }
	  	
	  	if(stac.empty()==true) break;
	  }
	/
	
	}
	cout<<"---------------------------------DONE PARSING"<<endl;
	
}*/
