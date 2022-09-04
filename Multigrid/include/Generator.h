/**
 * @file Generator.h
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include "conditions.h"
#include "global.h"

template<int dim>
class Generator_base
{
public:
    Conditions<dim> &cond;
    int coarsest_N;

    virtual int generate(std::vector<SparseMatrix>& _Matrix, VectorXd& _f) = 0;
    Generator_base(Conditions<dim> &_cond, int _N = 4):cond(_cond), coarsest_N(_N){;};
};


template<int dim> class Generator;

template<>
class Generator<1>:public Generator_base<1>
{
public:
    virtual int generate(std::vector<SparseMatrix>& _Matrix, VectorXd& _f) override;
    Generator(Conditions<1> &_cond, int _N = 4): Generator_base(_cond, _N){;};
};

template<>
class Generator<2>:public Generator_base<2>
{
public:
    Generator(Conditions<2> &_cond, int _N = 4): Generator_base(_cond, _N){;};
    virtual int generate(std::vector<SparseMatrix>& _Matrix, VectorXd& _f) override;
    int gen_regular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
    int gen_irregular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
};

// template<>
// class Generator<2>:public Generator_base
// {
// public:
//     Conditions<2> &cond;
//     Generator(Conditions<2> &_cond, int _N = 4): Generator_base(_N), cond(_cond){;};
//     int gen_regular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
//     int gen_irregular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
// }

// template<int dim>
// class Generator
// {
// public:
//     Conditions<dim> &cond;
//     int coarsest_N;

//     Generator(Conditions<dim> &_cond, int _coarsest = 4): cond(_cond), coarsest_N(_coarsest){;};
//     int generate(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
//     int gen_dim1(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
//     int gen_dim2_regular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
//     int gen_dim2_irregular(std::vector<SparseMatrix>& _Matrix, VectorXd& _f);
// };

#endif