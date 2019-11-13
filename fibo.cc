#include "fibo.h"
#include<vector>
using namespace std;

Fibo::Fibo()
{
    this.v= new vector<bool>();
}
const & Fibo Zero(){
    static const Fibo* val0 = new Fibo();
    return *val0;
}

const & Fibo One(){
    static const Fibo* val1 = new Fibo(1);
    return *val1;
}

Fibo::Fibo(Fibo F)
{
    this.v= new vector<bool>(F.value());
}

Fibo & Fibo::operator=(const Fibo &rhs)
{
    this.v=F.value();
    return this;
}

Fibo & Fibo::operator&=(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    for(int i=0;i<this.v.size();i++)
    {
        if(v.size()<=i)this.v[i]=false;
        else this.v[i]&=v[i];
    }
    return this;
}

Fibo & Fibo::operator|=(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    while(this.v.size()<v.size())this.v.push_back(false);
    for(int i=0;i<v.size();i++)this.v[i]|=v[i];
    this.v.norm();
    return this;
}
Fibo & Fibo::operator^=(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    while(this.v.size()<v.size())this.v.push_back(false);
    for(int i=0;i<v.size();i++)this.v[i]^=v[i];
    this.v.norm();
    return this;
}

size_t Fibo::length()
{
    return this.v.size();
}

bool  Fibo::operator==(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    if(this.length()!=v.size())return false;
    for(int i=0;i<v.size();++v)if(this.v[i]!=v[i])return false;
    return true;
}
bool  Fibo::operator!=(const Fibo &rhs)
{
    return !this==rhs;
}
bool  Fibo::operator<(const Fibo &rhs)
{
    vector<bool> v=rhs.value();
    if(this.length()<v.size())return true;
    if(this.length()>v.size())return false;
    for(int i=v.size()-1;i>=0;--i)
    {
        if(this.v[i]<v[i])return true;
        if(this.v[i]>v[i])return false;
    }
    return false;
}
bool  operator<=(const Fibo &rhs)
{
    return this<rhs || this==rhs;
}
bool  operator>(const Fibo &rhs)
{
    return !this<=rhs;
}
bool  operator>=(const Fibo &rhs)
{
    return !this<rhs;
}
