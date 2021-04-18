 #include "infixToPostfix.h"
 #include <iostream>                                                         
 #include <vector>                                                           
 #include <string>                                                           
 #include <algorithm>                                                        
 #include <fstream>                                                          
 #include <ostream>                                                          
 #include <map>                                                              
 #include <iterator>                                                         
 #include <sstream>                                                          
 #include <stack>                                                            
 #include <string.h>        
 #include <bits/stdc++.h>   
 #include <sstream>                                              
 using namespace std;
int temp=1;
 int startsWith(string buyukstring, string aranmasigereken) {
    return strncmp(buyukstring.c_str(), aranmasigereken.c_str(), aranmasigereken.size());
   }

 string spaceCanceller(string text){
    string res = "";
    for(int i=0; i<text.length(); i++){

        if(text[i]=='\t'){
            continue;
        }
        else if(text[i] != ' '){
            res += text[i];
        }
    }
    return res;
}
bool isCheckedParantheses(string infix) {
    stack<char> stack;
    infix = spaceCanceller(infix);
    if(infix.find("()") != string::npos) {
        return false;
    }

    if(infix == "()") {
        return false;
    }
    for(int i = 0; i < infix.length(); i++) {
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
string toPostfix(string infix){
    stack<char> s;
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
void ifhasequal(string satir2,std::vector<string> variables){
    //stringstream ss;
    int index = satir2.find("=");
        string variable = satir2.substr(0,index);
        variable = spaceCanceller(variable);

        string value = satir2.substr(index);
        value = spaceCanceller(value);
        value = toPostfix(value);
        
      
   
std::stringstream ss(value);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
    

    if(tokens.size()==1){

        if(find(variables.begin(), variables.end(), variable) != variables.end()){
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"store i32 "+tokens[0]+", i32* %"+variable+"\n";
            }
            else{
            
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            cout<<"store i32 %t"+to_string(temp)+", i32* %"+variable+"\n";
            temp++;
        }
        }
        else{
             if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"store i32 "+tokens[0]+", i32* %"+variable+"\n";
            }
            else{
            
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            cout<<"store i32 %t"+to_string(temp)+", i32* %"+variable+"\n";
            temp++;
        }
        }
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
    cout<<"store i32 %"+calculate.top()+", i32* %"+variable+"\n";
    calculate.pop();
    }

}
void printFind(string satir2,std::vector<string> variables){
 
        int index = satir2.find('(');
        int index2 = satir2.find(')');
        string statement = satir2.substr(index+1,index2-index-1);
        statement = spaceCanceller(statement);
        statement = toPostfix(statement);
     
        std::stringstream ss(statement);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
   

    if(tokens.size()==1){
       
        string isCond;
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"all i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 "<<tokens[0]<<" )\n";
            }
            else{
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            string a= "t"+to_string(temp);
            temp++;
            cout<<"call i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 %"<<a<<" )\n";
        }
        
        
        
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
   cout<<"call i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 %"<<calculate.top()<<" )\n";
    calculate.pop();
    }

    
    




    }

   int main() {
    
    stringstream ss;  
    bool wloop = false;
    bool ifin=false;
    vector<string> variables;
    ifstream dosyaokuma("file.my");
    ofstream dosyayazma("file.ll");
    cout << "; ModuleID = 'mylang2ir'\ndeclare i32 @printf(i8*, ...)\n@print.str = constant [4 x i8] c\"%d\\0A\\00\"\n";
    cout<<"define i32 @main() {\n";
    string satir;
    while(getline(dosyaokuma,satir)) {
    if(satir.find("=") != string::npos){
        int index = satir.find("=");
        string variable = satir.substr(0,index);
        variable = spaceCanceller(variable);
        if(find(variables.begin(), variables.end(), variable) != variables.end()){

        }
        else{
            variables.push_back(variable);
            cout<<"  %"+variable+" = alloca i32\n";
        }
    }
    
    
    }
    for(int i = 0;i<variables.size();i++){
        cout<<"  store i32 0, i32* %"+variables[i]+"\n";
    }
    ifstream dosyaokuma2("file.my");
    string satir2;
    while(getline(dosyaokuma2,satir2)){
        if(satir2.find("=")!= string::npos && wloop ==false){
        int index = satir2.find("=");
        string variable = satir2.substr(0,index);
        variable = spaceCanceller(variable);

        string value = satir2.substr(index);
        value = spaceCanceller(value);
        value = toPostfix(value);
        
      
   
std::stringstream ss(value);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
    

    if(tokens.size()==1){

        if(find(variables.begin(), variables.end(), variable) != variables.end()){
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"store i32 "+tokens[0]+", i32* %"+variable+"\n";
            }
            else{
            
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            cout<<"store i32 %t"+to_string(temp)+", i32* %"+variable+"\n";
            temp++;
        }
        }
        else{
             if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"store i32 "+tokens[0]+", i32* %"+variable+"\n";
            }
            else{
            
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            cout<<"store i32 %t"+to_string(temp)+", i32* %"+variable+"\n";
            temp++;
        }
        }
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
    cout<<"store i32 %"+calculate.top()+", i32* %"+variable+"\n";
    calculate.pop();
    }


              }
    else if(satir2.find("while") != string::npos){
        wloop = true;
        cout<<"br label %whcond\n\n";
        int index = satir2.find('(');
        int index2 = satir2.find(')');
        string statement = satir2.substr(index+1,index2-index-1);
        cout<<"whcond:\n";
        
        statement = spaceCanceller(statement);
        statement = toPostfix(statement);
     
        std::stringstream ss(statement);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
   

    if(tokens.size()==1){
       
        string isCond;
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"%t"+to_string(temp)+" = icmp ne i32 "+tokens[0]+", 0" +"\n";
                temp++;
            }
            else{
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            string a= "t"+to_string(temp);
            temp++;
            cout<<"%t"+to_string(temp)+" = icmp ne i32 %"+a+", 0" +"\n";
            isCond = "t"+to_string(temp);
            temp++;
        }
        cout<<"br i1 %"+isCond+", label %whbody, label %whend\n";
        
        
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
    string isCond;
    cout<<"%t"+to_string(temp)+" = icmp ne i32 %"+calculate.top()+", 0" +"\n";
    isCond="t"+to_string(temp);
     cout<<"br i1 %"+isCond+", label %whbody, label %whend\n";
    calculate.pop();
    }

    
    cout<<"whbody: \n";
    while(wloop){

        getline(dosyaokuma2,satir2);
        
        if(satir2.find("=")!= string::npos ){
            ifhasequal(satir2,variables);
        }
        else if(satir2.find("}")!= string::npos){
            wloop = false;
        }
        else if(satir2.find("print") != string::npos){
            printFind(satir2,variables);
        }

        
    }
    cout<<"br label %whcond\n\nwhend:\n\nret i32 0\n";
}

    else if(satir2.find("if") != string::npos){
        ifin = true;
        cout<<"br label %"<<"ifcond\n\n";
        int index = satir2.find('(');
        int index2 = satir2.find(')');
        string statement = satir2.substr(index+1,index2-index-1);
        cout<<"ifcond:\n";
        
        statement = spaceCanceller(statement);
        statement = toPostfix(statement);
     
        std::stringstream ss(statement);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
   

    if(tokens.size()==1){
       
        string isCond;
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"%t"+to_string(temp)+" = icmp ne i32 "+tokens[0]+", 0" +"\n";
                temp++;
            }
            else{
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            string a= "t"+to_string(temp);
            temp++;
            cout<<"%t"+to_string(temp)+" = icmp ne i32 %"+a+", 0" +"\n";
            isCond = "t"+to_string(temp);
            temp++;
        }
        cout<<"br i1 %"+isCond+", label %"<<"ifbody, label %"<<"ifend\n";
        
        
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
    string isCond;
    cout<<"%t"+to_string(temp)+" = icmp ne i32 %"+calculate.top()+", 0" +"\n";
    isCond="t"+to_string(temp);
     cout<<"br i1 %"+isCond+", label %"+"ifbody, label %"+"ifend\n";
    calculate.pop();
    }

    
    cout<<"ifbody: \n";
    while(ifin){

        getline(dosyaokuma2,satir2);
        
        if(satir2.find("=")!= string::npos ){
            ifhasequal(satir2,variables);
        }
        else if(satir2.find("}")!= string::npos){
            ifin = false;
        }
        else if(satir2.find("print") != string::npos){
            printFind(satir2,variables);
        }

        
    }
    cout<<"br label %"<<"ifcond\n\nifend:\n\nret i32 0\n";
}

    else if(satir2.find("print") != string::npos){
        cout<<"lopopopop"<<endl;
        int index = satir2.find('(');
        int index2 = satir2.find(')');
        string statement = satir2.substr(index+1,index2-index-1);
        statement = spaceCanceller(statement);
        statement = toPostfix(statement);
     
        std::stringstream ss(statement);
std::istream_iterator<std::string> begin(ss);
std::istream_iterator<std::string> end;
std::vector<std::string> tokens(begin, end);
//std::copy(tokens.begin(), tokens.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
   

    
   

    if(tokens.size()==1){
       
        string isCond;
            if(tokens[0][0]>='0' && tokens[0][0]<='9'){
                cout<<"all i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 "<<tokens[0]<<" )\n";
            }
            else{
            cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[0]+"\n";
            string a= "t"+to_string(temp);
            temp++;
            cout<<"call i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 %"<<a<<" )\n";
        }
        
        
        
    }
    else{
    stack<string> calculate;
    

    

    for(int i=0;i<tokens.size();i++){
        if(tokens[i]=="+" ||tokens[i] =="*" ||tokens[i]=="-"||tokens[i]=="/" ){
            
            if(tokens[i]=="+"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = add i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="*"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = mul i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="/"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
                

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = udiv i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
           else if(tokens[i]=="-"){
                string b= calculate.top();
                calculate.pop();
                string a = calculate.top();
                calculate.pop();
                string temp1,temp2;
               

                if((a[0]>='0' && a[0]<='9') || (a[0]=='t' &&(a[1]>='0' && a[1]<='9') )){
                    temp1=a;
                                    }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+a+"\n";
                temp1 = "%t"+to_string(temp);
                temp++;

                }
                
                if((b[0]>='0' && b[0]<='9') || (b[0]=='t' &&(b[1]>='0' && b[1]<='9') )){
                    temp2=b;
                }
                else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+b+"\n";
                temp2 = "%t"+to_string(temp);
                temp++;

                }

                
                cout<<"%t"+to_string(temp)+" = sub i32 "+temp1+", "+temp2+"\n";
                string temp3 = "t"+to_string(temp);
                calculate.push(temp3);
                temp++;
            }
        }
        else{

            if(tokens[i][0]>='0' && tokens[i][0]<='9'){
                calculate.push(tokens[i]);
            }
            else{
                cout<<"%t"+to_string(temp)+" = load i32* %"+tokens[i]+"\n";
            calculate.push("t"+to_string(temp));
            temp++;
            }
            
        }

    }
   cout<<"call i32 (i8*, ...)* @printf(i8* getelementptr ([4x i8]* @print.str, i32 0, i32 0), i32 %"<<calculate.top()<<" )\n";
    calculate.pop();
    }

    
    




    }


    
    }















   	return 0;
   }
