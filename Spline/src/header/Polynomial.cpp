/**
 * @file Polynomial.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief implement of Polynomial.h
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Polynomial.h"

template<u_int _Degree, u_int _Dim>
Polynomial<_Degree, _Dim>::Polynomial()
{
    Coef.resize(_Degree+1);
}

template<u_int _Degree, u_int _Dim>
Polynomial<_Degree, _Dim>::Polynomial(const vector_Coef& _Coef)
{
    if(_Coef.size() != Degree+1)
    {
        std::cerr << "Unexpected Initializer." << std::endl;
        return;
    }
    auto it = _Coef.begin();
    for( ; it < _Coef.end(); it ++)
        Coef.push_back(*it);
}

template<u_int _Degree, u_int _Dim>
Polynomial<_Degree, _Dim>::Polynomial(const Polynomial& _p)
{
    if(_p.Dim != this->Dim || _p.Degree != this->Degree)
    {
        std::cerr << "Unexpected Initializer." << std::endl;
        return;
    }
    auto it = (_p.Coef).begin();
    for(; it < (_p.Coef).end() ; it ++)
    {
        Coef.push_back(*it);
    }
}

template<u_int _Degree, u_int _Dim>
int Polynomial<_Degree, _Dim>::set_Coef(const vector_Coef& _Coef)
{
    if(_Coef.size() != Degree+1)
        return -1;
    Coef.clear();
    auto it = _Coef.begin();
    for(; it < _Coef.end(); it ++)
        Coef.push_back(*it);
    return 0;
}

template<u_int _Degree, u_int _Dim>
int Polynomial<_Degree, _Dim>::set_Coef(int _Deg, const CoefType& _Coef)
{
    if(_Deg > _Degree || _Deg < 0)
        return -1;
    Coef[_Deg] = _Coef;
    return 0;
}

template<u_int _Degree, u_int _Dim>
typename Polynomial<_Degree, _Dim>::CoefType Polynomial<_Degree, _Dim>::get_Coef(int _Deg)
{
    return Coef[_Deg];
}


template<u_int _Degree, u_int _Dim>
Polynomial<_Degree==0?0:_Degree-1, _Dim> Polynomial<_Degree, _Dim>::diff()
{
    vector_Coef result;
    if(_Degree == 0)
    {    
        result.push_back(CoefType::zero());
        return Polynomial<_Degree==0?0:_Degree-1, _Dim>(result);
    }
    else
    {
        result.resize(Degree);
        for(int i = Degree; i >= 1 ; i --)
        {
            result[i - 1] = Coef[i] * i;
        }
        return Polynomial<_Degree==0?0:_Degree-1, _Dim>(result);
    }
}

/**
 * Implement of the overload operators.
 */

template<u_int _Degree, u_int _Dim>
template<u_int _Degree2>
Polynomial<std::max(_Degree, _Degree2), _Dim> Polynomial<_Degree, _Dim>::operator+
    (const Polynomial<_Degree2, _Dim>& _p) const
{
    Polynomial<std::max(_Degree, _Degree2), _Dim> res;
    const int N = std::max(_Degree, _Degree2);
    auto &c1 = this -> Coef;
    auto &c2 = _p.Coef;
    for(int i = 0 ; i <= N ; i ++)
    {
        CoefType t1, t2;
        if(i > _Degree)
            t1 = CoefType::zero();
        else
            t1 = c1[i];
        if(i > _Degree2)
            t2 = CoefType::zero();
        else 
            t2 = c2[i];
        res.Coef[i] = t1 + t2;
    }
    return res;
}

template<u_int _Degree, u_int _Dim>
template<u_int _Degree2>
Polynomial<std::max(_Degree, _Degree2), _Dim> Polynomial<_Degree, _Dim>::operator-
    (const Polynomial<_Degree2, _Dim>& _p) const
{
    Polynomial<std::max(_Degree, _Degree2), _Dim> res;
    const int N = std::max(_Degree, _Degree2);
    auto &c1 = this -> Coef;
    auto &c2 = _p.Coef;
    for(int i = 0 ; i <= N ; i ++)
    {
        CoefType t1, t2;
        if(i > _Degree)
            t1 = CoefType::zero();
        else
            t1 = c1[i];
        if(i > _Degree2)
            t2 = CoefType::zero();
        else 
            t2 = c2[i];
        res.Coef[i] = t1 - t2;
    }
    return res;
} 

template<u_int _Degree, u_int _Dim>
template<u_int _Degree2>
Polynomial<_Degree+_Degree2, _Dim> Polynomial<_Degree, _Dim>::operator*
    (const Polynomial<_Degree2, _Dim>& _p) const
{
    vector_Coef res;
    res.resize(_Degree+_Degree2+1);
    auto &c1 = this->Coef;
    auto &c2 = _p.Coef;
    for(int i = 0 ; i < c1.size(); i ++)
        for(int j = 0 ; j < c2.size(); j ++)
            res[i+j] = res[i + j] + c1[i] * c2[j];
    return Polynomial<_Degree+_Degree2, _Dim>(res);
}

/// Evaluation at some x
template<u_int _Degree, u_int _Dim>
typename Polynomial<_Degree, _Dim>::CoefType Polynomial<_Degree, _Dim>::operator()(double _x) const
{
    CoefType res = CoefType::zero();
    for(int i = 0 ; i < Coef.size() ; i ++)
        res = res + Coef[i] * std::pow(_x, i);
    return res;
}

template <u_int _Degree, u_int _Dim>
std::ostream& operator<< (std::ostream& output, const Polynomial<_Degree, _Dim>& _p)
{
    int n = _Degree;
    auto it = --(_p.Coef).end();
    if(_Degree == 0) ///< degree = 0
    {
        std::cout << *it << std::endl;
        return output;
    }
    std::cout << *it << " x^" << n;
    it --; n --;

    for(; it >= (_p.Coef).begin(); it --, n --)
    {
        if((*it) != Polynomial<_Degree, _Dim>::CoefType::zero())
        {
            if(n != 0)
                std::cout << " + " << *it << " x^" << n;
            else
                std::cout << " + " << *it;
        }
    }
    std::cout << std::endl;
    return output;
}