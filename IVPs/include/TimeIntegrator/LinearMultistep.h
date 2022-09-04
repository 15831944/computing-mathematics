/**
 * @file LinearMultistep.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LINEAR_MULTISTEP_H__
#define __LINEAR_MULTISTEP_H__

#include "TimeIntegrator.h"
#include "globals.h"
#include <vector>

namespace TI{

template<int step>
class LinearMultistep : public TimeIntegrator
{
public:
    enum{step_ = step};
    Real alpha_[step+1], beta_[step+1];
    
public:   
    PointSet_t_U completeInitials(Vector Initials, RHSFunction* RHS);
    LinearMultistep();
};
};

#endif