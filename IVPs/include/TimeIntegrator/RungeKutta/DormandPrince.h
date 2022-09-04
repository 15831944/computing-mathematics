/**
 * @file DormandPrince.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 5(4) Embedded RK
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __Dormand_Prince_H__
#define __Dormand_Prince_H__

#include "TimeIntegrator/RungeKutta/EmbeddedRK.h"

namespace TI{namespace RK{

class DormandPrince : public EmbeddedRK
{
public:
    DormandPrince()
    {
        resizeParam(7);
        A_ << 0, 0, 0, 0, 0, 0, 0,
              1/5.0, 0, 0, 0, 0, 0, 0,
              3/40.0, 9/40.0, 0, 0, 0, 0, 0,
              44/45.0, -56/15.0, 32/9.0, 0, 0, 0, 0,
              19372/6561.0, -25360/2187.0, 64448/6561.0, -212/729.0, 0, 0, 0,
              9017/3168.0, -355/33.0, 46732/5247.0, 49/176.0, -5103/18656.0, 0, 0,
              35/384.0, 0, 500/1113.0, 125/192.0, -2187/6784.0, 11/84.0, 0;
        b_ << 35/384.0, 0, 500/1113.0, 125/192.0, -2187/6784.0, 11/84.0, 0;
        bhat_ << 5179/57600.0, 0, 7571/16695.0, 393/640.0, -92097/339200.0, 187/2100.0, 1/40.0;
        c_ << 0, 1/5.0, 3/10.0, 4/5.0, 8/9.0, 1, 1;
        minOrder_ = 4;
    }
};

};};

#endif