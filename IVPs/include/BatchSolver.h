/**
 * @file BatchSolver.h
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 根据输入的Json文件，批量求解
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __BATCH_SOLVER_H__
#define __BATCH_SOLVER_H__

#include "TimeIntegratorFactory.h"
#include "RHSFunctionFactory.h"
#include "GeneralFactory.h"
#include "globals.h"
#include <string.h>
#include <json/json.h>
#include <vector>
#include <map>

using cstring = std::string;
using DblArray = std::vector<double>;
using PointSet_t_U = std::map<Real, Vector>;

class BatchSolver
{
protected:
    Json::Value root_;
    DblArray recorder_;
    DblArray timestep_;
    cstring outputPath_;
    cstring identifier_;
    double solve_unit(Json::Value unit, int index);
    void output_unit(const Json::Value &unit, const PointSet_t_U &res, int index);
	void output_others(const DblArray &err);
public:
    BatchSolver(cstring path);
    void setOutputPath(cstring path){outputPath_ = path;};
    void setIdentifier(cstring id){identifier_ = id;};
    void readJson(cstring path);
    DblArray getRecorder(){return recorder_;};
    DblArray solve();    
};

#endif