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
        return "User Already Exist";
    }
};

class EmptyInputField : public std::exception{
public:
    virtual const char* what() const throw(){
        return "Empty Input Field";
    }
};

class InvalidKeyLength : public std::exception{
public:
    virtual const char* what() const throw(){
        return "The key length must be beetween 6 and 20.";
    }
};

class InvalidUserLength : public std::exception{
public:
    virtual const char* what() const throw(){
        return "The username length must be beetween 4 and 20.";
    }
};

#endif // CUSTOMEXCEPTIONS_H
