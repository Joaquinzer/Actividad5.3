#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <fstream>
#include <thread>
#include <ctime>
#include <mutex>
#include <vector>

using namespace std;

set<char> nums = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
set<char> letras = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a',
 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H',
'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};
set<char> signos = {'=', '*', '(', '+', '-', ')', '^', '/'};

class NUMS{
private:
  int Estado;
  string res;
  string residuo;
public:
  int getEstado(){return Estado;}
  string getRes(){return res;}
  void Estado0(char c){
    if(nums.find(c) != nums.end()){
      Estado = 2;
      res = res+c;
    }else if(c == '-' || c == '+'){
      Estado = 1;
      res = res+c;
      residuo = residuo + c;
    }else if(c == '.'){
      Estado = 3;
      res = res+c;
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
  void Estado1(char c){
    if(nums.find(c) != nums.end()){
      Estado = 2;
      res = res+c;
      residuo = "";
    }else if(c == '.'){
      Estado = 3;
      res = res+c;
      residuo = "";
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
    void Estado2(char c){
      if(nums.find(c) != nums.end()){
        res = res+c;
      }else if(c == '.'){
        Estado = 3;
        res = res+c;
      }else{
        residuo = residuo + c;
        cout << res << " es numero entero" << endl;
        Estado = -1;
      }
  }
  void Estado3(char c){
    if(nums.find(c) != nums.end()){
      Estado = 4;
      res = res+c;
    }else if(c == 'E' || c == 'e'){
      Estado = 5;
      res = res+c;
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
  void Estado4(char c){
    if(nums.find(c) != nums.end()){
      res = res+c;
    }else if(c == 'E' || c == 'e'){
      Estado = 5;
      res = res+c;
    }else{
      residuo = residuo + c;
      cout << res << " es numero real" << endl;
      Estado = -1;
    }
  }
  void Estado5(char c){
    if(nums.find(c) != nums.end() || c == '-' || c == '+'){
      Estado = 4;
      res = res+c;
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
  string proceso(string entrada){
    char c;
    Estado = 0;
    for(int i = 0; i < entrada.size(); i++){
      c = entrada[i];
      switch(Estado){
        case -1 : residuo = residuo + c; break;
        case 0 : Estado0(c); break;
        case 1 : Estado1(c); break;
        case 2 : Estado2(c); break;
        case 3 : Estado3(c); break;
        case 4 : Estado4(c); break;
        case 5 : Estado5(c); break;
      }
    }
    if(Estado != -1){
      residuo = "";
      switch(Estado){
        case 2 : cout << res << " es numero entero" << endl; break;
        case 4 : cout << res << " es numero real" << endl; break;
      }
    }
    string rt = residuo;
    residuo = "";
    res = "";
    return rt;
  }
};

class VARS{
private:
  int Estado;
  string res;
  string residuo;
public:
  void Estado0(char c){
    if(letras.find(c) != letras.end()){
      Estado = 1;
      res = res + c;
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
  void Estado1(char c){
    if(letras.find(c) != letras.end() || nums.find(c) != nums.end() || c == '_'){
      res = res + c;
    }else{
      residuo = residuo + c;
      cout << res << " es una variable" << endl;
      Estado = -1;
    }
  }
  string proceso(string entrada){
    char c;
    Estado = 0;
    for(int i = 0; i < entrada.size(); i++){
      c = entrada[i];
      switch(Estado){
        case -1 : residuo = residuo + c; break;
        case 0 : Estado0(c); break;
        case 1 : Estado1(c); break;
      }
    }
    if(Estado != -1){
      residuo = "";
      cout << res << " es una variable" << endl;
    }
    string rt = residuo;
    residuo = "";
    res = "";
    return rt;
  }
};


class SIGN{
private:
  int Estado;
  string res;
  string residuo;
public:
  void Estado0(char c){
    if(signos.find(c) != signos.end()){
      res = res + c;
      if(c == '='){
        cout << res << " es una asignacion" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '*'){
        cout << res << " es una multiplicacion" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '('){
        cout << res << " es un parentesis que abre" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '+'){
        cout << res << " es una suma" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '-'){
        cout << res << " es una resta" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == ')'){
        cout << res << " es un parentesis que cierra" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '^'){
        cout << res << " es una potencia" << endl;
        residuo = "";
        Estado = -1;
      }else if(c == '/'){
        Estado = 1;
      }
    }else{
      residuo = residuo + c;
      Estado = -1;
    }
  }
  void Estado1(char c){
    if(c == '/'){
      res = res + c;
      Estado = 2;
    }else{
      cout << res << " es una division" << endl;
      residuo = residuo + c;
      Estado = -1;
    }
  }
  void Estado2(char c){
    res = res + c;
  }
  string proceso(string entrada){
    char c;
    Estado = 0;
    for(int i = 0; i < entrada.size(); i++){
      c = entrada[i];
      switch(Estado){
        case -1 : residuo = residuo + c; break;
        case 0 : Estado0(c); break;
        case 1 : Estado1(c); break;
        case 2 : Estado2(c); break;
      }
    }
    if(Estado == 2){
      residuo = "";
      cout << res << " es un comentario" << endl;
    }
    string rt = residuo;
    residuo = "";
    res = "";
    return rt;
  }
};


void checkLine(string input){
    NUMS n;
    VARS v;
    SIGN s;
    string residuo;
    while(input != ""){
        char c = input[0];
        if(nums.find(c) != nums.end() || c == '-'){
          residuo = n.proceso(input);
          input = residuo;
        }
        if(letras.find(c) != letras.end()){
          residuo = v.proceso(input);
          input = residuo;
        }
        if(signos.find(c) != signos.end()){
          residuo = s.proceso(input);
          input = residuo;
        }
        if(c == ' '){
          input.erase(0,1);
        }
      }
}

void Paralel(string arch){
    ifstream infile(arch);
    mutex mtx;
    while(infile.good()){
        mtx.lock();
        string input;
        getline(infile, input);
        mtx.unlock();
        checkLine(input);
    }
}

int main(int argc, char const *argv[]) {
  ifstream data;
  string arch;
  string input;
  int countL = 0;

  cout << "Nombre del archivo : ";
  cin >> arch;
  data.open(arch);
  int startTimeS = clock();
  if(data.is_open()){
    cout << "secuencial: " << endl;
    while(getline(data, input)){
      checkLine(input);
      countL++;
    }
  }
  int endTimeS = clock();


  vector<thread> threads;
  int numT = 4;
  int Spread = countL/numT;
  cout << "paralelo: " << endl;
  int startTimeP = clock();
  for(int i = 0; i < Spread; i++){
      threads.emplace_back(Paralel, arch);
  }
  for(auto& t : threads){
      t.join();
  }
  int endTimeP = clock();
  cout << "Tiempo secuencial: " << (endTimeS - startTimeS)/double(CLOCKS_PER_SEC) << endl;
  cout << "Tiempo paralelo: " << (endTimeP - startTimeP)/double(CLOCKS_PER_SEC) << endl;
  return 0;
}


