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

#endif // CUSTOMEXCEPTIONS_H
