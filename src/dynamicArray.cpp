#include "dynamicArray.h"

// === КОНСТРУКТОР ===

DynamicArray::DynamicArray() : size(0), data(nullptr) {}

DynamicArray::DynamicArray(const size_t& arraySize, unsigned char defaultValue) {
    this->size = arraySize;
    this->data = new unsigned char[this->size];
    
    for (size_t i = 0; i < this->size; ++i) {
        this->data[i] = defaultValue;
    }
}

DynamicArray::DynamicArray(const std::initializer_list<unsigned char>& initialValues) {
    this->size = initialValues.size();
    this->data = new unsigned char[this->size];
    
    size_t index = 0;
    for (const auto& value : initialValues) {
        this->data[index++] = value;
    }
}

DynamicArray::DynamicArray(const std::string& sourceString) {
    this->size = sourceString.size();
    this->data = new unsigned char[this->size];
    
    for (size_t i = 0; i < this->size; ++i) {
        this->data[i] = static_cast<unsigned char>(sourceString[i]);
    }
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    this->size = other.size;
    this->data = new unsigned char[this->size];
    
    for (size_t i = 0; i < this->size; ++i) {
        this->data[i] = other.data[i];
    }
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept {
    this->size = other.size;
    this->data = other.data;

    other.size = 0;
    other.data = nullptr;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
    }
    return *this;
}

//== GETTERS ==
size_t DynamicArray::getSize() const{
    return this->size;
}
unsigned char* DynamicArray::getData()const{
    return this->data;
}

//==SETTERS == 
void DynamicArray::setSize(size_t newSize){
    this->size = newSize;
}
void DynamicArray::setData(unsigned char* newData){
    this->data = newData;
}

// === РЕАЛИЗАЦИЯ ОПЕРАЦИЙ ===

DynamicArray DynamicArray::add(const DynamicArray& other) {
    return DynamicArray(this->size + other.size, '1');
}

DynamicArray DynamicArray::remove(const DynamicArray& other) {
    if (this->size < other.size) {
        throw std::logic_error("Размер массива не может быть отрицательным");
    }
    
    this->size -= other.size;
    return *this;
}

bool DynamicArray::equals(const DynamicArray& other) const {
    return this->size == other.size;
}

void DynamicArray::insertAt(size_t index, const char toInsert){
    this->data[index] =static_cast<unsigned char> (toInsert);
}

std::ostream& DynamicArray::print(std::ostream& outputStream) {
    for (size_t i = 0; i < this->size; ++i) {
        outputStream << this->data[i];
    }
    return outputStream;
}

// === ДЕСТРУКТОРА ===
DynamicArray::~DynamicArray() noexcept {
    if (this->data != nullptr) {
        delete[] this->data;
        this->data = nullptr;
    }
    this->size = 0;
}