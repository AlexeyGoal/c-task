#include "List.h"
#include <cstring>
#include <algorithm>

DynamicArray::DynamicArray(int initial_capacity) : current_size(0) {
    max_capacity = std::max(initial_capacity, 10);
    data = new int[max_capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : current_size(other.current_size), max_capacity(other.max_capacity) {
    data = new int[max_capacity];
    std::copy(other.data, other.data + current_size, data);
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        current_size = other.current_size;
        max_capacity = other.max_capacity;
        data = new int[max_capacity];
        std::copy(other.data, other.data + current_size, data);
    }
    return *this;
}

void DynamicArray::expandCapacity(int required_capacity) {
    if (required_capacity <= max_capacity) return;

    int new_capacity = std::max(required_capacity, max_capacity * 2);
    int* new_data = new int[new_capacity];
    std::copy(data, data + current_size, new_data);

    delete[] data;
    data = new_data;
    max_capacity = new_capacity;
}

int& DynamicArray::operator[](int position) {
    if (position < 0 || position >= current_size) {
        throw ListException();
    }
    return data[position];
}

int DynamicArray::getValue(int position) const {
    if (position < 0 || position >= current_size) {
        throw ListException();
    }
    return data[position];
}

void DynamicArray::setValue(int position, int value) {
    if (position < 0 || position >= current_size) {
        throw ListException();
    }
    data[position] = value;
}

void DynamicArray::insertAt(int position, int value) {
    if (position < 0 || position > current_size) {
        throw ListException();
    }

    if (current_size == max_capacity) {
        expandCapacity(current_size + 1);
    }

    if (position < current_size) {
        std::move_backward(data + position, data + current_size, data + current_size + 1);
    }

    data[position] = value;
    current_size++;
}

void DynamicArray::append(int value) {
    insertAt(current_size, value);
}

void DynamicArray::removeAt(int position) {
    if (position < 0 || position >= current_size) {
        throw ListException();
    }

    std::move(data + position + 1, data + current_size, data + position);
    current_size--;
}

int DynamicArray::size() const {
    return current_size;
}

std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
    os << "Size: " << arr.current_size << ", Capacity: " << arr.max_capacity << " [";
    for (int i = 0; i < arr.current_size; ++i) {
        os << " " << arr.data[i];
    }
    os << " ]";
    return os;
}