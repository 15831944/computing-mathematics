#ifndef __PolyInterp_CPP__
#define __PolyInterp_CPP__

#include "PolyInterp.h"

/**
 * @brief Struct InterpConditions
 * 
 */
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

/**
 * @brief Class Polynomial
 * 
 */
Polynomial::Polynomial()
{
    coefficient.push_back(0);
}

Polynomial::Polynomial(const double_array& _coefficient)
{
    for(double_array_const_it it = _coefficient.begin(); it < _coefficient.end(); it ++)
        coefficient.push_back(*it);
}

Polynomial::Polynomial(const Polynomial& _p)
{
    double_array_const_it it = (_p.coefficient).begin();
    for(; it < (_p.coefficient).end() ; it ++)
    {
        coefficient.push_back(*it);
    }
}

int Polynomial::set_coefficient(const double_array& _coefficient)
{
    coefficient.clear();
    for(double_array_const_it it = _coefficient.begin(); it < _coefficient.end(); it ++)
        coefficient.push_back(*it);
    return 0;
}

int Polynomial::get_degree() const
{
    return coefficient.size() - 1;
}

int Polynomial::refresh()
{
    double_array_it it = coefficient.end();
    it --; ///< it refers to the last element in coefficient
    for(; it > coefficient.begin(); it -- )
    {
        if(*it != 0)
            break;
        coefficient.pop_back();
    }
    return 0;
}

///< Derivation
Polynomial Polynomial::diff()
{
    refresh();
    if(get_degree() == 0)
    {    
        double_array result;
        result.push_back(0);
        return Polynomial(result);
    }
    else
    {
        double_array result(coefficient.size() - 1, 0);
        for(int i = get_degree(); i >= 1 ; i --)
        {
            result[i - 1] = i * coefficient[i];
        }
        return Polynomial(result);
    }
}
Polynomial Polynomial::diff(int _n)
{
    refresh();
    if(_n < 0)  
    {
        return POLY_NULL;
    }
    else if(_n == 0)
    {
        return Polynomial(*this);
    }
    else
    {
        Polynomial p(*this);
        for(int i = 1 ; i <= _n ; i ++)
            p = p.diff();
        return p;
    }
}

int Polynomial::output4Matlab(const std::string& path, int _n)
{
    std::ofstream outfile;
    outfile.open(path, std::ios::app);
    outfile << "p" << _n <<" = ";
    refresh(); ///< delete the monic zeros in coefficient.
    double_array_const_it it = coefficient.end();
    it --; ///< it refers to the last element in coefficient
    int n = coefficient.size() - 1;
    if(it == coefficient.begin()) ///< degree = 0
    {
        outfile << *it <<";" << std::endl;
        return 0;
    }
    outfile << *it << "* x.^" << n;
    it --; n --;

    for(; it >= coefficient.begin(); it --, n --)
    {
        if((*it)!= 0)
        {
            if(n != 0)
                outfile << " + " << *it << " * x.^" << n;
            else
                outfile << " + " << *it;
        }
    }
    outfile << ";" << std::endl;
    outfile.close();
    return 0;
}

///< Assignment operator
Polynomial& Polynomial::operator=(const Polynomial& _p)
{
    coefficient.clear();
    const double_array &c = _p.coefficient;
    for(double_array_const_it it = c.begin(); it < c.end() ; it ++)
        coefficient.push_back(*it);
    return *this;
}
Polynomial& Polynomial::operator=(const double c)
{
    coefficient.clear();
    coefficient.push_back(c);
    return *this;
}

///< Equiv operator
bool Polynomial::operator== (const Polynomial& _p) const
{
    int n1, n2;
    for(int i = get_degree(); i >= 0 ; i --)
    {
        if(coefficient[i] != 0)
        {
            n1 = i;
            break;
        }
    }
    for(int i = _p.get_degree(); i >= 0 ; i --)
    {
        if(_p.coefficient[i] != 0)
        {
            n2 = i;
            break;
        }
    }
    if(n1 != n2)
        return false;
    for(int i = n1 ; i >= 0 ; i --)
    {
        if(std::abs(coefficient[i] - _p.coefficient[i]) > 1e-10)
            return false;
    }
    return true;
}

///< Addition operator
Polynomial Polynomial::operator+(const Polynomial& _p) const
{
    double_array result(std::max((_p.coefficient).size(),coefficient.size()), 0);
    for(int i = 0 ; i < coefficient.size(); i++)
    {
        result[i] += coefficient[i];
    }
    for(int i = 0 ; i < (_p.coefficient).size(); i++)
    {
        result[i] += (_p.coefficient)[i];
    }
    Polynomial p(result);
    return p;
}

Polynomial Polynomial::operator+(double _t) const
{
    double_array result(coefficient);
    result[0] = result[0] + _t;
    Polynomial p(result);
    return p;
}
Polynomial operator+(double _t, const Polynomial& _p)
{
    double_array result(_p.coefficient);
    result[0] = result[0] + _t;
    Polynomial p(result);
    return p;
}

///< Subtraction operator
Polynomial Polynomial::operator-() const
{
    double_array result;
    double_array_const_it it = coefficient.begin();
    for(; it < coefficient.end(); it ++)
    {
        result.push_back(-(*it));
    }
    Polynomial p(result);
    return p;
}
Polynomial Polynomial::operator-(const Polynomial& _p) const
{
    return (*this) + (-_p);
}
Polynomial Polynomial::operator- (double _t) const
{
    return (*this) + (-_t);
}
Polynomial operator- (double _t, const Polynomial& _p)
{
    return _t + (-_p);
}

///< Multiplication operator
Polynomial Polynomial::operator*(const Polynomial& _p) const
{
    const double_array &c1 = coefficient;
    const double_array &c2 = _p.coefficient;
    double_array result((c1.size()-1) + (c2.size()-1) + 1 , 0);
    for(int i = 0 ; i < c1.size(); i ++)
    {
        for(int j = 0 ; j < c2.size(); j ++)
        {
            result[i + j] += c1[i] * c2[j];
        }
    }
    Polynomial p(result);
    p.refresh();
    return p;
}
Polynomial Polynomial::operator* (double _t) const
{
    double_array result(coefficient);
    for(int i = 0 ; i < coefficient.size() ; i ++)
    {
        result[i] *= _t;
    }
    Polynomial p(result);
    p.refresh();
    return p;
}
Polynomial operator* (double _t, const Polynomial& _p)
{
    double_array result(_p.coefficient);
    for(int i = 0 ; i < (_p.coefficient).size() ; i ++)
    {
        result[i] *= _t;
    }
    Polynomial p(result);
    p.refresh();
    return p;
}

///< Evaluation at some x
double Polynomial::operator()(double _x) const
{
    double result = 0;
    for(int i = 0 ; i < coefficient.size() ; i ++)
        result += coefficient[i] * std::pow(_x, i);
    return result;
}

///< Ostream operator
std::ostream& operator<< (std::ostream& output, Polynomial& _p)
{
    _p.refresh(); ///< delete the monic zeros in coefficient.
    double_array_const_it it = (_p.coefficient).end();
    it --; ///< it refers to the last element in coefficient
    int n = (_p.coefficient).size() - 1;
    if(it == (_p.coefficient).begin()) ///< degree = 0
    {
        std::cout << *it << std::endl;
        return output;
    }
    std::cout << *it << " x^" << n;
    it --; n --;

    for(; it >= (_p.coefficient).begin(); it --, n --)
    {
        if((*it)!= 0)
        {
            if(n != 0)
                std::cout << " + " << *it << " x^" << n;
            else
                std::cout << " + " << *it;
        }
    }
    std::cout << std::endl;
    return output;
}

///< Istream operator
std::istream& operator>> (std::istream& input, Polynomial& _p)
{
    int degree;
    (_p.coefficient).clear();
    std::cout << "Input the degree of polynomial: ";
    std::cin >> degree;
    std::cout << "Input all the coefficients(degree ascending): " << std::endl;
    for(int i = 0 ; i <= degree ; i ++)
    {
        double tmp;
        std::cin >> tmp;
        (_p.coefficient).push_back(tmp);
    }
    return input;
}

/**
 * @brief Class NewtonInterp
 *  
 */
int NewtonInterp::getPolyfromTable()
{
    Polynomial result;
    Polynomial p;
    result = tableOfDividedDiffs[0][1];
    p = 1;
    for(int i = 1 ; i < tableOfDividedDiffs.size() ; i ++)
    {
        double_array x0 = {-tableOfDividedDiffs[i - 1][0], 1};
        Polynomial p0(x0);
        p = p * p0;
        double t = tableOfDividedDiffs[i][i+1];
        result = result + t * p;
    }
    interPoly = result;
    return 0;
}

double NewtonInterp::Neville_Aitken(struct InterpConditions _points, double _x)
{
    if(_points.get_max_diff() != 0)
        return D_MAX;
    
    double2_array table;
    int n = (_points.x).size() - 1;
    for(int i = 0 ; i <= n; i ++)
    {
        double_array tmp = {_points.fx[i][0]};
        table.push_back(tmp);
    }

    for(int k = 0 ; k < n ; k ++)
    {
        for(int i = 0; i < n - k ; i ++)
        {
            double t;
            t = ((_x-_points.x[i])*table[i+1][k]-(_x-_points.x[i+k+1])*table[i][k]) 
                / (_points.x[i+k+1]-_points.x[i]);
            table[i].push_back(t);
        }
    }
    return table[0][n];
}

int NewtonInterp::Newton_overwrite(const struct InterpConditions _points)
{
    int N = _points.get_N();
    const double_array &x = _points.x;
    const double2_array &fx = _points.fx;
    double2_array &table = tableOfDividedDiffs;
    tableOfDividedDiffs.clear(); 
    for(int i = 0; i < fx.size() ; i ++)
    {
        double_array t = {x[i], fx[i][0]};
        for(int j = 1 ; j <= (fx[i]).size(); j ++)
            table.push_back(t);
    }
    
    for(int i = 2 ; i <= N; i ++)
    {
        for(int j = i - 1 ; j <= N - 1 ; j ++)
        {
            if(table[j - i + 1][0] == table[j][0])
                table[j].push_back(fx[_points.find_x(table[j][0])][i-1] / factorial(i-1));
            else
            {
                double tmp = (table[j][i-1] - table[j-1][i-1]) / (table[j][0] - table[j-i+1][0]);
                table[j].push_back(tmp);
            }
        }
    }

    getPolyfromTable();
    return 0;
}

int NewtonInterp::Newton_addition(const struct InterpConditions _points)
{
    InterpConditions all_cond;
    double2_array &table = tableOfDividedDiffs;
    Polynomial &p = interPoly;
    for(int i = 0 ; i < table.size(); i ++)
    {
        double t = table[i][0];
        double_array fx0;
        int j = 0;
        (all_cond.x).push_back(t);
        while(i < table.size() && t == table[i][0])
        {
            if(j == 0)
                fx0.push_back(p(t));
            else
            {               
                Polynomial tmp(p.diff(j));
                fx0.push_back(tmp(t));
            }
            i ++;
            j ++;
        }
        i --;
        (all_cond.fx).push_back(fx0); 
    }
    for(int i = 0 ; i < (_points.x).size(); i ++)
    {
        double t = _points.x[i];
        if(all_cond.find_x(t) != -1)
            return -1; 
        (all_cond.x).push_back(t);
        (all_cond.fx).push_back(_points.fx[i]);
    }
    Newton_overwrite(all_cond);
    return 0;
}


Polynomial NewtonInterp::get_Polynomial()
{
    return interPoly;
}

double factorial(int n)
{
    double sum = 1;
    for(int i = 1 ; i <= n ; i ++)
        sum *= i;
    return sum;
}

#endif