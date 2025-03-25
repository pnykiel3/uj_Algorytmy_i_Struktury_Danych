//
// Created by pawelubuntu on 3/18/25.
//

#ifndef OPENHASH_H
#define OPENHASH_H
#include <iostream>
#include "setlinked.h"
#define M 5

class openHash {

  private:
    int size;
    setLinked<int>* table[M]{};
    setLinked<int>* table2[M]{};
    bool tab2_even;
    setLinked<char>* tableChar[M]{};
    setLinked<std::string>* tableString[M]{};

    static int hash(const int value){
        return value % M;
    }

 public:
   explicit openHash(int a) {
       while (a < 1 || a > 4) {
           std::cout << "Niepoprawna wartość: " << a << std::endl;
           std::cout << "Podaj wartość [1-4]: ";
           std::cin >> a;
       }
       size = 0;

       switch (a) {
           case 1:
               for (int i = 0; i < M; i++) {
                   table[i] = new setLinked<int>();
               }
               break;
           case 2:
                for (int i = 0; i < M; i++) {
                    table2[i] = new setLinked<int>();
                }
                tab2_even = false;
                break;
           case 3:
                for (int i = 0; i < M; i++) {
                    tableChar[i] = new setLinked<char>();
                }
                break;
           case 4:
               for (int i = 0; i < M; i++) {
                   tableString[i] = new setLinked<std::string>();
               }
           default:
               break;
        }
   }

    ~openHash() {
         for (int i = 0; i < M; i++) {
             delete table[i];
             delete tableChar[i];
         }
    }

   void makeHash1(const int value) {
       const int index = hash(value);
       table[index]->insert(value);
       size++;
   }

    void makeHash2(const int value) {
       if (isEmpty(table2)) {
           if (value % 2 == 0) tab2_even = true;
       }
       if ( (value % 2 == 0 && !tab2_even) || (value % 2 == 1 && tab2_even) ) {
          std::cout << "Niepoprawna wartość: " << value << std::endl;
       }
       const int index = hash(value);
       table2[index]->insert(value);
       size++;
   }


    void makeHashChar(const char value) {
        static int index = static_cast<int>(value) % M;
        tableChar[index]->insert(value);
        size++;
    }

    void makeHashWord(const std::string& value) {
        static int index = hash( static_cast<int>(value[0]) + static_cast<int>(value[1]) );
        tableString[index]->insert(value);
        size++;
    }

    void delHash1(const int value) const {
       static int bucket = hash(value);
       table[bucket]->remove(value);
   }

    void delHash2(const int value) const {
       static int bucket = hash(value);
       table2[bucket]->remove(value);
   }

    void delHashChar(const char value) const {
       static int bucket = hash(static_cast<int>(value));
       tableChar[bucket]->remove(value);
   }

    void delHashWord(const std::string& value) const {
       static int bucket = hash( static_cast<int>(value[0]) + static_cast<int>(value[1]) );
       tableString[bucket]->remove(value);
   }


    static bool isEmpty(setLinked<int>* a[]) {
       for (auto i : a) {
           if (i -> isEmpty()) return true;
       }
         return false;
   }




  };


#endif //OPENHASH_H
