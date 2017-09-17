#include "Crypt.hpp"

Crypt::Crypt(string &name,string &key){
   fileName = name;
   bool userFound = false;
   vector<string> listOfFiles;
   getDir(listOfFiles);
   
   for(string tmp : listOfFiles){
      if(tmp.compare(fileName+".xml")==0){
         userFound = true;
      }
   }

   if(!userFound){
        throw UserNotFound();
   }
}

string Crypt::getData(string &key) const{ // retorna a string adiquirida a partir do arquivo xml

      ifstream inputStream("./res/"+fileName+".xml");
      string data((std::istreambuf_iterator<char>(inputStream)),(std::istreambuf_iterator<char>()));
      // data ainda está encriptada

      return(data);

}

void Crypt::setData(string &data, string &key){

      ofstream outputStream("./res/"+fileName+".xml");
      if(outputStream.is_open()){
         outputStream<<data;
         outputStream.close();
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

bool Crypt::validateUser(string &user, string &key){
    try{
        decryptate(generateKey(key), readEncrypted(user));
        return(true);
    }catch(CryptoPP::Exception ex){
        cout << "Caiu na exceção " << endl;
        throw InvalidKey();
    }
}

string Crypt::readEncrypted(string &file){
    ifstream inputStream("./res/"+fileName+".xml");
    string data((std::istreambuf_iterator<char>(inputStream)),(std::istreambuf_iterator<char>()));
    
    return(data);
}

SecByteBlock Crypt::generateKey(string &key){
    SecByteBlock derivedKey(keySize);

    PKCS5_PBKDF2_HMAC<SHA256> kdf;
    kdf.DeriveKey(derivedKey.data(), derivedKey.size(),
    0x00, (byte *)key.data(), key.size(),
    NULL, 0x00, iterations);

    return(derivedKey);
}

string Crypt::decryptate(SecByteBlock derivedKey, string encryptedText){
    string output;
    EAX<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(derivedKey.data(), keySize/2, derivedKey.data()+keySize/2, keySize/2);
    
    AuthenticatedDecryptionFilter df(decryptor, new StringSink(output));
    df.Put((byte *)encryptedText.data(), encryptedText.size());
    df.MessageEnd(); 

    return(output);
}
