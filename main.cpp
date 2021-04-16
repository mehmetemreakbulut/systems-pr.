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
 using namespace std;

   int main() {
    ifstream dosyaokuma("file.my");
    ofstream dosyayazma("file.ll");
    cout << "; ModuleID = 'mylang2ir'\ndeclare i32 @printf(i8*, ...)\n@print.str = constant [4 x i8] c\"%d\\0A\\00\"\n";
    string satir;
    while(getline(dosyaokuma,satir)) {
    if(satir.find("while") != string::npos) {

    }else if(satir.find("if") != string::npos) {

    }else if(satir.find("print") != string::npos) {

    }else if(satir.find("choose") != string::npos) {

    }else if(satir.find("#") != string::npos) {
             continue;
    }else {

    	}
    }














   	return 0;
   }
