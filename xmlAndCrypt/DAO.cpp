#include "DAO.hpp"

DAO::DAO(string &user, string &key) : user(user)
{
   //verifica se a chave descifra o arquivo do user
   objC = new Crypt(user, key);
   isValid = objC->isUserValid();
}

bool DAO::isKeyValid() const
{
   return (isValid);
}

vector<string> DAO::getNames(string &key) const
{

   vector<string> list;
   string data = objC->getData(key);

   pugi::xml_document doc;
   pugi::xml_parse_result res = doc.load_string(data.c_str());

   {
      string result(res.description());
      if (result.compare("No error") != 0)
      {
         return (list);
      }
   }

   pugi::xml_node root = doc.child("doc");

   for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
   {
      list.push_back(node.child("name").child_value());
   }
   return (list);
}

vector<string> DAO::getEntry(string &name, string &key) const
{
   vector<string> entry;
   string data = objC->getData(key);

   pugi::xml_document doc;
   pugi::xml_parse_result res = doc.load_string(data.c_str());

   {
      string result(res.description());
      if (result.compare("No error") != 0)
      {
         return (entry);
      }
   }

   pugi::xml_node root = doc.child("doc");

   for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
   {
      if (((string)node.child("name").child_value()).compare(name) == 0)
      {
         entry.push_back(node.child("name").child_value());
         entry.push_back(node.child("login").child_value());
         entry.push_back(node.child("pass").child_value());
      }
   }
   return (entry);
}

vector<vector<string>> DAO::getAllEntrys(string &key) const
{
   vector<vector<string>> entrys;
   string data = objC->getData(key);

   pugi::xml_document doc;
   pugi::xml_parse_result res = doc.load_string(data.c_str());

   {
      string result(res.description());
      if (result.compare("No error") != 0)
      {
         return (entrys);
      }
   }

   pugi::xml_node root = doc.child("doc");

   for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
   {
      vector<string> entry;
      entry.push_back(node.child("name").child_value());
      entry.push_back(node.child("login").child_value());
      entry.push_back(node.child("pass").child_value());
      entrys.push_back(entry);
   }

   return (entrys);
}

void DAO::createNewEntry(string &itemName, string &login, string &pass, string &key)
{
   {
      vector<string> allNames = getNames(key);
      bool alreadyExist = false;
      for(string name : allNames){
         if(name.compare(itemName) == 0){
            alreadyExist = true;
         }
      }
      if(alreadyExist){
         return;
      }
   }
   string data = objC->getData(key);
   int lastId{0};
   pugi::xml_document doc;
   pugi::xml_parse_result res = doc.load_string(data.c_str());

   {
      string result(res.description());
      if (result.compare("No error") != 0)
      {
         return;
      }
   }

   pugi::xml_node root = doc.child("doc");

   for(pugi::xml_node node=root.child("item");node;node = node.next_sibling("item")){
      lastId = node.attribute("id").as_int();
   }

   root.append_child("item").append_attribute("id") = lastId+1;

   for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
   {
      if (node.attribute("id").as_int() == lastId + 1)
      {
         node.append_child("name").append_child(pugi::node_pcdata).set_value(itemName.c_str());
         node.append_child("login").append_child(pugi::node_pcdata).set_value(login.c_str());
         node.append_child("pass").append_child(pugi::node_pcdata).set_value(pass.c_str());
      }
   }

   xmlToString(data,doc.child("doc"));
   
   objC->setData(data,key);
}

void DAO::deleteEntry(string &itemName,string &key){
   string data = objC->getData(key);

   pugi::xml_document doc;
   pugi::xml_parse_result res = doc.load_string(data.c_str());

   {
      string result(res.description());
      if (result.compare("No error") != 0)
      {
         return;
      }
   }

   pugi::xml_node root = doc.child("doc");

   pugi::xml_node nodeToDelete;
   bool foundNode = false;
   for(pugi::xml_node node=root.child("item");node;node=node.next_sibling("item")){
      string name = node.child("name").child_value();
      if(name.compare(itemName) == 0){
         nodeToDelete = node;
         foundNode = true;
         break;
      }
   }
   cout<<foundNode<<endl;
   if(foundNode){
      root.remove_child(nodeToDelete);      
      xmlToString(data,root);
      objC->setData(data,key);
   }
}

void DAO::deleteUser(string &key){
   objC->deleteUser(key);
}

void DAO::xmlToString(string &data,pugi::xml_node root){
   data = "<doc>\n";
   for(pugi::xml_node node=root.child("item");node;node = node.next_sibling("item")){
      data+="\t<item id='";
      data+=node.attribute("id").value();
      data+="'>\n";
      data+="\t\t<name>";
      data+=node.child("name").child_value();
      data+="</name>\n";
      data+="\t\t<login>";
      data+=node.child("login").child_value();
      data+="</login>\n";
      data+="\t\t<pass>";
      data+=node.child("pass").child_value();
      data+="</pass>\n";
      data+="\t</item>\n";
   }
   data+="</doc>";
}

void DAO::createNewUser(string &user, string &key)
{
   string data = "<doc></doc>";
   Crypt::createData(user, data, key);
}