#pragma once
#include <iostream>

class BitString{

public:
    //==CONSTRUCTORS==

    //default    
    BitString();
    //defined size + default value
    BitString(const size_t& arraySize, unsigned char defaultValue = '0');
    //initialised list
    BitString(const std::initializer_list<unsigned char>& initialValues);   
    // from a string
    BitString(const std::string& sourceString);
    //copy contstructor 
    BitString(const BitString& other); 
    // moving constructor
    BitString(BitString&& other) noexcept;

    // == Getters==
    size_t getSize();
    unsigned char* getBitArray();

    // ==Setters==
    void setSize(size_t newSize);
    void setBitArray(unsigned char* newArray);

    //==OPERATIONS==
    BitString andOperation(const BitString& other);
    BitString orOperation(const BitString& other);
    BitString xorOperation(const BitString& other);
    BitString notOperation();

    void print() const;

    //==DESTRUCTOR==
    ~BitString() noexcept;

    bool equals(const BitString& other) const ;
    std::string toString() const;

private:
    size_t arraySize;
    unsigned char* bitArray;

    bool validCharacter(char c);
    BitString padding(size_t length) const;
};