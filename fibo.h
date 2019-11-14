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
    protected:
        const std::vector<bool> & value() const;
    public:
        // Konstruktory
        Fibo();
        Fibo(const std::string &S);
        Fibo(int n);
        Fibo(const Fibo &F);

        //Destruktor
        //~Fibo();

        //Operatory
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);
        Fibo & operator<<=(const int n);

        const Fibo operator+(const Fibo &rhs) const;
        const Fibo operator&(const Fibo &rhs) const;
        const Fibo operator|(const Fibo &rhs) const;
        const Fibo operator^(const Fibo &rhs) const;
        const Fibo operator<<(const int n) const;

        // Porownania
        bool  operator==(const Fibo &rhs) const;
        bool  operator!=(const Fibo &rhs) const;
        bool  operator<(const Fibo &rhs) const;
        bool  operator>(const Fibo &rhs) const;
        bool  operator<=(const Fibo &rhs) const;
        bool  operator>=(const Fibo &rhs) const;

        // Strumien
        friend std::ostream& operator<<(std::ostream& os, const Fibo& f1);

        //Dlugosc
        size_t length() const;
};

const Fibo& Zero();
const Fibo& One();

#endif // FIBO_H
