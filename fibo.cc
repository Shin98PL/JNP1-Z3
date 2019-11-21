/* Trzecie zadanie z Języków i narzędzi programowania I 19/20
 * 2019-11-21
 * Damian Chańko i Andrzej Małek
 */
#include "fibo.h"
#include <vector>
#include <cassert>
using namespace std;

void Fibo::norm()
{
    if (this->v.size() == 0) return;
    //Dwa zera dla bezpieczenstwa na poczatku.
    this->v.push_back(false);
    this->v.push_back(false);

    for (unsigned i = this->v.size() - 1; i > 0; --i)
    // Pozbywamy się par postaci sąsiednich "aktywnych" fibitów od najbardziej
    // znaczących do najmniej.
    {
        for (unsigned j = i; this->v[j] == true && this->v[j - 1] == true;
            j += 2)
        // Jeżeli para fibitów this.v[j] i this.v[j - 1] tworzą ciąg "aktywnych"
        // fibitów zamieniamy je wzorem F(n) + F(n - 1) = F(n + 1). Zauważmy,
        // że nie mogłoby w takiej sytuacji zajść this.v[j + 1] == true, bo
        // albo w pierwszej pętli zostałoby to rozpatrzone wcześniej, dla
        // i o jeden większego, lub w kolejnych pętlach napis musiałby nie być
        // unormowany na pozycjach większych od aktualnego j.
        {
            this->v[j] = false;
            this->v[j - 1] = false;
            this->v[j + 1] = true;
        }
    }

    // Usuwanie nadmiarowych zer na początku.
    for (size_t last = this->v.size(); last > 0 && !this->v.back(); --last)
    {
        this->v.pop_back();
    }
}

Fibo::Fibo()
{
}

Fibo::Fibo(const string &val)
{
    if (val.empty() || val == "0") return;
    assert(val.front() != '0');
    bool proper = true;
    for (size_t i = 0; i < val.size() && proper; ++i)
    {
        if (val[i] != '0' && val[i] != '1') proper = false;
    }
    assert(proper);
    this->v = vector<bool>(val.size(), false);
    for(size_t i = 0; i < val.size(); ++i)
        if(val[val.size() - i - 1] == '1') v[i] = true;

    this->norm();
}


Fibo::Fibo(const Fibo & F)
{
    this->v = F.v;
}

const vector<bool> & Fibo::getV() const
{
    return this->v;
}

Fibo & Fibo::operator=(const Fibo &rhs)
{
    if (this != &rhs) this->v = rhs.v;
    return *this;
}

Fibo & Fibo::operator+=(const Fibo &rhs)
{
    // Bezpieczny margines z false przy dodawaniu.
    size_t overtake = 0;
    if (rhs.length() > this->length()) overtake = rhs.length() - this->length();
    for (size_t i = 0; i < overtake + 5; ++i) this->v.push_back(false);

    // Dodajemy od najmniej znaczących fibitów do najbardziej znaczących.
    for (size_t i = 0; i < this->v.size() && i < rhs.v.size(); ++i)
    {

        if (this->v[i] == false || rhs.v[i] == false)
        // Jeżeli nie ma "podwójnego fibitu" wstawiamy większy z dwóch.
        {
            this->v[i] = (this->v[i] || rhs.v[i]);
        }
        else
        // Gdy jest "podwójny fibit" :
        {
            for (size_t j = i; j != this->v.size();)
            // Pętlimy się po obliczonych wartościach w tył aż do momentu, gdy
            // nie będziemy mieli sytuacji "podwójnego fibitu". j wskazuje
            // pozycję w której musimy dodać fibit do obliczonej sumy.
            {
                if (this->v[j] == false)
                // Jeżeli musimy dodać fibit tam gdzie go nie ma, sprawa jest
                // prosta i pętla się kończy
                {
                    this->v[j] = true;
                    j = this->v.size();
                }
                else if (this->v[j + 1] == true)
                // Jeżeli znaleźliśmy się w sytuacji, gdzie fibit o pozycji
                // j + 1 jest obecny, możemy je zamienić na fibit o pozycji
                // j + 2. Zauważmy, że gdy pętla się rozpoczyna, z unormowania
                // this.v i wiedzy, że this.v[i] = true wynika, że powyższa
                // sytuacja nie zachodzi. Dla każdego następnego obrotu musiała
                // zajść chwilę wcześniej sytuacja this.v[j] == true,
                // this.v[j + 1] == false i j > 2, więc po wykonaniu
                // this.v[j] = false, this.v[j + 1] = true, j -= 2
                // mamy pewność, że this.v[j + 2] == 0 (tj. nie mamy ponownej
                // sytuacji "podwójnego fibitu").
                {
                    this->v[j + 1] = false;
                    this->v[j + 2] = true;
                    j = this->v.size();
                }
                else
                // W przeciwnym przypadku możemy zastosować wzór
                // 2F(n) = F(n + 1) + F(n - 2), przy uwzględnieniu przypadków
                // skrajnych.
                {
                    this->v[j] = false;
                    this->v[j + 1] = true;
                    if (j >= 2) j -= 2;
                    else
                    {
                        // Dla j == 0 wzór 2F(n) = F(n + 1) + F(n - 2) ma
                        // postać 2F(2) = F(3), a dla j == 1 mamy wzory
                        // 2F(3) = F(4) + F(2) oraz
                        // F(2) + 2F(3) = F(4) + F(3)
                        if (j == 1)
                        {
                            this->v[1] = this->v[0];
                            this->v[0] = !this->v[0];
                        }
                        j = this->v.size();
                    }
                }

            }
        }
    }
    this->norm();
    return *this;
}

const Fibo operator+(const Fibo &lhs, const Fibo &rhs)
{
    return Fibo(lhs) += rhs;
}

Fibo & Fibo::operator&=(const Fibo &rhs)
{
    for (size_t i = 0; i < this->v.size(); ++i)
    {
        if (i < rhs.v.size()) this->v[i] = this->v[i] & rhs.v[i];
        else  this->v[i] = false;
    }
    this->norm();
    return *this;
}

const Fibo operator&(const Fibo &lhs, const Fibo &rhs)
{
    return Fibo(lhs) &= rhs;
}

Fibo & Fibo::operator|=(const Fibo &rhs)
{
    while (this->v.size() < rhs.v.size()) this->v.push_back(false);
    for (size_t i = 0; i < rhs.v.size(); ++i) {
        this->v[i] = this->v[i] | rhs.v[i];
    }
    this->norm();
    return *this;
}

const Fibo operator|(const Fibo &lhs, const Fibo &rhs)
{
    return Fibo(lhs) |= rhs;
}

Fibo & Fibo::operator^=(const Fibo &rhs)
{
    while(this->v.size() < rhs.v.size()) this->v.push_back(false);
    for (size_t i = 0; i < rhs.v.size(); ++i) {
        this->v[i] = this->v[i] ^ rhs.v[i];
    }
    this->norm();
    return *this;
}

const Fibo operator^(const Fibo &lhs, const Fibo &rhs)
{
    return Fibo(lhs) ^= rhs;
}


Fibo & Fibo::operator<<=(const unsigned long n)
{
    for (unsigned long i = 0; i < n; ++i) this->v.push_back(false);
    for (size_t i = this->length() - n; i > 0; --i)
    {
        this->v[i + n - 1] = this->v[i - 1];
        this->v[i - 1] = false;
    }
    return *this;
}

const Fibo operator<<(const Fibo &lhs, const unsigned long n)
{
    return Fibo(lhs) <<= n;
}

bool operator==(const Fibo &lhs, const Fibo &rhs)
{
    if (lhs.length() != rhs.length()) return false;
    const vector<bool> lv = lhs.getV();
    const vector<bool> rv = rhs.getV();
    for (size_t i = 0; i < rv.size(); ++i) if (lv[i] != rv[i]) return false;
    return true;
}

bool operator!=(const Fibo &lhs, const Fibo &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Fibo &lhs, const Fibo &rhs)
{
    if (lhs.length() < rhs.length()) return true;
    if (lhs.length() > rhs.length()) return false;
    const vector<bool> lv=lhs.getV();
    const vector<bool> rv=rhs.getV();
    for (size_t i = rv.size(); i > 0; --i)
    {
        if (lv[i - 1] < rv[i - 1]) return true;
        if (lv[i - 1] > rv[i - 1]) return false;
    }
    return false;
}

bool operator>(const Fibo &lhs, const Fibo &rhs)
{
    return rhs < lhs;
}

bool operator<=(const Fibo &lhs, const Fibo &rhs)
{
    return !(lhs > rhs);
}


bool operator>=(const Fibo &lhs, const Fibo &rhs)
{
    return !(lhs < rhs);
}

ostream& operator<<(ostream& os, const Fibo& f1)
{
    string tmp;
    if(f1.length() == 0) tmp = "0";
    for (size_t i = f1.length(); i > 0; --i)
    {
        if (f1.v[i - 1] == true) tmp.push_back('1');
        else tmp.push_back('0');
    }
    os << tmp;
    return os;
}

size_t Fibo::length() const
{
    return this->v.size();
}

const Fibo & Zero(){
    static const Fibo* val0 = new Fibo();
    return *val0;
}

const Fibo & One(){
    static const Fibo* val1 = new Fibo(1);
    return *val1;
}
