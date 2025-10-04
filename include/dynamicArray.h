#pragma once
#include <string>
#include <iostream>

class DynamicArray {
public:
    // === КОНСТРУКТОРЫ ===
    
    DynamicArray();
    DynamicArray(const size_t& arraySize, unsigned char defaultValue = 0);
    DynamicArray(const std::initializer_list<unsigned char>& initialValues);
    DynamicArray(const std::string& sourceString);
    
    // === КОПИРУЮЩИЕ И ПЕРЕМЕЩАЮЩИЕ ОПЕРАЦИИ ===
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    // === ОПЕРАЦИИ С МАССИВАМИ ===
    
    DynamicArray add(const DynamicArray& other);
    DynamicArray remove(const DynamicArray& other);
    bool equals(const DynamicArray& other) const;
    void insertAt(size_t index, const char toInsert);
    
    std::ostream& print(std::ostream& outputStream);

    // == GETTERS ==
    size_t getSize() const;
    unsigned char* getData() const;

    // == SETTERS ==
    void setSize(size_t newSize);
    void setData(unsigned char* newData);

    // === ДЕСТРУКТОР ===
    virtual ~DynamicArray() noexcept;

private:
    // === ДАННЫЕ-ЧЛЕНЫ ===   
    size_t size;           
    unsigned char* data;   
};