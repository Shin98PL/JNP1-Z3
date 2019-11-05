#include "fibo.h"
using namespace std;

Fibo::Fibo()
{
    this.v= new vector<bool>();
}
const & Fibo Zero(){
    static const Fibo* val0 = new Fibo();
    return *val0;
}

Fibo::Fibo(Fibo F)
{
    this.v= new vector<bool>(F.value());
}
size_t Fibo::length()
{
    return this.v.size();
}
