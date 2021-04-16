#include <iostream>
#include <stack>

using namespace std;
bool isBalancedParantheses(string infix) {   //metod bu ama syntax error durumunda nereye ekleyeceğimiz önemli!
  stack<char> stack;
  if(infix == "()") {
     return false;	  
  }
  for(int i=0; i < infix.length(); i++) {
     	if(infix[i] == '(') {
			stack.push(infix[i]);
		} else if(infix[i] == ')') {
			if(stack.empty()) {
				return false;
			} else {
				stack.pop();
			}
		}  
  }
	return stack.empty() ? true:false;
}
bool isOperator(char c){
		if(c=='+' || c=='-' || c=='/' || c=='*'){
			return true;
		}
		else
			return false;
}
int precedence(char c){
	if(c=='*' || c=='/'){
		return 2;
	}
	else if(c=='+' || c=='-'){
		return 1;
	}
	else
		return -1;
}
string toPostfix(stack<char> s, string infix){
	string postfix;
	for(int i =0; i<infix.length();i++){
	
		if(infix[i]==' '){
			continue;
		}
		else if((infix[i] >= 'a' && infix[i]<='z')|| (infix[i]>= 'A' && infix[i]<='Z') || (infix[i]>='0' && infix[i]<='9' )){
			postfix+=infix[i];
			int k=i+1;
			while((infix[k] >= 'a' && infix[k]<='z')|| (infix[k]>= 'A' && infix[k]<='Z') || (infix[k]>='0' && infix[k]<='9' )){
				i=k;
				postfix+=infix[k];
				k++;

			
			}
			

		}

		else if(infix[i]== '('){
			s.push(infix[i]);
		}
		else if(infix[i]== ')'){
			while((s.top() != '(') && (!s.empty())){
				char temp = s.top();
				postfix += temp;
				s.pop();

			}
			if(s.top()=='('){
				s.pop();
			}
		}
		else if(isOperator(infix[i])){
			if(s.empty()){
				s.push(infix[i]);
			}
			else{
				if(precedence(infix[i])>precedence(s.top())){
					s.push(infix[i]);
				}
				else if((precedence(infix[i])>precedence(s.top()))&&(infix[i]=='^')){
					s.push(infix[i]);
				}
				else{
					while((!s.empty()) &&( precedence(infix[i])<= precedence(s.top()))){
						char a = s.top();
						postfix+=a;
						s.pop();

					}
					s.push(infix[i]);
				}
			}
		}


		postfix+=' ';

	}

	while(!s.empty()){
		
		postfix+=s.top();
		postfix+=' ';
		s.pop();
	}









	return postfix;
}


int main(){

string infix_first;
string postfix_last ;
getline(cin,infix_first);
cout<<infix_first;
stack<char> Stack;
postfix_last = toPostfix(Stack,infix_first);
cout<<postfix_last;
	}
