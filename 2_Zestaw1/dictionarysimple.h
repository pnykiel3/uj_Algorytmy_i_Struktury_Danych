#ifndef DICTIONARYSIMPLE_H
#define DICTIONARYSIMPLE_H

#include <iostream>
#include <cstring>

#define N 1000

class dictionarysimple {
private:
    std::string data[N];
    int size;

    public:

      dictionarysimple() : size(0) {}

      bool exists(std::string str) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == str) {
                return true;
            }
        }
        return false;
	  }

       void insert(std::string str) {
        	if (!exists(str)) {
            	data[size] = str;
            	size++;
         	}
        }

       void remove(std::string str) {
        for (int i = 0; i < size; i++) {
            if (data[i] == str) {
                for (int j = i; j < size - 1; j++) {
                    data[j] = data[j + 1];
                }
                size--;
                return;
                }
            }
        }



    // Wypisanie zawartości zbioru
    void print() const {
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << std::endl;
        }
    }

};

#endif // DICTIONARYSIMPLE_H