#include <iostream>
#include <utility>
#include "DAO.hpp"

using namespace std;

int main(){

   string user = "username3";
   string text = "test";
   string entry = "bla2";

   DAO::createNewUser(user,text);

   DAO objDAO(user,text);
   if(!objDAO.isKeyValid()){
      return(-1);
   }
   string itemName = "item1";
   string login = "login2";
   string pass = "pass1";
   objDAO.createNewEntry(itemName,login,pass,text);
   
   itemName = "item2";
   login = "login2";
   pass = "pass2";
   objDAO.createNewEntry(itemName,login,pass,text);

   itemName = "item2";
   login = "login2";
   pass = "pass2";
   objDAO.createNewEntry(itemName,login,pass,text);

   itemName = "item3";
   login = "login3";
   pass = "pass3";
   objDAO.createNewEntry(itemName,login,pass,text);

   for(pair<string,string> reg : objDAO.getNamesAndLogin(text)){
      cout<<"name: "<<reg.first<<" login: "<<reg.second<<endl;
   }
   
   objDAO.deleteEntry(itemName,text);

   for(pair<string,string> reg : objDAO.getNamesAndLogin(text)){
      cout<<"name: "<<reg.first<<" login: "<<reg.second<<endl;
   }

   itemName = "item2";
   login = "new@login";
   pass = "newPass";

   objDAO.modifyEntry(itemName,login,pass,text);
   objDAO.modifyEntry(itemName,login,pass,text,"item4");



   return(0);
}