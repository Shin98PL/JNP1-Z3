#ifndef FIBO_H
#define FIBO_H

#include <string>
#include <iostream>
#include <vector>

class Fibo
{
    private:
        std::vector<bool> v;
        void norm();
    protected:
        vector<bool> value();
    public:
        // Konstruktory
        Fibo();
        Fibo(std::string &val);
        Fibo(int n);
        Fibo(Fibo F);

        //Destruktor
        ~Fibo();

        //Operatory
        Fibo & operator=(const Fibo &rhs);
        Fibo & operator+=(const Fibo &rhs);
        Fibo & operator&=(const Fibo &rhs);
        Fibo & operator|=(const Fibo &rhs);
        Fibo & operator^=(const Fibo &rhs);
        Fibo & operator<<=(const int n);

        Fibo & operator+(const Fibo &rhs);
        Fibo & operator&(const Fibo &rhs);
        Fibo & operator|(const Fibo &rhs);
        Fibo & operator^(const Fibo &rhs);
        Fibo & operator<<(const int n);

        // Porownania
        bool  operator==(const Fibo &rhs);
        bool  operator!=(const Fibo &rhs);
        bool  operator<(const Fibo &rhs);
        bool  operator>(const Fibo &rhs);
        bool  operator<=(const Fibo &rhs);
        bool  operator>=(const Fibo &rhs);

        // Strumien
        friend ostream& operator<<(ostream& os, const Fibo& f1);

        //Dlugosc
        size_t length();
};

const Fibo Zero();
const Fibo One();

#endif // FIBO_H
