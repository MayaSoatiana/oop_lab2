#include <bitString.h>
#include <dynamicArray.h>
#include <iostream>
#include <string.h>

bool BitString::validCharacter(char c) {
    return (c == '0' || c == '1');
}

BitString::BitString(): bitArray(){}

BitString::BitString(const size_t& arraySize, unsigned char defaultValue){  
    if (!validCharacter(defaultValue)){
        throw std::invalid_argument("default value incorrected");
    } 
    
    this->bitArray = DynamicArray(arraySize, defaultValue);
}

BitString::BitString(const std::initializer_list<unsigned char>& initialValues){
    for (const auto& c : initialValues){
        if (!validCharacter(c)){
            throw std::invalid_argument("invalid characters entered - only '0' and '1' allowed");
        } 
    }
    
    this->bitArray = DynamicArray(initialValues);
}  

BitString::BitString(const std::string& sourceString){ 
    if (sourceString.empty()){
        throw std::invalid_argument("Empty string");
    }
    for (char c : sourceString){
        if (!validCharacter(c)){
            throw std::invalid_argument("invalid characters entered");
        } 
    }

    this->bitArray = DynamicArray(sourceString); 
}
 
BitString::BitString(const BitString& other){
    this->bitArray = other.bitArray;
}
    
BitString::BitString(BitString&& other) noexcept{
    this->bitArray = std::move(other.bitArray);
}

// == Getters==
DynamicArray BitString::getBitArray(){
    return this->bitArray;
}

// ==Setters==
void BitString::setBitArray(DynamicArray newArray){
    this->bitArray = newArray;
}

BitString BitString::andOperation (const BitString& other){
    size_t maxLength = std::max(this->bitArray.getSize(), other.bitArray.getSize());
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray.getData()[i] == '1' && padded2.bitArray.getData()[i]=='1')){
            result.bitArray.insertAt(i, '1');
        }
        else{
            result.bitArray.insertAt(i, '0');
        }
    }
    return result;    
}

BitString BitString::orOperation(const BitString& other){
    size_t maxLength = std::max(this->bitArray.getSize(), other.bitArray.getSize());
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray.getData()[i] == '0' && padded2.bitArray.getData()[i]=='0')){
            result.bitArray.insertAt(i, '0');
        }
        else{
            result.bitArray.insertAt(i, '1');
        }
    }
    return result;    
}

BitString BitString::xorOperation(const BitString& other){
    size_t maxLength = std::max(this->bitArray.getSize(), other.bitArray.getSize());
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray.getData()[i] == padded2.bitArray.getData()[i])){
            result.bitArray.insertAt(i, '0');
        }
        else{
            result.bitArray.insertAt(i, '1');
        }
    }
    return result;
}

BitString BitString::notOperation(){
    BitString result(this->bitArray.getSize());

    for(size_t i = 0; i < this->bitArray.getSize(); i++){
        if(this->bitArray.getData()[i] == '0'){
            result.bitArray.insertAt(i, '1');
        }
        else{
            result.bitArray.insertAt(i, '0');
        }
    }
    return result;
}

void BitString::print() const{
    for(size_t i = 0; i < this->bitArray.getSize() ; i++){
        std::cout << this->bitArray.getData()[i];
    }
    std::cout << std::endl;
}

BitString::~BitString() noexcept{    
    if (bitArray.getData() != nullptr) {
        delete[] bitArray.getData();
        bitArray.setData(nullptr);
    }
    bitArray.setSize(0);
}

BitString BitString::padding(size_t length) const{
    if(bitArray.getSize() >= length){
        return *this;
    }
    BitString result(length, '0'); 

    size_t offset = length - this->bitArray.getSize();
    for(size_t i = 0; i < this->bitArray.getSize(); i++){
        result.bitArray.getData()[offset + i] = this->bitArray.getData()[i];
    }
    return result;
}

bool BitString::equals(const BitString& other) const {
    if (this->bitArray.getSize() != other.bitArray.getSize()) return false;
    for (size_t i = 0; i < bitArray.getSize(); i++) {
        if (bitArray.getData()[i] != other.bitArray.getData()[i]) return false;
    }
    return true;
}

std::string BitString::toString() const {
    if (bitArray.getData() == nullptr) {
        return "";
    }
    return std::string(bitArray.getData(), bitArray.getData() + bitArray.getSize());
}