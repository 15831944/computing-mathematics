/**
 * @file ThreeBody.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __THREE_BODY_H__
#define __THREE_BODY_H__

#include "globals.h"
#include "RHSFunction.h"
#include <cassert>
#include <cmath>

namespace RHS
{

Real mu = 1/81.45;

class ThreeBody : public RHSFunction
{
    Vector eval(Vector u, Real t) override;
    Matrix Jacobi(Vector u, Real t) override;
};

Vector ThreeBody::eval(Vector u, Real t)
{
    assert(u.size() == 6);
    Vector res = Vector::Zero(6);
    Real tmp1 = std::pow(SQUARE(u[1]) + SQUARE(u[2]) + SQUARE(u[0]+mu-1), 1.5);
    Real tmp2 = std::pow(SQUARE(u[1]) + SQUARE(u[2]) + SQUARE(u[0]+mu), 1.5);
    res[0] = u[3];
    res[1] = u[4];
    res[2] = u[5];
    res[3] = 2*u[4]+u[0]-(mu*(u[0]+mu-1))/tmp1-((1-mu)*(u[0]+mu))/tmp2;
    res[4] = -2*u[3]+u[1]-mu*u[1]/tmp1-(1-mu)*u[1]/tmp2;
    res[5] = -mu*u[2]/tmp1-(1-mu)*u[2]/tmp2;
    return res;
}

Matrix ThreeBody::Jacobi(Vector u, Real t)
{
    Matrix res = Matrix::Zero(6,6);
    double deno_0_15 = std::pow(SQUARE(mu + u[0]) + SQUARE(u[1]) + SQUARE(u[2]), 1.5);
    double deno_1_15 = std::pow(SQUARE(mu + u[0] - 1) + SQUARE(u[1]) + SQUARE(u[2]), 1.5);
    double deno_0_25 = std::pow((SQUARE(mu + u[0]) + SQUARE(u[1]) + SQUARE(u[2])), 2.5);
    double deno_1_25 = std::pow(SQUARE(mu + u[0] - 1) + SQUARE(u[1]) + SQUARE(u[2]), 2.5);
    res(0,3) = 1;
    res(1,4) = 1;
    res(2,5) = 1;
    res(3,0) = (mu - 1)/deno_0_15 
                - mu/deno_1_15
                + (3*mu*(2*mu + 2*u[0] - 2)*(mu + u[0] - 1))/(2.0*deno_1_25) 
                - (3*(2*mu + 2*u[0])*(mu + u[0])*(mu - 1))/(2.0*deno_0_25) + 1;
    res(3,1) = (3*mu*u[1]*(mu + u[0] - 1))/deno_1_25
                - (3*u[1]*(mu + u[0])*(mu - 1))/deno_0_25;
    res(3,2) = (3*mu*u[2]*(mu + u[0] - 1))/deno_1_25
                - (3*u[2]*(mu + u[0])*(mu - 1))/deno_0_25;
    res(3,4) = 2;
    res(4,0) = (3*mu*u[1]*(2*mu + 2*u[0] - 2))/(2*deno_1_25)  
                - (3*u[1]*(2*mu + 2*u[0])*(mu - 1))/(2*deno_0_25);
    res(4,1) = (mu - 1)/deno_0_15
                - mu/deno_1_15
                - (3*SQUARE(u[1])*(mu - 1))/deno_0_25 
                + (3*mu*SQUARE(u[1]))/deno_1_25 + 1;
    res(4,2) = (3*mu*u[1]*u[2])/deno_1_25 
                - (3*u[1]*u[2]*(mu - 1))/deno_0_25;
    res(4,3) = -2;
    res(5,0) = (3*mu*u[2]*(2*mu + 2*u[0] - 2))/(2*deno_1_25) 
                - (3*u[2]*(2*mu + 2*u[0])*(mu - 1))/(2*deno_0_25);
    res(5,1) = (3*mu*u[1]*u[2])/deno_1_25 
                - (3*u[1]*u[2]*(mu - 1))/deno_0_25;
    res(5,2) = (mu - 1)/deno_0_15
                - mu/deno_1_15
                - (3*SQUARE(u[2])*(mu - 1))/deno_0_25
                + (3*mu*SQUARE(u[2]))/deno_1_25;
    return res;
}

};

#endif