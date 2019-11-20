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
        Fibo(const unsigned long long n);
        Fibo(const Fibo &F);

        //Operatory
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);
        Fibo & operator<<=(const unsigned long n);

        const Fibo operator+(const Fibo &rhs) const;
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

const Fibo& Zero();
const Fibo& One();

#endif // FIBO_H
