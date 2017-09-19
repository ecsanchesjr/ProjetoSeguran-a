#include "DAO.hpp"

#include <exception>

DAO::DAO(string &user, string &key) : user(user)
{
    if (user.length() != 0 && key.length() != 0)
    { // se nenhuma for vazia
        if (user.length() >= 4 && user.length() <= 20)
        { // user entre 6 a 20 caracteres
            if (key.length() >= 6 && key.length() <= 20)
            {                                // key entre 4 a 20 caracteres
                objC = new Crypt(user, key); //verifica se a chave descifra o arquivo do user
            }
            else
            {
                throw InvalidKeyLength();
            }
        }
        else
        {
            throw InvalidUserLength();
        }
    }
    else
    {
        throw EmptyInputField();
    }
}

DAO::~DAO()
{
    delete objC;
}

bool DAO::isKeyValid() const
{
    return (isValid);
}

vector<pair<string, string>> DAO::getNamesAndLogin(string &key) const
{

    vector<pair<string, string>> list;
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
        pair<string, string> reg{node.child("name").child_value(), node.child("login").child_value()};
        list.push_back(reg);
    }
    return (list);
}

vector<string> DAO::getEntry(string &name, string &key) const
{
    if (key.length() != 0)
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
    else
    {
        throw EmptyInputField();
    }
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
    if (key.length() != 0)
    {
        {
            vector<pair<string, string>> allNames = getNamesAndLogin(key);
            bool alreadyExist = false;
            for (pair<string, string> reg : allNames)
            {
                if (reg.first.compare(itemName) == 0)
                {
                    alreadyExist = true;
                }
            }
            if (alreadyExist)
            {
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

        for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
        {
            lastId = node.attribute("id").as_int();
        }

        root.append_child("item").append_attribute("id") = lastId + 1;

        for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
        {
            if (node.attribute("id").as_int() == lastId + 1)
            {
                node.append_child("name").append_child(pugi::node_pcdata).set_value(itemName.c_str());
                node.append_child("login").append_child(pugi::node_pcdata).set_value(login.c_str());
                node.append_child("pass").append_child(pugi::node_pcdata).set_value(pass.c_str());
            }
        }

        xmlToString(data, doc.child("doc"));

        objC->setData(data, key);
    }
    else
    {
        throw EmptyInputField();
    }
}

void DAO::deleteEntry(string &itemName, string &key)
{
    if (key.length() != 0)
    {
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
        for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
        {
            string name = node.child("name").child_value();
            if (name.compare(itemName) == 0)
            {
                nodeToDelete = node;
                foundNode = true;
                break;
            }
        }
        if (foundNode)
        {
            root.remove_child(nodeToDelete);
            xmlToString(data, root);
            objC->setData(data, key);
        }
    }
    else
    {
        throw EmptyInputField();
    }
}

void DAO::modifyEntry(string &itemName, string &login, string &pass, string &key, string newItemName)
{
    if (key.length()!=0)
    {
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

        pugi::xml_node nodeToMod;
        bool foundNode = false;
        for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
        {
            string name = node.child("name").child_value();
            if (name.compare(itemName) == 0)
            {
                nodeToMod = node;
                foundNode = true;
                break;
            }
        }
        if (foundNode)
        {
            if(newItemName.length()!=0 && login.length()!=0){
                nodeToMod.child("name").text().set(newItemName.c_str());
                nodeToMod.child("login").text().set(login.c_str());
            }else{
                throw EmptyInputField();
            }
            if(!pass.length()==0){
                nodeToMod.child("pass").text().set(pass.c_str());
            }
            xmlToString(data, root);
            objC->setData(data, key);
        }
    }
    else
    {
        throw EmptyInputField();
    }
}

void DAO::deleteUser(string &key)
{
    if (key.length() != 0)
    {
        objC->deleteUser(key);
    }
    else
    {
        throw EmptyInputField();
    }
}

void DAO::xmlToString(string &data, pugi::xml_node root)
{
    data = "<doc>";
    for (pugi::xml_node node = root.child("item"); node; node = node.next_sibling("item"))
    {
        data += "<item id='";
        data += node.attribute("id").value();
        data += "'>";
        data += "<name>";
        data += node.child("name").child_value();
        data += "</name>";
        data += "<login>";
        data += node.child("login").child_value();
        data += "</login>";
        data += "<pass>";
        data += node.child("pass").child_value();
        data += "</pass>";
        data += "</item>";
    }
    data += "</doc>";
}

void DAO::createNewUser(string &user, string &key)
{
    if (user.length() != 0 && key.length() != 0)
    { // se nenhuma for vazia
        if (user.length() >= 4 && user.length() <= 20)
        { // user entre 6 a 20 caracteres
            if (key.length() >= 6 && key.length() <= 20)
            { // key entre 4 a 20 caracteres
                string data = "<doc></doc>";
                Crypt::createData(user, data, key);
            }
            else
            {
                throw InvalidKeyLength();
            }
        }
        else
        {
            throw InvalidUserLength();
        }
    }
    else
    {
        throw EmptyInputField();
    }
}

void DAO::changeUserKey(string &newKey, string &key)
{
    if (key.length() != 0 && newKey.length() != 0)
    {
        if (newKey.length() >= 4 && newKey.length() <= 20)
        {
            objC->changeKey(newKey, key);
        }
        else
        {
            throw InvalidKeyLength();
        }
    }
    else
    {
        throw EmptyInputField();
    }
}