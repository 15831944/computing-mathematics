/**
 * @file myJson2.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief generate json for: 
 * u(x,y) = exp(y + sin(x)) \n
 * domain: square minus a circle whoes center is at the center of square \n 
 * boundary conditions: Dirichlet.
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "FD.h"
#include "conditions.h"
#include "global.h"
#include "genJson.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <math.h>


double f(double x, double y)
{
    return std::exp(y + std::sin(x))*std::sin(x) - std::exp(y + std::sin(x)) - std::exp(y + std::sin(x))*std::cos(x)*std::cos(x);
}

double u(double x, double y)
{
    return std::exp(y + std::sin(x));
}

int main()
{
    double n_set[4] = {8, 16, 32, 64};
    double1d n_list(n_set, n_set+4);
    
    for(auto n: n_list)
    {
        genJson myjson(1/n);
        cstring path = cstring("../json/f2_N")+std::to_string(int(n))+cstring(".json");
        myjson.set_circ(Vec(0.5,0.5), 0.15);
        myjson.set_fval(f);
        myjson.set_BV0(u);
        myjson.write_json(path);
    }
    return 0;
}