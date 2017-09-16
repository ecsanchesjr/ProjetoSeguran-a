#ifndef CRYPT_H
#define CRYPT_H

#include <sys/types.h>
#include <dirent.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class Crypt{

public:

   Crypt(string&,string&);

   //procurar o arquivo
   bool isUserValid();
   //ler o arquivo
   string getData(string&) const;
   //gravar o arquivo
   void setData(string&,string&);

   //deletar usuário se a senha for correta
   void deleteUser(string&);

   //criar um novo arquivo
   void static createData(string& ,string& ,string&);

private:
   string fileName;
   bool isValid;

   void getDir(vector<string>&);
};

#endif