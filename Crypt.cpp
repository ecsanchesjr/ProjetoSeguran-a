#include "Crypt.hpp"

const string Crypt::fileExtension = ".lock";
const string Crypt::dirName = "res";

Crypt::Crypt(string &name, string &key)
{
    userName = name;
    bool userFound = false;
    vector<string> listOfFiles;
    getDir(listOfFiles);

    for (string tmp : listOfFiles)
    {
        if (tmp.compare(userName + fileExtension) == 0)
        {
            userFound = true;
            if (!validateUser(userName, key))
            {
                throw InvalidKey();
            }
        }
    }

    if (!userFound)
    {
        throw UserNotFound();
    }
}

string Crypt::getData(string &key)
{ // retorna a string adiquirida a partir do arquivo xml
    if (validateUser(userName, key))
    {
        vector<string> data;
        {
            string temp, aux;
            int i = 0;
            ifstream inputStream("./" + dirName + "/" + userName + fileExtension);
            while (getline(inputStream, temp))
            {
                if (i == 0)
                {
                    data.push_back(temp);
                }
                else
                {
                    aux.append(temp);
                }
                i++;
            }
            data.push_back(aux);
        }
        // data ainda está encriptada
        data[1] = decryptate(generateKey(key), data[1]);
        return (data[1]);
    }
    else
    {
        throw InvalidKey();
    }
}

void Crypt::setData(string &data, string &key)
{

    ofstream outputStream("./" + dirName + "/" + userName + fileExtension);
    if (outputStream.is_open())
    {
        data = encryptate(generateKey(key), data);
        outputStream << hash<string>{}(data);
        outputStream << "\n";
        outputStream << data;
        outputStream.close();
    }
}

void Crypt::deleteUser(string &key)
{
    //se a chave for válida
    if (validateUser(userName, key))
    {
        string file = "./" + dirName + "/" + userName + fileExtension;
        remove(file.c_str());
    }
}

void Crypt::createData(string &user, string &data, string &key)
{
    string dir = "./" + dirName + "/", cmd = "mkdir " + dirName;
    if (opendir(dir.c_str()) == nullptr)
    {
        system(cmd.c_str());
        ofstream newFile("./" + dirName + "/" + user + fileExtension);
        data = encryptate(generateKey(key), data);
        newFile << hash<string>{}(data);
        newFile << "\n";
        newFile << data;
        newFile.close();
    }
    else
    {
        if (!userExists(user))
        {
            ofstream newFile("./" + dirName + "/" + user + fileExtension);
            data = encryptate(generateKey(key), data);
            newFile << hash<string>{}(data);
            newFile << "\n";
            newFile << data;
            newFile.close();
        }
        else
        {
            throw DuplicatedUser();
        }
    }
}

void Crypt::getDir(vector<string> &listOfFiles)
{
    DIR *dp;
    struct dirent *dirp;
    string dir = "./" + dirName;

    if ((dp = opendir(dir.c_str())) == NULL)
    {
        cout << "Cannot open dir..." << endl;
    }
    else
    {
        while ((dirp = readdir(dp)) != NULL)
        {
            listOfFiles.push_back(string(dirp->d_name));
        }
    }
    closedir(dp);
}

bool Crypt::validateUser(string &user, string &key)
{
    try
    {
        if(!validateIntegrity(readData(user))){
            throw FileIntegrityNotAssure();
        }
        decryptate(generateKey(key), readData(user)[1]);
        return (true);
    }
    catch (CryptoPP::Exception ex)
    {
        throw InvalidKey();
    }
}

vector<string> Crypt::readData(string &file)
{
    vector<string> data;
    string temp, aux("");
    int i = 0;
    ifstream inputStream("./" + dirName + "/" + file + fileExtension);
    while (getline(inputStream, temp))
    {
        if (i == 0)
        {
            data.push_back(temp);
        }
        else
        {
            aux.append(temp);
        }
        i++;
    }
    data.push_back(aux);

    return (data);
}

SecByteBlock Crypt::generateKey(string &key)
{
    SecByteBlock derivedKey(keySize);

    PKCS5_PBKDF2_HMAC<SHA256> kdf;
    kdf.DeriveKey(derivedKey.data(), derivedKey.size(),
                  0x00, (byte *)key.data(), key.size(),
                  NULL, 0x00, iterations);

    return (derivedKey);
}

string Crypt::decryptate(SecByteBlock derivedKey, string encryptedText)
{
    string output;
    EAX<AES>::Decryption decryptor;
    decryptor.SetKeyWithIV(derivedKey.data(), keySize / 2, derivedKey.data() + keySize / 2, keySize / 2);

    AuthenticatedDecryptionFilter df(decryptor, new StringSink(output));
    df.Put((byte *)encryptedText.data(), encryptedText.size());
    df.MessageEnd();

    return (output);
}

string Crypt::encryptate(SecByteBlock derivedKey, string dataText)
{
    string output;
    EAX<AES>::Encryption encryptor;
    encryptor.SetKeyWithIV(derivedKey.data(), keySize / 2, derivedKey.data() + keySize / 2, keySize / 2);

    AuthenticatedEncryptionFilter ef(encryptor, new StringSink(output));
    ef.Put((byte *)dataText.data(), dataText.size());
    ef.MessageEnd();

    return (output);
}

bool Crypt::userExists(string &userFile)
{
    vector<string> list;
    getDir(list);

    for (string c : list)
    {
        if (c.compare(userFile + fileExtension) == 0)
            return (true);
    }
    return (false);
}

void Crypt::changeKey(string &newKey, string &key)
{
    if (validateUser(userName, key))
    {
        encryptate(generateKey(newKey), getData(key));
    }
    else
    {
        throw InvalidKey();
    }
}

bool Crypt::validateIntegrity(vector<string> data)
{
    hash<string> hash;
    size_t hashTrans = hash(data[1]);
    size_t hashCode;
    istringstream sstream(data[0]);
    sstream >> hashCode;
    if(hashTrans == hashCode){
        return(true);
    }else{
        return(false);
    }
}