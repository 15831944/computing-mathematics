/**
 * @file ImplicitLM.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/LinearMultistep/ImplicitLM.h"
#include <Eigen/Dense>
#include <iostream>

namespace TI{namespace LM{

const Real MaxRes = 1e-10;

template<int step>
PointSet_t_U ImplicitLM<step>::solve(Vector Initials, RHSFunction* RHS)
{
    assert(T_end_ > 0 && time_step_ > 0); // 参数已设定
    int dim = Initials.size(); // dimension
    PointSet_t_U res = completeInitials(Initials, RHS);
    // std::cout << "OK " << res.size() << std::endl;
    Real t = step * time_step_;
    while(t <= T_end_)
    {
        auto it = --res.end();
        Vector Con = Vector::Zero(dim);
        for(int j = step_-1 ; j >= 0 ; j --)
        {
            Con += time_step_ * beta_[j] * RHS->eval(it->second, t-(step_-j)*time_step_)
                   - alpha_[j] * it->second;
            if(j != 0)
                it --;
            // std::cout << it->second << std::endl;
        }
        Con /= time_step_*beta_[step];
        
        // 求解非线性方程组
        Real k = -alpha_[step]/(time_step_*beta_[step]);
        Vector X = it->second;
        Vector F = RHS->eval(X, t)+k*X+Con;
        Matrix Jacobi;
        // std::cout << t << std::endl;
        while(F.norm() > MaxRes)
        {
            // std::cout << F.transpose() << std::endl;
            Jacobi = RHS->Jacobi(X, t) + k*Matrix::Identity(dim, dim);
            Vector delta = Jacobi.colPivHouseholderQr().solve(F);
            X -= delta;
            F = RHS->eval(X, t)+k*X+Con;
        }

        res.insert(Point_t_U(t, X));
        t = t + time_step_;
    }
    return res;
}

template class ImplicitLM<1>;
template class ImplicitLM<2>;
template class ImplicitLM<3>;
template class ImplicitLM<4>;

};};