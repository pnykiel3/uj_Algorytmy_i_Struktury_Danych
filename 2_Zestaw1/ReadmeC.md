| **Kategoria**               | **setLinked (lista wiązana)**                                                                 | **setSimple (tablica)**                                                                       |
|------------------------------|-----------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| **Struktura danych**         | Lista wiązana z uporządkowanymi elementami.                                                   | Tablica o stałym rozmiarze (`MAX_SIZE = 10M`).                                                |
| **Rozmiar**                  | Dynamiczny (ograniczony pamięcią systemową).                                                  | Stały (maksymalnie `10M` elementów).                                                          |
| **Złożoność operacji**       | - `insert`: O(n) (sprawdzenie duplikatu + wstawienie w odpowiednie miejsce).<br>- `exists`: O(n) (liniowe przeszukiwanie).<br>- `remove`: O(n). | - `insert`: O(1) (jeśli brak duplikatu).<br>- `exists`: O(n).<br>- `remove`: O(n) (wyszukiwanie + zamiana z ostatnim elementem). |
| **Pamięć**                   | Większy narzut (wskaźniki + dynamiczna alokacja).                                             | Mniejszy narzut (tylko dane), ale z góry alokuje pamięć dla `MAX_SIZE`.                       |
| **Kolejność elementów**      | Zachowuje kolejność wstawiania/sortowanie.                                                    | Traci kolejność przy usuwaniu (zamiana z ostatnim elementem).                                 |
| **Duże zbiory**              | Wolniejsze operacje (przejście przez całą listę).                                             | Wydajne, jeśli mieszczą się w `MAX_SIZE`.                                                     |
| **Główne zalety**            | - Dynamiczny rozmiar.<br>- Zachowanie kolejności.<br>- Brak marnowania pamięci.               | - Szybkie wstawianie (O(1)).<br>- Stabilna wydajność dla dużych zbiorów.                      |
| **Główne wady**              | - Wolniejsze operacje dla dużych zbiorów.<br>- Większy narzut pamięciowy.                     | - Stały rozmiar (ograniczenie do 10M).<br>- Marnowanie pamięci przy małych zbiorach.          |
| **Optymalne zastosowania**   | - Częste modyfikacje.<br>- Kolejność/sortowanie ma znaczenie.<br>- Nieznany rozmiar zbioru.   | - Zbiory o znanym, stałym rozmiarze.<br>- Szybkie wstawianie.<br>- Kolejność nieistotna.      |


`exists` gdy ważna jest elastyczność, kolejność elementów lub pracujesz z danymi o nieprzewidywalnym rozmiarze.

`setSimple`  gdy zbiór jest duży (do 10M), szybkość wstawiania jest kluczowa, a kolejność nie ma znaczenia.