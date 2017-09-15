#include "Crypt.hpp"

Crypt::Crypt(string &name,string &key){
   fileName = name;
   vector<string> listOfFiles;
   isValid=false;
   getDir(listOfFiles);
   
   for(string tmp : listOfFiles){
      if(tmp.compare(fileName+".xml")==0){
         cout<<tmp<<endl;
         isValid=true;
      }
   }
}

bool Crypt::isUserValid(){
   return(isValid);
}

string Crypt::getData(string &key) const{
   if(isValid){
      ifstream inputStream("./res/"+fileName+".xml");
      string data((std::istreambuf_iterator<char>(inputStream)),(std::istreambuf_iterator<char>()));
      return(data);
   }else{
      return("");
   }
}

void Crypt::setData(string &data, string &key){
   if(isValid){
      ofstream outputStream("./res/"+fileName+".xml");
      if(outputStream.is_open()){
         outputStream<<data;
         outputStream.close();
      }
   }
}


void Crypt::deleteUser(string &key){
   //se a chave for válida
   string file = "./res/"+fileName+".xml";
   remove(file.c_str());  
}

void Crypt::createData(string &user, string &data, string &key){
   ofstream newFile("./res/"+user+".xml");
   newFile<<data;
   newFile.close();
}

void Crypt::getDir(vector<string> &listOfFiles){
   DIR *dp;
   struct dirent *dirp;
   string dir = "./res";

   if((dp = opendir(dir.c_str())) == NULL){
      cout<<"Cannot open dir..."<<endl;
   }else{
      while((dirp = readdir(dp)) != NULL){
         listOfFiles.push_back(string(dirp->d_name));
      }
   }
   closedir(dp);
}