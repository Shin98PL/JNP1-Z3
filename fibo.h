#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <iostream>
#include <vector>

class Fibo
{
    private:
        std::vector<bool> v{};
        void norm();
    public:
        // Konstruktory
        Fibo();
        Fibo(const std::string &S);
        Fibo(const Fibo &F);

        template<typename number,
            typename = typename std::enable_if<
            std::is_integral<number>::value
            && !std::is_same<char, number>::value
            && !std::is_same<bool, number>::value>::type>
        Fibo(number n);


        // Operatory
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);
        Fibo & operator<<=(const unsigned long n);

        const Fibo operator&(const Fibo &rhs) const;
        const Fibo operator|(const Fibo &rhs) const;
        const Fibo operator^(const Fibo &rhs) const;
        const Fibo operator<<(const unsigned long n) const;

        // Porownania
        bool  operator==(const Fibo &rhs) const;
        bool  operator!=(const Fibo &rhs) const;
        bool  operator<(const Fibo &rhs) const;
        bool  operator>(const Fibo &rhs) const;
        bool  operator<=(const Fibo &rhs) const;
        bool  operator>=(const Fibo &rhs) const;

        // Strumien
        friend std::ostream& operator<<(std::ostream& os, const Fibo& f1);

        // Dlugosc
        size_t length() const;
};

const Fibo operator+(const Fibo &lhs, const Fibo &rhs);

const Fibo& Zero();
const Fibo& One();

#endif // FIBO_H
