/**
 * @file ExplicitLM.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __EXPLICIT_LM_H__
#define __EXPLICIT_LM_H__

#include "TimeIntegrator/LinearMultistep.h"

namespace TI{namespace LM{

template<int step>
class ExplicitLM : public LinearMultistep<step>
{
protected:
    using LinearMultistep<step>::T_end_, LinearMultistep<step>::time_step_, 
        LinearMultistep<step>::step_, LinearMultistep<step>::completeInitials, 
        LinearMultistep<step>::alpha_, LinearMultistep<step>::beta_;
public:
    PointSet_t_U solve(Vector Initials, RHSFunction* RHS) override;
    // 使用默认 setSolverParam
};

};};

#endif