#ifndef DAO_HPP
#define DAO_HPP

#include <string>
#include <vector>
#include <utility>
#include "Crypt.hpp"
#include "pugi/pugixml.hpp"

using std::pair;
using std::vector;
using std::string;
using std::ostream;

class DAO{

public:
  //iniciaza a classe e seta o user
  DAO(string &, string &);
  ~DAO();

  //verifica se a senha do user está correta
  bool isKeyValid() const;

  //pegar o nome dos programas e sites que o usuário possui dados
  vector<pair<string,string>> getNamesAndLogin(string &) const;

  //pegar as informações do programa ou site escolhido
  vector<string> getEntry(string &,string &) const;

  //pegar as informações de todos
  vector<vector<string>> getAllEntrys(string &) const;

  //criar uma nova entrada para um usuário
  void createNewEntry(string &, string &, string &, string &);

  //deletar uma entrada para um usuário
  void deleteEntry(string &, string &);

  //modificar uma entrada
  void modifyEntry(string&,string&, string&, string& ,string="");

  //deletar um usuário
  void deleteUser(string &);

  //criar um novo arquivo para um novo usuário
  void static createNewUser(string &,string &);

  // alterar a senha do usuário
  void changeUserKey(string&, string&);
private:
  string user;
  Crypt *objC;
  bool isValid;

  void xmlToString(string&,pugi::xml_node);
};

#endif
