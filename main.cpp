#include <iostream>
#include <cassert>
#include <chrono>
#include <random>
#include "fibo.h"

using namespace std;

int main() {
    Fibo f;



    assert(f == Zero());
    assert(Fibo(f) == Zero());
    assert(Fibo("11") == Fibo("100"));
    assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
    assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
    assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
    assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
    assert((Fibo("101") << 3) == Fibo("101000"));

    f = One();
    f <<= 3;
    assert(f == Fibo("1000"));

    f = One();
    assert(f + Fibo("1") == Fibo("10"));
    assert(f == One());

    Fibo f1("101");
    Fibo f2 = Fibo("101");
    assert(f1 == f2);

    assert(Fibo("11").length() == 3); // 11 == 100

    std::cout << Fibo("11") << std::endl; // prints 100
    assert(Zero() < One());

    unsigned seed {static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count())};
    std::default_random_engine rng(seed);
    int counter = 0;

    int liczba_sumowan = 10000;

    for (int i = 0; i < liczba_sumowan; ++i)
    {
        unsigned long l = rng();
        unsigned long k = rng();
        Fibo fl(l);
        Fibo fk(k);
        Fibo fkl(k + l);
        if (fkl != fl + fk)
        {
            std::cout << "l     : " << l << '\n' << fl << '\n'
                      << "k     : " << k << '\n' << fk << '\n'
                      << "l + k : " << l + k << '\n' << fkl << '\n' << '\n';
            std::cout << (Fibo(l + k) ^ (Fibo(l) + Fibo(k))) << std::endl;
            std::cout << Fibo(l + k)<< std::endl;
            std::cout << Fibo(l) + Fibo(k) << std::endl << '\n';
            ++counter;
        }
    }

    std::cout << "Zle sumowania : " << counter << " z " << liczba_sumowan << std::endl;

    Fibo fib{};
    std::cout << fib << '\n';
    fib += 2;
    std::cout << fib << '\n';
    Fibo fib2{10};
    fib = fib2 + 10;
    std::cout << fib << '\n';
//    fib = 10 + fib2;
    std::cout << fib << '\n';
    fib = 3;
    std::cout << fib << '\n';
//    std::cout << (2 < fib) << '\n';
    std::cout << (fib > 2) << '\n';


}
