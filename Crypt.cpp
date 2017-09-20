#include "Crypt.hpp"

#include "basen.hpp"

const string Crypt::fileExtension = ".lock";
const string Crypt::dirName = "res";
const string Crypt::dirBackup = ".backup";
const int Crypt::keySize = 2 * AES::DEFAULT_KEYLENGTH;
const int Crypt::iterations = 1000;

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
            lastState = readData(userName);
            cout << endl;
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
                    temp = decodeFrom64(temp);
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

void Crypt::writeData(string &data, string &key, string &userName)
{
    ofstream outputStream("./" + dirName + "/" + userName + fileExtension);
    if (outputStream.is_open())
    {
        data = encryptate(generateKey(key), data);
        data = encodeTo64(data);
        outputStream << hash<string>{}(data);
        outputStream << "\n";
        outputStream << data;
    }
    outputStream.close();
    backupUserData(userName);
}

void Crypt::setData(string &data, string &key)
{
    if (validateUser(userName, key))
    {
        writeData(data, key, userName);
        lastState = readData(userName);
    }
    else
    {
        throw InvalidKey();
    }
}

void Crypt::deleteUser(string &key)
{
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
        writeData(data, key, user);
    }
    else
    {
        if (!userExists(user))
        {
            writeData(data, key, user);
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
        if (!validateIntegrity(lastState))
        {
            throw FileIntegrityNotAssured();
        }
        decryptate(generateKey(key), readData(user)[1]);
        return (true);
    }
    catch (CryptoPP::Exception ex)
    {
        throw InvalidKey();
    }
    return (false);
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
            temp = decodeFrom64(temp);
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

string Crypt::encodeTo64(string strangeText)
{
    string encodedText = "";

    bn::encode_b64(strangeText.begin(), strangeText.end(), std::back_inserter(encodedText));

    return (encodedText);
}

string Crypt::decodeFrom64(string encodedText)
{
    string strangeText = "";

    bn::decode_b64(encodedText.begin(), encodedText.end(), std::back_inserter(strangeText));

    return (strangeText);
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
        string data = getData(key);
        writeData(data, newKey, userName);
        lastState = readData(userName);
    }
    else
    {
        throw InvalidKey();
    }
}

bool Crypt::validateIntegrity(vector<string> data)
{
    hash<string> hash;
    string hashText = "", txt = "", hashDiskText = "";

    ifstream input2("./" + dirName + "/" + userName + fileExtension);
    int i = 0;
    while (getline(input2, txt))
    {
        if (i != 0)
        {
            hashText.append(txt);
        }
        else
        {
            hashDiskText.append(txt);
        }
        i++;
    }

    size_t hashNow = hash(hashText);
    size_t hashLast;
    size_t hashDisk;
    istringstream sstream(data[0]), sstream1(hashDiskText);
    sstream >> hashLast;
    sstream1 >> hashDisk;
    if (hashLast == hashNow && hashLast == hashDisk && hashDisk == hashNow)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

void Crypt::backupUserData(string &userName)
{
    cout << "escreveu" << endl;

    string dir = "./" + dirBackup + "/", cmd = "mkdir " + dirBackup;
    if (opendir(dir.c_str()) == nullptr)
    {
        system(cmd.c_str());
    }

    ifstream inputStream("./" + dirName + "/" + userName + fileExtension);
    ofstream outputStream("./" + dirBackup + "/" + userName + fileExtension);

    istreambuf_iterator<char> beginSource(inputStream);
    istreambuf_iterator<char> endSource;
    ostreambuf_iterator<char> beginDestination(outputStream);

    copy(beginSource, endSource, beginDestination);

    inputStream.close();
    outputStream.close();
}