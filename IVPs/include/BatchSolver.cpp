/**
 * @file BatchSolver.cpp
 * @author MaCheng (macheng@zju.edu.cn)
 * @brief 实现class BatchSolver
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "BatchSolver.h"
#include <cassert>
#include <Eigen/Core>
#include <chrono>
#include <iostream>
#include <fstream>

#define TIME_NOW (std::chrono::high_resolution_clock::now())
using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

double sec_duration(time_point &a, time_point &b)
{
    auto d = std::chrono::duration_cast<std::chrono::duration<double>>(b-a);
    return d.count();
}

BatchSolver::BatchSolver(cstring path)
{
    readJson(path);
}

void BatchSolver::readJson(cstring path)
{
    std::ifstream infile(path);
    assert(infile.good());
    Json::Value root;

    Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	Json::String errs;
	assert(parseFromStream(builder, infile, &root, &errs) && "error when parse json");
    
    assert(root.isArray());
    root_ = root;
}

bool isUnitValid(const Json::Value &unit)
{
    if(unit["Method"].isNull() 
        || (unit["TimeStep"].isNull() && unit["StepNum"].isNull())
        || unit["T"].isNull()
        || unit["Initial"].isNull()
        || unit["RHS"].isNull())
        return false;
    return true;
}

double BatchSolver::solve_unit(Json::Value unit, int index)
{
    assert(isUnitValid(unit));
    cstring Method = unit["Method"].asString();
    cstring RHS = unit["RHS"].asString();
    double T = unit["T"].asDouble();
    double TimeStep;
    if(unit["TimeStep"].isNull())
    {
        double N = unit["StepNum"].asDouble();
        TimeStep = T / N;
    }
    else
    {
        TimeStep= unit["TimeStep"].asDouble();
    }
    // TimeStep = T/double(std::round(T/TimeStep)); ////////////
    double Order;
    if(unit["Order"].isNull())
        Order = 0;
    else
        Order = unit["Order"].asInt();
    Json::Value init = unit["Initial"];
    Vector Initial(init.size());
    for(int i = 0 ; i < init.size() ; i ++)
        Initial(i) = init[i].asDouble();
    Vector Exact(init.size());
    if(unit["ExactSolution"].isNull())
        Exact = Initial;
    else
    {
        Json::Value exact = unit["ExactSolution"];
        assert(exact.size() == init.size());
        for(int i = 0 ; i < exact.size() ; i ++)
            Exact(i) = exact[i].asDouble();
    }

    // 
    TimeIntegrator* solver = TimeIntegratorFactory::
        Instance().CreateObject(TimeIntegratorIdentifier(Method, Order));
    RHSFunction* rhsFunc = RHSFunctionFactory::Instance().CreateObject(RHS);
    if(Method == "DormandPrince" || Method == "Fehlberg")
    {
        Vector AbsErr = 1e-10*Vector::Ones(init.size());
        Vector RelErr = 1e-10*Vector::Ones(init.size());
        if(!unit["AbsErr"].isNull())
        {
            Json::Value tmp = unit["AbsErr"];
            if(tmp.isArray())
            {
                assert(tmp.size() == init.size());
                for(int i = 0 ; i < tmp.size() ; i ++)
                    AbsErr(i) = tmp[i].asDouble();
            }
            else
            {
                // std::cout << "111 " << std::endl;
                AbsErr = tmp.asDouble() * Vector::Ones(init.size());
            }
        }
        if(!unit["RelErr"].isNull())
        {
            Json::Value tmp = unit["RelErr"];
            if(tmp.isArray())
            {
                assert(tmp.size() == init.size());
                for(int i = 0 ; i < tmp.size() ; i ++)
                    RelErr(i) = tmp[i].asDouble();
            }
            else
            {
                RelErr = tmp.asDouble() * Vector::Ones(init.size());
            }
        }
        solver -> setEmbeddedRKParam(AbsErr, RelErr);
    }
    solver -> setSolverParam(TimeStep, T);
    auto t1 = TIME_NOW;
    auto res = solver -> solve(Initial, rhsFunc);
    auto t2 = TIME_NOW;
    double cputime = sec_duration(t1, t2);
    recorder_.push_back(cputime);
    timestep_.push_back(TimeStep);
    output_unit(unit, res, index);
    
    //
    auto p = res.end();
    p --;
    Vector numSol = p->second;
    
    Real err = (numSol - Exact).lpNorm<Eigen::Infinity>();
    // std::cout << (numSol - Exact).norm();
    std::cout << "error: "<<  err 
              << ", step: " << res.size() 
              << ", CPUtime: " << cputime << std::endl;
    // std::cout << numSol << std::endl << std::endl;
    return err;
}

DblArray BatchSolver::solve()
{
    int N = root_.size();
    DblArray res;
    recorder_.resize(0);
    timestep_.resize(0);
    for(int i = 0; i < N ; i ++)
    {
        // std::cout << i << std::endl;
        res.push_back(solve_unit(root_[i], i+1));
    }
    output_others(res);
    return res;
}

void BatchSolver::output_unit(const Json::Value &unit, const PointSet_t_U &res, int index)
{
    std::ofstream outputfile;
    cstring filepath = outputPath_ + cstring("/")
            + identifier_ + cstring("_") + std::to_string(index) + (".csv");
    outputfile.open(filepath);
    outputfile << identifier_ << ",";
    outputfile << unit["Method"].asString() << ",";
    if(!unit["Order"].isNull())
        outputfile << unit["Order"].asInt() << ",";
    else
        outputfile << "0,";
    
    double TimeStep;
    if(unit["TimeStep"].isNull())
    {
        double N = unit["StepNum"].asDouble();
        TimeStep = unit["T"].asDouble() / N;
    }
    else
    {
        TimeStep= unit["TimeStep"].asDouble();
    }

    outputfile << unit["RHS"].asString() << ","
               << unit["T"].asDouble() << ","
               << TimeStep << ","
               << index << std::endl; 
    auto it = res.begin();
    outputfile << (it++->second)[0];
    for(; it != res.end() ; it++)
        outputfile << "," << (it->second)[0];
    outputfile << std::endl;
    
    it = res.begin();
    outputfile << (it++->second)[1];
    for(; it != res.end() ; it++)
        outputfile << ", " << (it->second)[1];
    outputfile << std::endl;

    outputfile.close();
}

void BatchSolver::output_others(const DblArray &err)
{
    std::ofstream outputfile;
    // recorder
    cstring filepath = outputPath_ + cstring("/")
            + identifier_ + cstring("_CPUtime.csv");
    outputfile.open(filepath);
    outputfile << identifier_ << ",CPUtime" << std::endl; 
    for(int i = 0 ; i < recorder_.size() ; i ++)
        outputfile << timestep_[i] << "," << recorder_[i] << std::endl;
    outputfile.close();

    // err
    filepath = outputPath_ + cstring("/")
            + identifier_ + cstring("_error.csv");
    outputfile.open(filepath);
    outputfile << identifier_ << ",error" << std::endl; 
    for(int i = 0 ; i < err.size() ; i ++)
        outputfile << timestep_[i] << "," << err[i] << std::endl;
    outputfile.close();
}