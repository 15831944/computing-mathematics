/**
 * @file LinearMultistep.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LINEAR_MULTISTEP__
#define __LINEAR_MULTISTEP__

#include "TimeIntegrator/LinearMultistep.h"
#include "TimeIntegrator/RungeKutta/ClassicalRK.h"
#include "globals.h"
#include <cassert>

namespace TI{

template<int step>
PointSet_t_U LinearMultistep<step>::completeInitials(Vector Initials, RHSFunction* RHS)
{
    assert(time_step_ > 0 && step >= 1);
    if(step == 1)
    {
        PointSet_t_U res;
        res.insert(Point_t_U(0, Initials));
        return res;
    }
    TI::RK::ClassicalRK solver;
    solver.setSolverParam(time_step_, (step-1)*time_step_+DBL_EPSILON);
    PointSet_t_U res = solver.solve(Initials, RHS);
    return res;
}

template<int step>
LinearMultistep<step>::LinearMultistep()
{
    for(int i = 0 ; i <= step_ ; i ++)
    {
        alpha_[i] = 0;
        beta_[i] = 0;
    }
}

template class LinearMultistep<1>;
template class LinearMultistep<2>;
template class LinearMultistep<3>;
template class LinearMultistep<4>;

};

#endif