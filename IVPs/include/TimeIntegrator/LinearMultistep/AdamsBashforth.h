/**
 * @file AdamsBashforth.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __ADAM_BASHFORTH_H__
#define __ADAM_BASHFORTH_H__

// #include "TimeIntegrator/LinearMultistep.h"
#include "TimeIntegrator/LinearMultistep/ExplicitLM.h"

namespace TI{namespace LM{

template<int step>
class AdamsBashforth : public ExplicitLM<step>
{
public:
    AdamsBashforth();
};

using AB1 = AdamsBashforth<1>;
using AB2 = AdamsBashforth<2>;
using AB3 = AdamsBashforth<3>;
using AB4 = AdamsBashforth<4>;

template<>
AB1::AdamsBashforth()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = 1;
}

template<>
AB2::AdamsBashforth()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = -0.5;
    beta_[1] = 1.5;
}

template<>
AB3::AdamsBashforth()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = 5/12.0;
    beta_[1] = -16/12.0;
    beta_[2] = 23/12.0;
}

template<>
AB4::AdamsBashforth()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = -9/24.0;
    beta_[1] = 37/24.0;
    beta_[2] = -59/24.0;
    beta_[3] = 55/24.0;
}

};};

#endif