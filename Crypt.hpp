#ifndef CRYPT_H
#define CRYPT_H

#include <sys/types.h>
#include <dirent.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "aes.h"
#include "sha.h"
#include "pwdbased.h"
#include "eax.h"
#include "hex.h"

#include "customexceptions.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using CryptoPP::SecByteBlock;
using CryptoPP::AES;
using CryptoPP::PKCS5_PBKDF2_HMAC;
using CryptoPP::SHA256;
using CryptoPP::EAX;
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::byte;
using CryptoPP::StringSink;

class Crypt
{

  public:
    Crypt(string &, string &);

    //procurar o arquivo
    bool isUserValid();
    //ler o arquivo
    string getData(string &);
    //gravar o arquivo
    void setData(string &, string &);

    //deletar usuário se a senha for correta
    void deleteUser(string &);

    //criar um novo arquivo
    void static createData(string &, string &, string &);

    // mudar senha do usuário
    void changeKey(string &, string &);

  private:
    string userName;
    const static string fileExtension;
    const static string dirName;
    const static int keySize = 2 * AES::DEFAULT_KEYLENGTH;
    const static int iterations = 100;

    void static getDir(vector<string> &);

    // validar a senha do usuario
    bool validateUser(string &, string &);

    // ler arquivo encriptado
    string static readData(string &);

    // gerar key derivada da senha do usuario
    SecByteBlock static generateKey(string &);

    // retorna o texto decryptado, porém gera uma excecao em senha errada
    string static decryptate(SecByteBlock, string);

    // retorna se existe ou não usuário criado
    bool static userExists(string &);

    // retorna a string encriptada
    string static encryptate(SecByteBlock, string);
};

#endif
