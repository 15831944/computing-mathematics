/**
 * @file ClassicalRK.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief classical RK算法
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CLASSICAL_RK_H__
#define __CLASSICAL_RK_H__

#include "TimeIntegrator/RungeKutta/ExplicitRK.h"

namespace TI{namespace RK{

class ClassicalRK : public ExplicitRK
{
public:
    ClassicalRK()
    {
        resizeParam(4);
        b_ << 1/6.0, 1/3.0, 1/3.0, 1/6.0;
        c_ << 0, 1/2.0, 1/2.0, 1;
        A_ << 0,0,0,0,
              0.5,0,0,0,
              0,0.5,0,0,
              0,0,1,0;
    }
};

};};

#endif