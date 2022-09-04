/**
 * @file EmbeddedRK.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __EMBEDDED_RK_H__
#define __EMBEDDED_RK_H__

#include "TimeIntegrator/RungeKutta.h"

namespace TI{namespace RK{

using VecArray = std::vector<Vector>;

class EmbeddedRK : public RungeKutta
{
protected:
    int minOrder_;
    Vector bhat_;
    Vector E_abs_, E_rel_;
    Real rho_, rho_min_, rho_max_;
public:
    virtual PointSet_t_U solve(Vector Initials, RHSFunction* RHS) override;
    virtual bool setEmbeddedRKParam(Vector E_abs , Vector E_rel , Real rho = 0, Real rho_min = 0, Real rho_max = 0) override;
    bool checkParam(const Vector &Initials);
    // bool checkFSAL();
    virtual void resizeParam(int s) override;
};

};};



#endif