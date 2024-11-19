#include "mystack.h"
#include <cassert>
#include <cmath>

int rpn(const std::vector<std::string>& input) {
    MyStack<int> stack;

    for (const auto& x : input) {
        // jesli jest symbolem to sprawdzam czy byly wczesniej conajmniej 2 liczby
        if (x == "+" || x == "-" || x == "*" || x == "/") {
            // Musimy mieć co najmniej dwa elementy na stosie
            if (stack.size() < 2) {
                throw std::invalid_argument("Błąd: Nie można wykonać działania. Zbyt mało argumentów.");
            }

            // Sciaga elementy ze stosu
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            if (x == "+") stack.push(a + b);
            else if (x == "-") stack.push(a - b);
            else if (x == "*") stack.push(a * b);
            else if (x == "/") {
                if (b == 0) {
                    throw std::domain_error("Błąd: Dzielenie przez zero.");
                }
                // obsluga zaokraglen
                double result = static_cast<double> (a) / b;
                stack.push(static_cast<int>(std::round(result)));
            }
        } else {
            // jesli jest liczba to konwertuje na int i dodaje na stos
            try {
                stack.push(std::stoi(x));
            } // jesli nie jest liczba to wyjatek
            catch (const std::exception&) {
                throw std::invalid_argument("Błąd: Nieprawidłowy wyraz \"" + x + "\".");
            }
        }
    }

    // Na końcu na stosie powinien być dokładnie jeden element
    if (stack.size() != 1) {
        throw std::invalid_argument("Błąd: Nieprawidłowe wyrażenie ONP.");
    }

    return stack.top();
}

int main() {
    // test
    std::vector<std::string> input1 { "3", "4", "+", "2", "*", "7", "/" }; // ((3 + 4) * 2) / 7 = 2
    std::vector<std::string> input2 { "5", "1", "2", "+", "4", "*", "+", "3", "-" }; // 5 + ((1 + 2) * 4) - 3 = 14
    std::vector<std::string> input3 { "-6", "+2", "/" }; // (-6) / (+2) = -3
    std::vector<std::string> input4 { "5", "2", "/" };
    std::vector<std::string> input5 { "5", "3", "7", "-", "2", "*", "3", "5", "1", "+", "*", "-", "*", "3", "-" }; // 5 * ((3 - 7) * 2 - (3 * (5 + 1))) - 3 = -123
    std::vector<std::string> input6 { "-3", "5", "+", "4", "2", "*", "-" }; // (-3 + 5) - (4 * 2) = -3
    std::vector<std::string> input7 { "1000", "500", "200", "+", "*", "10", "/" }; // 1000 * ( 500 + 200 ) / 10 = 70000
    std::vector<std::string> input8 { "100000", "50000", "50000", "+", "/", "4", "*", "2","-" }; // 100000 / ( 50000 + 50000 ) * 4 - 2 = 2
    std::vector<std::string> input9 { "5", "0", "/" }; // Dzieleni przez zero
    std::vector<std::string> input10 { "5", "+" }; // Zbyt mało argumentów


    try {
        assert(rpn(input1) == 2);
        assert(rpn(input2) == 14);
        assert(rpn(input3) == -3);
        assert(rpn(input4) == 3);
        assert(rpn(input5) == -133);
        assert(rpn(input6) == -6);
        assert(rpn(input7) == 70000);
        assert(rpn(input8) == 2);

        // Testy z błędami

        std::cout << "Testy wyjątków (z błędami w input):" << std::endl;

        try {
            rpn(input9); // dzielenie przez zero
        } catch (const std::domain_error& e) {
            std::cout << e.what() << std::endl;
        }

        try {
            rpn(input10); // za mało argumentów
        } catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "WYNIK TESTU RPN: Wszystkie testy zakończone pomyślnie!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << std::endl;
    }

    return 0;
}
