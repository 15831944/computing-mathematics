/**
 * @file GaussLegendre.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __Gauss_Legendre_H__
#define __Gauss_Legendre_H__

#include "TimeIntegrator/RungeKutta/ImplicitRK.h"
#include <cmath>

namespace TI{namespace RK{

template<int stage>
class GaussLegendre : public ImplicitRK
{
public:
    GaussLegendre();
};

using GL1 = GaussLegendre<1>;
using GL2 = GaussLegendre<2>;
using GL3 = GaussLegendre<3>;

template<>
GL1::GaussLegendre()
{
    resizeParam(1);
    b_ << 1;
    c_ << 1/2.0;
    A_ << 1/2.0;
}

template<>
GL2::GaussLegendre()
{
    resizeParam(2);
    b_ << 1/2.0, 1/2.0;
    c_ << (3-std::sqrt(3))/6.0, (3+std::sqrt(3))/6.0;
    A_ << 1/4.0, (3-2*std::sqrt(3))/12.0, 
          (3+2*std::sqrt(3))/12.0, 1/4.0;
}

template<>
GL3::GaussLegendre()
{
    resizeParam(3);
    b_ << 5/18.0, 4/9.0, 5/18.0;
    c_ << (5-std::sqrt(15))/10.0, 1/2.0, (5+std::sqrt(15))/10.0;
    A_ << 5/36.0, 2/9.0-std::sqrt(15)/15.0, 5/36.0-std::sqrt(15)/30.0, 
          5/36.0+std::sqrt(15)/24.0, 2/9.0, 5/36.0-std::sqrt(15)/24.0,
          5/36.0+std::sqrt(15)/30.0, 2/9.0+std::sqrt(15)/15.0, 5/36.0;
}

};};

#endif