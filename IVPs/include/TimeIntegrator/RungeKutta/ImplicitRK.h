/**
 * @file ImplicitRK.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __IMPLICIT_RK_H__
#define __IMPLICIT_RK_H__

#include "TimeIntegrator/RungeKutta.h"

namespace TI{namespace RK{

class ImplicitRK : public RungeKutta
{
public:
    virtual PointSet_t_U solve(Vector Initials, RHSFunction* RHS) override;
    // 使用默认的 setSolverParams
};

};};

#endif