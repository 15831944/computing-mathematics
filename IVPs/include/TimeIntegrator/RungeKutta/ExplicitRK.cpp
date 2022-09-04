/**
 * @file ExplicitRK.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/RungeKutta/ExplicitRK.h"
#include "RHSFunction.h"
#include <cassert>
#include <vector>

namespace TI{namespace RK{

using VecArray = std::vector<Vector>;

PointSet_t_U ExplicitRK::solve(Vector Initials, RHSFunction* RHS)
{
    // std::cout << T_end_ << " " << time_step_ << std::endl;
    assert(T_end_ > 0 && time_step_ > 0); // 参数已设定
    Real time_step = time_step_;
    int s = getStage(); // stage of RK
    int dim = Initials.size(); // dimension
    PointSet_t_U res;
    Vector Ut = Initials;
    Real t = 0;
    while(t <= T_end_)
    {
        res.insert(Point_t_U(t, Ut));
        if(t + time_step > T_end_)
            time_step = T_end_ - t;
        if(t == T_end_)
            break;
        VecArray y(s, Vector::Zero(dim));
        y[0] = RHS -> eval(Ut, t);
        for(int i = 1 ; i < s ; i ++)
        {
            Vector tmp = Ut;
            for(int j = 0 ; j < i ; j ++)
                tmp = tmp + y[j] * time_step * A_(i,j);
            y[i] = RHS -> eval(tmp, t + c_[i]*time_step);
            // std::cout << "tmp " << tmp << std::endl;
            // std::cout << "y " << RHS -> eval(tmp, t + c_[i]*time_step_) << std::endl;
        }
        for(int i = 0 ; i < s ; i ++)
            Ut = Ut + y[i]*time_step*b_[i];
        // std::cout << t << " " << Ut << std::endl;
        t = t + time_step;
    }
    return res;
}

};};