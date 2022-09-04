/**
 * @file Fehlberg.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 4(5) Embedded RK
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __FEHLBERG_H__
#define __FEHLBERG_H__

#include "TimeIntegrator/RungeKutta/EmbeddedRK.h"

namespace TI{namespace RK{

class Fehlberg : public EmbeddedRK
{
public:
    Fehlberg()
    {
        resizeParam(6);
        A_ << 0, 0, 0, 0, 0, 0,
              1/4.0, 0, 0, 0, 0, 0,
              3/32.0, 9/32.0, 0, 0, 0, 0,
              1932/2197.0, -7200/2197.0, 7296/2197.0, 0, 0, 0,
              439/216.0, -8, 3680/513.0, -845/4104.0, 0, 0,
              -8/27.0, 2, -3544/2565.0, 1859/4104.0, -11/40.0, 0;
        b_ << 25/216.0, 0, 1408/2565.0, 2197/4104.0, -1/5.0, 0;
        bhat_ << 16/135.0, 0, 6656/12825.0, 28561/56430.0, -9/50.0, 2/55.0;
        c_ << 0, 1/4.0, 3/8.0, 12/13.0, 1, 1/2.0;
        minOrder_ = 4;
    }
};

};};

#endif