/* Trzecie zadanie z Języków i narzędzi programowania I 19/20
 * 2019-11-21
 * Damian Chańko i Andrzej Małek
 */
#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <iostream>
#include <vector>
#include <cassert>

class Fibo
{
    private:
        // Wektor przechowujący zapis fibitowy liczby.
        std::vector<bool> v{};
        // Funkcja normalizująca zapis liczby w wektorze v, tzn. pozbywa się
        // sąsiednich jedynek oraz zbędnych zer.
        void norm();
    public:
        Fibo();
        // explicit w celu uniknięcia autokonwersji przy operatorach.
        explicit Fibo(const std::string &S);
        Fibo(const Fibo &F);

        template<typename number,
            typename = typename std::enable_if<
            std::is_integral<number>::value
            && !std::is_same<char, number>::value
            && !std::is_same<bool, number>::value>::type>
        Fibo(number n)
        {
            assert(n >= 0);
            this->v = std::vector<bool>();
            // Pusty vector jak zero.
            if(n > 0)
            {
                // Kolejne dwie liczby fibonacciego.
                number f1 = 0;
                number f2 = 1;
                // Liczba zawiera co najmniej jeden bit zapalony.
                this->v.push_back(false);
                // Szukamy najwiekszej liczby fibonacciego niewiekszej od n.
                while(n - f2 > f1)
                {
                    this->v.push_back(false);
                    std::swap(f1, f2);
                    if(f1 != 1) f2 += f1;
                    else f2=2;
                }
                // Podzial liczby n na liczby fibonacciego.
                for(size_t i = this->v.size(); i > 0; --i)
                {
                    if(n >= f2)
                    {
                        this->v[i - 1] = true;
                        n -= f2;
                }
                    f2 -= f1;
                    std::swap(f1, f2);
                }
                // Normalizacja.
                this->norm();
            }
        }

        // Funkcja przekazująca const & do v, dla operatorów poza klasą.
        const std::vector<bool> & getV() const;

        // Operatory przypisania.
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);

        template<typename number,
            typename = typename std::enable_if<
            std::is_integral<number>::value
            && !std::is_same<char, number>::value
            && !std::is_same<bool, number>::value>::type>
        Fibo & operator<<=(number n)
        {
            assert(n >= 0);
            for (number i = 0; i < n; ++i) this->v.push_back(false);
            for (size_t i = this->length() - static_cast<size_t>(n); i > 0; --i)
            {
                this->v[i + static_cast<size_t>(n) - 1] = this->v[i - 1];
                this->v[i - 1] = false;
            }
            return *this;
        }

        // Operator przesunięcia.
        template<typename number,
            typename = typename std::enable_if<
            std::is_integral<number>::value
            && !std::is_same<char, number>::value
            && !std::is_same<bool, number>::value>::type>
        const Fibo operator<<(number n) const
        {
            return Fibo(*this) <<= n;
        }


        // Wypisywanie na strumień.
        friend std::ostream& operator<<(std::ostream& os, const Fibo& f1);

        // Funkcja zwracająca długość zapisu liczby.
        size_t length() const;
};

// Operatory.
const Fibo operator+(const Fibo &lhs, const Fibo &rhs);
const Fibo operator&(const Fibo &lhs, const Fibo &rhs);
const Fibo operator|(const Fibo &lhs, const Fibo &rhs);
const Fibo operator^(const Fibo &lhs, const Fibo &rhs);

bool  operator==(const Fibo &lhs, const Fibo &rhs);
bool  operator!=(const Fibo &lhs, const Fibo &rhs);
bool  operator<(const Fibo &lhs, const Fibo &rhs);
bool  operator>(const Fibo &lhs, const Fibo &rhs);
bool  operator<=(const Fibo &lhs, const Fibo &rhs);
bool  operator>=(const Fibo &lhs, const Fibo &rhs);

// Funkcje zwracające stałe reprezentujące liczby fibonacciego F(0) i F(1).
const Fibo& Zero();
const Fibo& One();

#endif // FIBO_H
