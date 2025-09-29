#include <BitString.h>
#include <iostream>
#include <string.h>

bool BitString::validCharacter(char c) {
    return (c == '0' || c == '1');
}


BitString::BitString() : bitArray(nullptr), arraySize(0) {
    std::cout << "default constructor" << std::endl;
}

//defined size + default value
BitString::BitString(const size_t& arraySize, unsigned char defaultValue){  
    if (!validCharacter(defaultValue)){
        throw std::invalid_argument("default value incorrected");
    } 
    
    this->arraySize = arraySize;
    this->bitArray = new unsigned char[arraySize];

    for (size_t i = 0; i < arraySize; i++){
        this->bitArray[i] = defaultValue;
    }   
}

//initialised list
BitString::BitString(const std::initializer_list<unsigned char>& initialValues){
    for (const auto& c : initialValues){
        if (!validCharacter(c)){
            throw std::invalid_argument("invalid characters entered - only '0' and '1' allowed");
        } 
    }
    
    this->arraySize = initialValues.size();
    this->bitArray = new unsigned char[arraySize];
    
    size_t index = 0;
    for (const auto& value : initialValues) {
        bitArray[index++] = value;
    }
}  

// from a string
BitString::BitString(const std::string& sourceString){ 
    if (sourceString.empty()){
        throw std::invalid_argument("Empty string");
    }
    for (char c : sourceString){
        if (!validCharacter(c)){
            throw std::invalid_argument("invalid characters entered");
        } 
    }

    this->arraySize = sourceString.length();
    this->bitArray = new unsigned char[arraySize];

    for (size_t i = 0; i < sourceString.length(); i++){
        this->bitArray[i] = static_cast<unsigned char>(sourceString.at(i));
    }    
}

//copy contstructor 
BitString::BitString(const BitString& other){
    this->arraySize = other.arraySize;
    this->bitArray = new unsigned char[arraySize];

    for (size_t i = 0; i < arraySize; i++){
        this->bitArray[i] = other.bitArray[i];
    }  
}
    
// moving constructor
BitString::BitString(BitString&& other) noexcept{
    this->arraySize = other.arraySize;
    this->bitArray = other.bitArray;

    other.arraySize = 0;
    other.bitArray = nullptr;
}

// == Getters==
size_t BitString::getSize(){
    return this->arraySize;
}

unsigned char* BitString::getBitArray(){
    return this->bitArray;
}

// ==Setters==
void BitString::setSize(size_t newSize){
    this->arraySize = newSize;
}

void BitString::setBitArray(unsigned char* newArray){
    this->bitArray = newArray;
}

BitString BitString::andOperation (const BitString& other){
    size_t maxLength = std::max(this->arraySize, other.arraySize);
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray[i] == '1' && padded2.bitArray[i]=='1')){
            result.bitArray[i] = '1';
        }
        else{
            result.bitArray[i] = '0';
        }
    }
    return result;    
}

BitString BitString::orOperation(const BitString& other){
    size_t maxLength = std::max(this->arraySize, other.arraySize);
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray[i] == '0' && padded2.bitArray[i]=='0')){
            result.bitArray[i] = '0';
        }
        else{
            result.bitArray[i] = '1';
        }
    }
    return result;    
}

BitString BitString::xorOperation(const BitString& other){
    size_t maxLength = std::max(this->arraySize, other.arraySize);
    BitString padded1 = this->padding(maxLength);
    BitString padded2 = other.padding(maxLength);
    BitString result(maxLength);

    for(size_t i = 0; i < maxLength; i++){
        if((padded1.bitArray[i] == padded2.bitArray[i])){
            result.bitArray[i] = '0';
        }
        else{
            result.bitArray[i] = '1';
        }
    }
    return result;
}

BitString BitString::notOperation(){
    BitString result(this->arraySize);

    for(size_t i = 0; i < this->arraySize; i++){
        if(this->bitArray[i] == '0'){
            result.bitArray[i] = '1';
        }
        else{
            result.bitArray[i] = '0';
        }
    }
    return result;
}

void BitString::print() const{
    for(size_t i = 0; i < this->arraySize ; i++){
        std::cout << this->bitArray[i];
    }
    std::cout << std::endl;
}

BitString::~BitString() noexcept{
    // std::cout << "destructor" << std::endl;
    
    if (bitArray != nullptr) {
        delete[] bitArray;
        bitArray = nullptr;
    }
    arraySize = 0;
}

BitString BitString::padding(size_t length) const{
    if(this->arraySize >= length){
        return *this;
    }
    BitString result(length, '0'); 

    size_t offset = length - this->arraySize;
    for(size_t i = 0; i < this->arraySize; i++){
        result.bitArray[offset + i] = this->bitArray[i];
    }
    return result;
}

// Add comparison function for testing
bool BitString::equals(const BitString& other) const {
    if (arraySize != other.arraySize) return false;
    for (size_t i = 0; i < arraySize; i++) {
        if (bitArray[i] != other.bitArray[i]) return false;
    }
    return true;
}

// Add function to get as string for testing
std::string BitString::toString() const {
    return std::string(bitArray, bitArray + arraySize);
}