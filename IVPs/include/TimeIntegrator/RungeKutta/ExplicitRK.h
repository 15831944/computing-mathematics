/**
 * @file ExplicitRK.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __EXPLICIT_RK_H__
#define __EXPLICIT_RK_H__

#include "TimeIntegrator/RungeKutta.h"

namespace TI{namespace RK{

class ExplicitRK : public RungeKutta
{

public:
    virtual PointSet_t_U solve(Vector Initials, RHSFunction* RHS) override;
    // 使用默认的 setSolverParams
};

};};

#endif