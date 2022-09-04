/**
 * @file BDF.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BDF_H__
#define __BDF_H__

#include "TimeIntegrator/LinearMultistep/ImplicitLM.h"

namespace TI{namespace LM{

template<int step>
class BDF : public ImplicitLM<step>
{
public:
    BDF();
};

using BDF1 = BDF<1>;
using BDF2 = BDF<2>;
using BDF3 = BDF<3>;
using BDF4 = BDF<4>;

template<>
BDF1::BDF()
{
    beta_[step_] = 1;
    alpha_[0] = -1;
    alpha_[1] = 1;
}

template<>
BDF2::BDF()
{
    beta_[step_] = 2/3.0;
    alpha_[0] = 1/3.0;
    alpha_[1] = -4/3.0;
    alpha_[2] = 1;
}

template<>
BDF3::BDF()
{
    beta_[step_] = 6/11.0;
    alpha_[0] = -2/11.0;
    alpha_[1] = 9/11.0;
    alpha_[2] = -18/11.0;
    alpha_[3] = 1;
}

template<>
BDF4::BDF()
{
    beta_[step_] = 12/25.0;
    alpha_[0] = 3/25.0;
    alpha_[1] = -16/25.0;
    alpha_[2] = 36/25.0;
    alpha_[3] = -48/25.0;
    alpha_[4] = 1;
}

};};

#endif