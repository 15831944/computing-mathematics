/**
 * @file InterpConditions.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief implement of InterpConditions.h
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "InterpConditions.h"

int InterpConditions::get_max_diff() const
{
    int m = 0;
    for(int i = 0 ; i < x.size(); i ++)
    {
        if(fx[i].size()-1 > m)
            m = fx[i].size()-1;
    }
    return m;
}

int InterpConditions::get_N() const
{
    int s = 0;
    for(int i = 0 ; i < fx.size(); i ++)
        s += fx[i].size();
    return s;
}

int InterpConditions::find_x(double _x) const
{
    for(int i = 0 ; i < x.size(); i ++)
    {
        if(x[i] == _x)
            return i;
    }
    return -1;
}

std::istream& operator>> (std::istream& input, InterpConditions& _interp)
{
    int n;
    (_interp.x).clear();
    (_interp.fx).clear();
    std::cout << "Please input the number of points: ";
    std::cin >> n;
    std::cout << "Input x, f(x), f'(x), ... in each line." << std::endl;
    for(int i = 1 ; i <= n ; i ++)
    {
        double t;
        double_array tmp;
        int f = 1;
        while(std::cin >> t)
        {
            if(f == 1)
            {
                (_interp.x).push_back(t);
                f = 0;
            }
            else
                tmp.push_back(t);
            
            if(std::cin.get() == '\n')
                break;
        }
        (_interp.fx).push_back(tmp);
    }
    return input;
}