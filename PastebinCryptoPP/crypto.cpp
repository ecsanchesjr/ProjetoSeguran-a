#include <string>
#include <iostream>
 
#include "cryptlib.h"
#include "osrng.h"
#include "sha.h"
#include "aes.h"
#include "hex.h"
#include "integer.h"
#include "pwdbased.h"
#include "modes.h"
 
 using namespace CryptoPP;
 
int main(int argc, char * argv[])
{
        using namespace std;
        using namespace CryptoPP;
        string password = "123";
        cout<<"Digite um pass: "<<endl;
        cin>>password;
        unsigned int iterations = 1000;
 
        AutoSeededX917RNG<AES> rng;
        /*      Gera uma seed usando o RNG proveniente do SO. 
                AES? Seria o tipo de rng que ele vai gerar para a cryp?
        */
        SecByteBlock iv(AES::BLOCKSIZE);
        rng.GenerateBlock(iv,iv.size());
 
        // See NIST SP 800-132 for detailed recommendations on length, generation and
        // format of the salt. This test program will just generate a random one. That
        // might not be sufficient for every application.
        SecByteBlock pwsalt(AES::DEFAULT_KEYLENGTH);
        rng.GenerateBlock(pwsalt,pwsalt.size());
 
        SecByteBlock derivedkey(AES::DEFAULT_KEYLENGTH);
       
        cout << "Password is " << password << endl;
        cout << "Deriving key from password:" << endl;
        PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
        pbkdf.DeriveKey(
                // buffer that holds the derived key
                derivedkey, derivedkey.size(),
                // purpose byte. unused by this PBKDF implementation.
                0x00,
                // password bytes. careful to be consistent with encoding...
                (byte *) password.data(), password.size(),
                // salt bytes
                pwsalt, pwsalt.size(),
                // iteration count. See SP 800-132 for details. You want this as large as you can tolerate.
                // make sure to use the same iteration count on both sides...
                iterations
                );
        cout << "Done" << endl;
 
 
        string message = "Enfin, il est nécessaire, vu les circonstances qui en commandent l’application,"
        " que le système soit d’un usage facile, ne demandant ni tension d’esprit, ni la connaissance d’une"
        " longue série de règles à observer.";
        string ciphertext;
 
        CBC_Mode<AES>::Encryption aesencryption(derivedkey,derivedkey.size(),iv);
        // encrypt message using key derived above, storing the hex encoded result into ciphertext
        StringSource encryptor(message,true,
                new StreamTransformationFilter(aesencryption, new HexEncoder( new StringSink(ciphertext)))
                );
        cout << endl;
        cout << "Mensagem: " << message << endl;
        cout << endl;
        // hex encode salt and IV for "transport"
        string hexsalt, hexiv;
        ArraySource saltEncoder(pwsalt,pwsalt.size(), true, new HexEncoder(new StringSink(hexsalt)));
        ArraySource ivEncoder(iv,iv.size(), true, new HexEncoder(new StringSink(hexiv)));
        cout << "Salt: " << hexsalt << endl;
        cout << "IV: " << hexiv << endl;
        cout << "Ciphertext: " << ciphertext << endl;
       
        // now recover the plain text given the password, salt, IV and ciphertext
        SecByteBlock recoveredkey(AES::DEFAULT_KEYLENGTH);
        SecByteBlock recoveredsalt(AES::DEFAULT_KEYLENGTH);
        StringSource saltDecoder(hexsalt,true,new HexDecoder(new ArraySink(recoveredsalt, recoveredsalt.size())));
        cout << "Re-deriving encryption key based on encoded values above." << endl;
        pbkdf.DeriveKey(recoveredkey, recoveredkey.size(), 0x00, (byte *) password.data(), password.size(),
                recoveredsalt, recoveredsalt.size(), iterations);
        cout << "Done." << endl;
        SecByteBlock recoverediv(AES::BLOCKSIZE);
        StringSource ivDecoder(hexiv,true,new HexDecoder(new ArraySink(recoverediv, recoverediv.size())));
        CBC_Mode<AES>::Decryption aesdecryption(recoveredkey, recoveredkey.size(), recoverediv);
        string recoveredtext;
        StringSource decryptor(ciphertext, true, new HexDecoder(
                new StreamTransformationFilter(aesdecryption, new StringSink(recoveredtext))
                ));
        cout << "Recovered plaintext value: " << recoveredtext << endl;
 
        return 0;
 
}