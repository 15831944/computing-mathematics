/**
 * @file ExplicitLM.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "TimeIntegrator/LinearMultistep/ExplicitLM.h"

namespace TI{namespace LM{

template<int step>
PointSet_t_U ExplicitLM<step>::solve(Vector Initials, RHSFunction* RHS)
{
    assert(T_end_ > 0 && time_step_ > 0); // 参数已设定
    int dim = Initials.size(); // dimension
    PointSet_t_U res = completeInitials(Initials, RHS);
    Real time_step = time_step_;
    // std::cout << "OK " << res.size() << std::endl;
    Real t = step * time_step;
    while(t <= T_end_)
    {
        auto it = --res.end();
        Vector Ut = it->second;
        // std::cout << t<<std::endl;
        for(int j = step_-1 ; j >= 0 ; j --)
        {
            Ut = Ut + RHS->eval(it->second, t-(step_-j)*time_step) * beta_[j] * time_step;
            if(j != 0)
                it --;
            // std::cout << it->second << std::endl;
        }
        res.insert(Point_t_U(t, Ut));
        if(t == T_end_)
            break;
        if(t + time_step > T_end_)
            time_step = T_end_ - t;
        t = t + time_step;
    }
    return res;
}

template class ExplicitLM<1>;
template class ExplicitLM<2>;
template class ExplicitLM<3>;
template class ExplicitLM<4>;

};};