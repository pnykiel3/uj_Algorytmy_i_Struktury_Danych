//
// Created by pawelubuntu on 3/18/25.
//

#ifndef SETHASHED_H
#define SETHASHED_H
#include <iostream>
#include "setlinked.h"

template<typename T>
class SetHashed {
private:
    int size;
    setLinked<int>* table;
    int capacity;

    int hash(int value) const {
        return value % capacity;
    }

public:
    explicit SetHashed(int c = 10) {
        size = 0;
        capacity = c;
        table = new setLinked<int>[capacity];
        for (int i = 0; i < c; i++) {
            table[i] = setLinked<int>();
        }
    }

    ~SetHashed() {
        delete[] table;
    }

    bool insert(int value) {
        if (!this->contains(value)) {
            table[hash(value)].insert(value);
            size++;
            return true;
        } return false;
    }

    bool remove(int value) {
        if (this->contains(value)){
            table[hash(value)].remove(value);
            size--;
            return true;
        }
        return false;
    }

    bool contains(int value) const {
        int h = hash(value);
        return table[h].exists(value);
    }

    // suma AuB
    SetHashed sum (const SetHashed &other) const {
        int newCapacity = (capacity >= other.capacity) ? capacity : other.capacity;
        SetHashed result(newCapacity);
        for (int i = 0; i < capacity; i++) {
            for (Node<T>* a = table[i].getHead(); a; a = a -> getNext()) {
                result.insert(a->data);
            }
        }
        for (int i = 0; i < other.capacity; i++) {
            for (Node<T>* a = other.table[i].getHead(); a; a = a -> getNext()) {
                result.insert(a->data);
            }
        }
        return result;
    }

    // część wspólna A n B
    SetHashed intersection(const SetHashed &other) const {
        int newCapacity = (capacity >= other.capacity) ? capacity : other.capacity;
        SetHashed result(newCapacity);
        for (int i = 0; i < capacity; i++) {
            for (Node<T>* a = table[i].getHead(); a; a = a -> getNext()) {
                if (other.contains(a->data)) {
                    result.insert(a->data);
                }
            }
        }
        return result;
    }

    // A - B
    SetHashed difference(const SetHashed &other) const {
        int newCapacity = (capacity >= other.capacity) ? capacity : other.capacity;
        SetHashed result(newCapacity);
        for (int i = 0; i < capacity; i++) {
            for (Node<T>* a = table[i].getHead(); a; a = a -> getNext()) {
                if (!other.contains(a->data)) {
                    result.insert(a->data);
                }
            }
        }
        return result;
    }

    bool equals(const SetHashed &other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < capacity; i++) {
            for (Node<T>* a = table[i].getHead(); a; a = a->getNext()) {
                if (!other.contains(a->data)) {
                    return false;
                }
            }
        }
        return true;
    }

    void print() const {
        for (int i = 0; i < capacity; i++) {
            std::cout << "Bucket " << i << ":  ";
            table[i].print();
        }
    }

    int getSize() const {
        return size;
    }


};


#endif //SETHASHED_H
