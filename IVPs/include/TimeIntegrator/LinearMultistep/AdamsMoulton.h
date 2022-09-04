/**
 * @file AdamsMoulton.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/LinearMultistep/ImplicitLM.h"

#ifndef __ADAMS_MOULTON_H__
#define __ADAMS_MOULTON_H__

namespace TI{namespace LM{

template<int step>
class AdamsMoulton : public ImplicitLM<step>
{
public:
    AdamsMoulton();
};

using AM2 = AdamsMoulton<1>;
using AM3 = AdamsMoulton<2>;
using AM4 = AdamsMoulton<3>;
using AM5 = AdamsMoulton<4>;

template<>
AM2::AdamsMoulton()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = 0.5;
    beta_[1] = 0.5;
}

template<>
AM3::AdamsMoulton()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = -1/12.0;
    beta_[1] = 8/12.0;
    beta_[2] = 5/12.0;
}

template<>
AM4::AdamsMoulton()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = 1/24.0;
    beta_[1] = -5/24.0;
    beta_[2] = 19/24.0;
    beta_[3] = 9/24.0;
}

template<>
AM5::AdamsMoulton()
{
    alpha_[step_] = 1;
    alpha_[step_ - 1] = -1;
    beta_[0] = -19/720.0;
    beta_[1] = 106/720.0;
    beta_[2] = -264/720.0;
    beta_[3] = 646/720.0;
    beta_[4] = 251/720.0;
}

};};

#endif