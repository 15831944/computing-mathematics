/**
 * @file EmbeddedRK.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/RungeKutta/EmbeddedRK.h"
#include <cmath>
#include <iostream>

namespace TI{namespace RK{

void EmbeddedRK::resizeParam(int s)
{
    A_.resize(s, s);
    bhat_.resize(s);
    b_.resize(s);
    c_.resize(s);
}

bool EmbeddedRK::setEmbeddedRKParam(Vector E_abs, Vector E_rel, Real rho, Real rho_min, Real rho_max)
{
    E_abs_ = E_abs;
    E_rel_ = E_rel;
    if(rho == 0)
    {
        rho_ = std::pow(0.38, 1/double(1+minOrder_));
        rho_min_ = (0.2+rho_)/2.0;
        rho_max_ = 2;
    }
    else
    {
        rho_ = rho;
        rho_min_ = rho_min;
        rho_max_ = rho_max;
    }
    return true;
}

// bool EmbeddedRK::checkFSAL()
// {
//     int s = A_.size();
//     if(c_[s - 1] != 1)
//         return false;
//     for(int j = 0 ; j < s ; j ++)
//         if(b_[j] != A_(s-1, j))
//             return false;
//     return true;
// }

bool EmbeddedRK::checkParam(const Vector &Initials)
{
    assert((Initials.size() == E_abs_.size() && E_abs_.size() == E_rel_.size()));
        // return false;
    assert((0.2 <= rho_min_ && rho_min_ <= rho_));
        // return false;
    assert((1.5 <= rho_max_ && rho_max_ <= 5));
        // return false;
    assert((rho_ < 1));
        // return false;
    // std::cout << rho_ << std::endl;
    return true;
}

PointSet_t_U EmbeddedRK::solve(Vector Initials, RHSFunction* RHS)
{
    int dim = Initials.size(); // dimension

    assert(time_step_ > 0 && T_end_ > 0); // 设置基本参数
    if(E_abs_.size() == 0) // 用户没有设置EmbeddedRK的参数
        setEmbeddedRKParam(1e-8*Vector::Ones(dim), 1e-8*Vector::Ones(dim)); // 采用默认参数
    else // 用户设置了EmbeddedRK的参数
        assert(checkParam(Initials));  // 判断用户设定的参数是否合法

    bool FSAL = checkFSAL(); 
    // std::cout << FSAL << std::endl;
    int s = getStage(); // stage of RK
    Real time_step = time_step_;
    
    PointSet_t_U res;
    Vector Ut = Initials;
    Vector FSAL_register(dim);
    Real t = 0;

    while(t <= T_end_)
    {
        // std::cout << t << std::endl;
        res.insert(Point_t_U(t, Ut));
        // if(t + time_step > T_end_)
        // {
        //     if(t == T_end_)
        //         break;
        //     if(t + time_step_ <= T_end_)
        //         time_step = time_step_;
        //     else
        //         time_step = T_end_ - t;
        // }
        if(t + time_step > T_end_)
        {
            if(t == T_end_)
                break;
            else
                time_step = T_end_ - t;
        }
        VecArray y(s, Vector::Zero(dim));
        Real E_ind = 10;
        if(t != 0 && FSAL)
            y[0] = FSAL_register;
        else
            y[0] = RHS -> eval(Ut, t);
        Vector tmp_U(dim), tmp_Uhat(dim);
        Real old_time_step;
        while(E_ind > 1)
        {
            old_time_step = time_step;
            for(int i = 1 ; i < s ; i ++)
            {
                Vector tmp = Ut;
                for(int j = 0 ; j < i ; j ++)
                    tmp = tmp + y[j] * time_step * A_(i,j);
                y[i] = RHS -> eval(tmp, t + c_[i]*time_step);
            }
            if(FSAL)
                FSAL_register = y[s - 1];
            tmp_U = Ut;
            tmp_Uhat = Ut;
            for(int i = 0 ; i < s ; i ++)
            {
                tmp_U = tmp_U + y[i]*time_step*b_[i];
                tmp_Uhat = tmp_Uhat + y[i]*time_step*bhat_[i];
            }
            // E_ind
            E_ind = 0;
            for(int i = 0 ; i < dim ; i ++)
            {
                Real eps = E_abs_[i]+std::abs(Ut[i])*E_rel_[i];
                E_ind += std::abs(tmp_U[i] - tmp_Uhat[i])/eps;
            }
            E_ind = std::sqrt(E_ind/double(dim));
            // std::cout << "E_ind " << E_ind << std::endl;
            time_step *= std::min(rho_max_, std::max(rho_min_, rho_*std::pow(E_ind, -1/double(minOrder_+1))));
        }
        Ut = tmp_U;
        t = t + old_time_step;
    }
    return res;
}

};};