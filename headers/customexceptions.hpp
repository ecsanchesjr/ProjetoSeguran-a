#ifndef CUSTOMEXCEPTIONS_HPP
#define CUSTOMEXCEPTIONS_HPP

#include <exception>

class InvalidKey : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Invalid User Key";
    }
};

class UserNotFound : public std::exception{
public:
    virtual const char* what() const throw(){
        return "User Not Found";
    }
};

class DuplicatedUser : public std::exception{
public:
    virtual const char* what() const throw(){
        return "User Already Exists";
    }
};

class EmptyInputField : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Empty Input Field, check the fields and try again";
    }
};

class DuplicatedEntry : public std::exception{
public:
    virtual const char* what() const throw(){
        return "An entry with this name already exists";
    }   
};

class InvalidKeyLength : public std::exception{
public:
    virtual const char* what() const throw(){
        return "The key length must have beetween 6 and 20 characters.";
    }
};

class InvalidUserLength : public std::exception{
public:
    virtual const char* what() const throw(){
        return "The username length must have beetween 4 and 20 characters.";
    }
};

class FileIntegrityNotAssured : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Integrity of the vault file not warranted, you may have suffered a hacker attack!\n"
               "Please change your passwords!";
    }
};



#endif // CUSTOMEXCEPTIONS_H
