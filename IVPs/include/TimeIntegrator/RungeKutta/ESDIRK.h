/**
 * @file ESDIRK.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ESDIRK_H__
#define __ESDIRK_H__

#include "TimeIntegrator/RungeKutta/DiagonalIRK.h"

namespace TI{namespace RK{

class ESDIRK : public DiagonalIRK
{
public:
    ESDIRK()
    {
        resizeParam(6);
        A_ << 0, 0, 0, 0, 0, 0,
              1/4.0, 1/4.0 , 0, 0, 0, 0,
              8611/62500.0, -1743/31250.0, 1/4.0, 0, 0, 0,
              5012029/34652500.0, -654441/2922500.0, 174375/388108.0, 1/4.0, 0, 0,
              15267082809/155376265600.0, -71443401/120774400.0, 730878875/902184768.0, 2285395/8070912.0, 1/4.0, 0,
              82889/524892.0, 0, 15625/83664.0, 69875/102672.0, -2260/8211.0, 1/4.0;
        b_ << 82889/524892.0, 0, 15625/83664.0, 69875/102672.0, -2260/8211.0, 1/4.0;
        c_ << 0, 1/2.0, 83/250.0, 31/50.0, 17/20.0, 1;
    }
};

};}

#endif