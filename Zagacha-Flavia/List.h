#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

class ListException : public std::exception {
public:
    const char* what() const noexcept override {
        return "List operation failed";
    }
};

class DynamicArray {
private:
    int* data;
    int current_size;
    int max_capacity;

    void expandCapacity(int required_capacity);

public:
    explicit DynamicArray(int initial_capacity = 10);
    ~DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);

    int& operator[](int position);
    int getValue(int position) const;
    void setValue(int position, int value);

    void insertAt(int position, int value);
    void append(int value);
    void removeAt(int position);

    int size() const;

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
};

#endif