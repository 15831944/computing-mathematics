/**
 * @file TimeIntegrator.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TIME_INTEGRATOR_H__
#define __TIME_INTEGRATOR_H__

#include <map>
#include <initializer_list>
#include "RHSFunction.h"
#include "globals.h"

using PointSet_t_U = std::map<Real, Vector>;
using Point_t_U = std::pair<Real, Vector>;

class TimeIntegrator
{
protected:
    Real T_end_;
    Real time_step_;

public:
    virtual PointSet_t_U solve(Vector Initials, RHSFunction* RHS) = 0;
    virtual bool setSolverParam(Real time_step, Real T_end, std::initializer_list<double> params = {})
    {
        T_end_ = T_end;
        time_step_ = time_step;
        return true;
    }
    virtual bool setEmbeddedRKParam(Vector E_abs, Vector E_rel, Real rho = 0, Real rho_min = 0, Real rho_max = 0)
    {
        return false;
    }
};

#endif