#include "fibo.h"
#include<vector>
using namespace std;

void Fibo::norm()
{
    if (v.size() == 0) return;


    for (unsigned i = this.v.size() - 1; i > 0; --i)
    // Pozbywamy się par postaci sąsiednich "aktywnych" fibitów od najbardziej
    // znaczących do najmniej.
    {
        for (unsigned j = i; this.v[j] == true && this.v[j - 1] == true; j += 2)
        // Jeżeli para fibitów this.v[j] i this.v[j - 1] tworzą ciąg "aktywnych"
        // fibitów zamieniamy je wzorem F(n) + F(n - 1) = F(n + 1). Zauważmy,
        // że nie mogłoby w takiej sytuacji zajść this.v[j + 1] == true, bo
        // albo w pierwszej pętli zostałoby to rozpatrzone wcześniej, dla
        // i o jeden większego, lub w kolejnych pętlach napis musiałby nie być
        // unormowany na pozycjach większych od aktualnego j.
        {
            this.v[j] = false;
            this.v[j - 1] = false;
            this.v[j + 1] = true;
        }
    }

    // Usuwanie nadmiarowych zer na początku.
    auto largestDigit = this.v.begin();
    for (auto iter = this.v.begin(); iter != this.v.end(); ++iter)
    {
        if (*iter == true) largestDigit = iter;
    }
    this.v.erase(++largestDigit, this.v.end());
}

const vector<bool> & value()
{
    return this.v;
}

string & Fibo::to_string()
{
    string tmp(this.length(), '0');
    for (size_t i = 0; i < tmp.size(); ++i)
    {
        if (this.v[i] == true) tmp[i] = '1';
    }
    return tmp;
}

Fibo::Fibo()
{
    this.v = new vector<bool>();
}

Fibo::Fibo(string &val)
{
    unsigned i = val.size();
    while(val[i - 1] != '1' && i > 0) --length;

    this.v = new vector<bool>(i + 2, false);
    while (i > 0)
    {
        if (val[i - 1] == '1') this.v[i - 1] = true;
        --i;
    }

    this.norm();
}

Fibo::Fibo(Fibo F)
{
    this.v = new vector<bool>(F.const_v());
}

Fibo & Fibo::operator=(const Fibo &rhs)
{
    if (this != rhs) this.v = rhs.const_v();
    return this;
}

Fibo & Fibo::operator+=(const Fibo &rhs)
{
    // 5 by zachować bezpieczny margines z false dla norm() po dodaniu
    for (int i = 0; i < 5; ++i) this.v.push_back(false);
    const vector<bool> rhs_v = rhs.const_v();

    // Dodajemy od najmniej znaczących fibitów do najbardziej znaczących
    for (size_t i = 0; i < this.v.size() && i < rhs_v.size(); ++i)
    {

        if (this.v[i] == false || rhs_v[i] == false)
        // Jeżeli nie ma "podwójnego fibitu" wstawiamy większy z dwóch
        {
            this.v[i] = (this.v[i] || rhs_v[i]);
        }
        else
        // Gdy jest "podwójny fibit" :
        {
            for (size_t j = i; j != this.v.size();)
            // Pętlimy się po obliczonych wartościach w tył aż do momentu, gdy
            // nie będziemy mieli sytuacji "podwójnego fibitu". j wskazuje
            // pozycję w której musimy dodać fibit do obliczonej sumy.
            {
                if (this.v[j] == false)
                // Jeżeli musimy dodać fibit tam gdzie go nie ma, sprawa jest
                // prosta i pętla się kończy
                {
                    this.v[j] = true;
                    j = this.v.size();
                }
                else if (this.v[j + 1] == true)
                // Jeżeli znaleźliśmy się w sytuacji, gdzie fibit o pozycji
                // j + 1 jest obecny, możemy je zamienić na fibit o pozycji
                // j + 2. Zauważmy, że gdy pętla się rozpoczyna, z unormowania
                // this.v i wiedzy, że this.v[i] = true wynika, że powyższa
                // sytuacja nie zachodzi. Dla każdego następnego obrotu musiała
                // zajść chwilę wcześniej sytuacja this.v[j] == true,
                // this.v[j + 1] == false i j > 2, więc po wykonaniu
                // this.v[j] = false, this.v[j + 1] = true, j -= 2
                // mamy pewność, że this.v[j] == 0 (tj. nie mamy ponownej
                // sytuacji "podwójnego fibitu").
                {
                    this.v[j + 1] = false;
                    this.v[j + 2] = true;
                    j = this.v.size();
                }
                else
                // W przeciwnym przypadku możemy zastosować wzór
                // 2F(n) = F(n + 1) + F(n - 2), przy uwzględnieniu przypadków
                // skrajnych.
                {
                    this.v[j] = false;
                    this.v[j + 1] = true;
                    if (j >= 2) j -= 2;
                    else
                    {
                        // Dla j == 0 wzór 2F(n) = F(n + 1) + F(n - 2) ma
                        // postać 2F(2) = F(3), a dla j == 1 mamy wzory
                        // 2F(3) = F(4) + F(2) oraz
                        // F(2) + 2F(3) = F(4) + F(3)
                        if (j == 1)
                        {
                            this.v[1] = this.v[0];
                            this.v[0] = ~this.v[0];
                        }
                        j = this.v.size();
                    }
                }

            }
        }
    }
    this.norm();
}

Fibo & Fibo::operator&=(const Fibo &rhs)
{
    vector<bool> v = rhs.value();
    for (int i = 0; i < this.v.size(); i++)
    {
        if (v.size() <= i) this.v[i] = false;
        else this.v[i] &= v[i];
    }
    return this;
}

Fibo & Fibo::operator|=(const Fibo &rhs)
{
    vector<bool> v = rhs.value();
    while (this.v.size() < v.size()) this.v.push_back(false);
    for (int i = 0; i < v.size(); i++) this.v[i] |= v[i];
    this.norm();
    return this;
}

Fibo & Fibo::operator^=(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    while(this.v.size() < v.size()) this.v.push_back(false);
    for (int i = 0; i < v.size(); i++) this.v[i] ^= v[i];
    this.norm();
    return this;
}

bool  Fibo::operator==(const Fibo &rhs)
{
    vector<bool> v = rhs.value();
    if (this.length() != v.size()) return false;
    for (int i = 0; i < v.size(); ++v) if (this.v[i] != v[i]) return false;
    return true;
}

bool  Fibo::operator!=(const Fibo &rhs)
{
    return !(this == rhs);
}

bool  Fibo::operator<(const Fibo &rhs)
{
    vector<bool> v = rhs.value();
    if (this.length() < v.size()) return true;
    if (this.length() > v.size()) return false;
    for (int i = v.size() - 1; i >= 0; --i)
    {
        if (this.v[i] < v[i]) return true;
        if (this.v[i] > v[i]) return false;
    }
    return false;
}

bool  operator<=(const Fibo &rhs)
{
    return this < rhs || this == rhs;
}

bool  operator>(const Fibo &rhs)
{
    return !(this <= rhs);
}

bool  operator>=(const Fibo &rhs)
{
    return !(this < rhs);
}

friend ostream& operator<<(ostream& os, const Fibo& f1)
{
    os << f1.to_string();
    return os;
}

size_t Fibo::length()
{
    return this.v.size();
}

const & Fibo Zero(){
    static const Fibo* val0 = new Fibo();
    return *val0;
}

const & Fibo One(){
    static const Fibo* val1 = new Fibo(1);
    return *val1;
}


