#pragma once
#include <iostream>
#include <dynamicArray.h>

class BitString{

public:
    //==CONSTRUCTORS==
   
    BitString();
    BitString(const size_t& arraySize, unsigned char defaultValue = '0');
    BitString(const std::initializer_list<unsigned char>& initialValues);   
    BitString(const std::string& sourceString);

    BitString(const BitString& other); 
    BitString(BitString&& other) noexcept;

    // == Getters==
    DynamicArray getBitArray();

    // ==Setters==
    void setBitArray(DynamicArray newArray);

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
    DynamicArray bitArray;
    bool validCharacter(char c);

    BitString padding(size_t length) const;
};