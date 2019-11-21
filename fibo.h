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

        Fibo(unsigned long long n);

        const std::vector<bool> & getV() const;

        // Operatory
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);
        Fibo & operator<<=(const unsigned long n);


        // Strumien
        friend std::ostream& operator<<(std::ostream& os, const Fibo& f1);

        // Dlugosc
        size_t length() const;
};

const Fibo operator+(const Fibo &lhs, const Fibo &rhs);
const Fibo operator&(const Fibo &lhs, const Fibo &rhs);
const Fibo operator|(const Fibo &lhs, const Fibo &rhs);
const Fibo operator^(const Fibo &lhs, const Fibo &rhs);
const Fibo operator<<(const Fibo &lhs, const unsigned long n);

// Porownania
bool  operator==(const Fibo &lhs, const Fibo &rhs);
bool  operator!=(const Fibo &lhs, const Fibo &rhs);
bool  operator<(const Fibo &lhs, const Fibo &rhs);
bool  operator>(const Fibo &lhs, const Fibo &rhs);
bool  operator<=(const Fibo &lhs, const Fibo &rhs);
bool  operator>=(const Fibo &lhs, const Fibo &rhs);

const Fibo& Zero();
const Fibo& One();

#endif // FIBO_H
