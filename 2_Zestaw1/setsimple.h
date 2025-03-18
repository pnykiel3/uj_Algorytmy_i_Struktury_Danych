#ifndef ZADANIEA_H
#define ZADANIEA_H

#include <iostream>

class setSimple {

  int N;
  bool *tab;

  public:
    setSimple(int size) {
      N = size;
      tab = new bool[N];

      for (int i = 0; i < N; i++) {
        tab[i] = false;
      }
    }

    setSimple() {
      N = 10000;
      tab = new bool[N];

      for (int i = 0; i < N; i++) {
        tab[i] = false;
      }
    }

    void insert(int value) {
      if (value < N) {
        tab[value] = true;
      }
    }

    void remove(int value) {
      if (value < N) {
        tab[value] = false;
      }
    }

    bool exists(int value) {
      if (value < N) {
        return tab[value];
      }
      return false;
    }

    setSimple sum (setSimple &other) {
      setSimple C(N);


      for (int i = 0; i < N; i++) {
        C.tab[i] = tab[i] || other.tab[i];
      }

      return C;
    }

  // Część wspólna (A ∩ B)
    setSimple intersection (setSimple &other) {
      setSimple C(N);

      for (int i = 0; i < N; i++) {
        C.tab[i] = tab[i] && other.tab[i];
      }

      return C;
    }

  // Różnica zbiorów (A - B)
    setSimple complement (setSimple &other) {
      setSimple C(N);

      for (int i = 0; i < N; i++) {
        C.tab[i] = tab[i] && !other.tab[i];
      }

      return C;
    }

    bool equals (setSimple &other) {

      if (N != other.N) {
        return false;
      }

      for (int i = 0; i < N; i++) {
        if (tab[i] != other.tab[i]) {
          return false;
        }
      }
      return true;
    }


    void print() {
      for (int i = 0; i < N; i++) {
        std::cout << i << ":     ";
        if (tab[i]) {
          std::cout << "true" << std::endl;
        } else {
          std::cout << "false" << std::endl;
      	}
      }
    }

  };


#endif //ZADANIEA_H
