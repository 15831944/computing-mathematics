/**
 * @file Spline.cpp
 * @author MaCheng (Ch.Ma01@outlook.com)
 * @brief implement of Spline.h
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Spline.h"

/// declaration
template<u_int _Deg, SplineType _type>
Spline<1, _Deg, _type> interpolate(const InterpConditions& _cond, BCType _BCType= complete);
template<>
Spline<1, 3, ppForm> interpolate<3, ppForm>(const InterpConditions& _cond, BCType _BCType);

template<u_int _Deg> 
Spline<2, _Deg, ppForm> fitCurve(const vector_Vec2& _points, BCType _BCType = periodic);

/// Utils
inline double factorial(int n)
{
    double s = 1;
    for(int i = 1 ; i <= n ; i ++)
        s*= i;
    return s;
}

inline double combo(int n , int m)
{
    return factorial(n)/(factorial(m) * factorial(n - m));
}

inline double pow1(int n)
{
    return n%2==0?1:-1;
}

/// Implement

template<u_int _Deg>
Spline<2, _Deg, ppForm> fitCurve(const vector_Vec2& _points, BCType _BCType)
{
    std::cerr << "Not Supported." << std::endl;
    return Spline<2, _Deg, ppForm>::NULL_Spline;
}

template<>
Spline<2, 1, ppForm> fitCurve<1>(const vector_Vec2& _points, BCType _BCType)
{
    Spline<2, 1, ppForm> res;
    auto &list_t = res.interpPoints;
    list_t.push_back(0);
    Vec2 P0 = _points[0];
    for(auto it = _points.begin() + 1; it < _points.end() ; it ++)
        list_t.push_back(list_t[list_t.size()-1] + dist(*(it-1), *it));
    auto it_p = _points.begin();
    for(auto it = list_t.begin() ; it < list_t.end()-1 && it_p < _points.end() - 1 ; it ++, it_p++)
    {
        Vec2 P1 = *it_p;    Vec2 P2 = *(it_p+1);
        double t1 = *it;    double t2 = *(it+1);
        Vec2 A0 = (P1*t2-P2*t1) / (t2-t1);
        Vec2 A1 = (P2-P1)/(t2-t1);
        (res.poly4ppForm).push_back(Polynomial<1, 2>(vector_Vec2{A0,A1}));
    }
    return res;
}

template<>
Spline<2, 3, ppForm> fitCurve<3>(const vector_Vec2& _points, BCType _BCType)
{
    Spline<2, 3, ppForm> res;
    auto &list_t = res.interpPoints;
    list_t.push_back(0);
    vector2_double x_coord = {{_points[0][0]}}, y_coord = {{_points[0][1]}};
    Vec2 P0 = _points[0];
    for(auto it = _points.begin() + 1; it < _points.end() ; it ++)
    { 
        x_coord.push_back(vector_double{(*it)[0]});
        y_coord.push_back(vector_double{(*it)[1]});
        list_t.push_back(list_t[list_t.size()-1] + dist(*(it-1), *it));
    }

    InterpConditions cond;
    Spline<1, 3, ppForm> x_spline;
    cond.x = list_t;
    cond.fx = x_coord;
    x_spline = interpolate<3, ppForm>(cond, notAknot);

    Spline<1, 3, ppForm> y_spline;
    cond.fx = y_coord;
    y_spline = interpolate<3, ppForm>(cond, notAknot);

    ///combine
    for(int i = 0 ; i < list_t.size() - 1 ; i ++)
    {
        Polynomial<3, 2> tmp;
        for(int j = 0 ; j <= 3 ; j ++)
        {
            double cx = (x_spline.poly4ppForm[i]).get_Coef(j)[0];
            double cy = (y_spline.poly4ppForm[i]).get_Coef(j)[0];
            tmp.set_Coef(j, Vec2{cx,cy});
        }
        res.poly4ppForm.push_back(tmp);
    }
    
    return res;
}


template<u_int _Deg, SplineType _type> 
Spline<1, _Deg, _type> interpolate(const InterpConditions& _cond, BCType _BCType)
{
    std::cerr << "Not Supported." << std::endl;
    return Spline<1, _Deg, _type>::NULL_Spline;
}

template<>
Spline<1, 3, ppForm> interpolate<3, ppForm>(const InterpConditions& _cond, BCType _BCType)
{
    Spline<1, 3, ppForm> res;
    for(auto it = (_cond.x).begin() ; it < (_cond.x).end() ; it ++)
        (res.interpPoints).push_back(*it);
    if(_BCType == complete)
        cubic_complete(_cond, res);
    else if(_BCType == notAknot)
        cubic_notAknot(_cond, res);
    else ///< _BCType == periodic
        cubic_periodic(_cond, res);
    return res;    
}

int cubic_complete(const InterpConditions& _cond, Spline<1, 3, ppForm>& _res)
{
    /**
     * Boundary condition.
     * s'(f;a) = f'(a) & s'(f;b) = f'(b)
     */
    typedef Vec<double, 1> Vec_1;
    auto &x = _cond.x;
    auto &f = _cond.fx;

    vector_double DL, D, DU, b;
    auto &res_poly = _res.poly4ppForm;

    for(int i = 0 ; i < x.size() ; i ++)
    {
        if(i == 0) //< 2M(1) + M(2) = 6f[x(1),x(1),x(2)]
        {
            double t = 6 * ( (f[i+1][0] - f[i][0])/(x[i+1] - x[i]) - f[i][1] ) / (x[i+1] - x[i]);
            b.push_back(t);
            D.push_back(2);
            DU.push_back(1);
        }
        else if(i == x.size() - 1) ///< M(N-1) + 2M(N) = 6f[x(N-1),x(N),x(N)]
        {
            double t = 6 * ( f[i][1] - (f[i][0]-f[i-1][0])/(x[i]-x[i-1]) ) / (x[i] - x[i-1]); 
            b.push_back(t);
            D.push_back(2);
            DL.push_back(1);
        }
        else
        {
            double mu = (x[i] - x[i-1]) / (x[i+1] - x[i-1]);
            double lambda = 1 - mu;
            double t = 6 * ( (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - (f[i][0]-f[i-1][0])/(x[i]-x[i-1]) ) 
                        / (x[i+1] - x[i-1]);
            b.push_back(t);
            DU.push_back(lambda);
            D.push_back(2);
            DL.push_back(mu);
        }
    }
    solve_tridiag(DL, D, DU, b);
    double x0, x1, t0, t1, t2, t3, a0, a1, a2, a3;
    for(int i = 0 ; i < b.size() - 1; i ++)
    {
        /**
         * p(x) = t0 + t1(x-x0) + t2(x-x0)^2 + t3(x-x0)^3
         *      = a0 + a1 x + a2 x^2 + a3 x^3
         */
        //if(i == 0)
            //t1 = f[i][1];
        x0 = x[i];
        x1 = x[i + 1];
        t0 = f[i][0];
        t1 = (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - (x[i+1]-x[i])/2*b[i] - (x[i+1]-x[i])/6*(b[i+1]-b[i]);
        t2 = b[i] / 2;
        t3 = (b[i+1] - b[i]) / (x[i+1] - x[i]) / 6;
        a0 = t0 - t1*x0 + t2*x0*x0 - t3*x0*x0*x0;
        a1 = t1 - 2*x0*t2 + 3*t3*x0*x0;
        a2 = t2 - 3*t3*x0;
        a3 = t3;
        res_poly.push_back(Polynomial<3, 1>
            (std::vector<Vec_1>{Vec_1{a0},Vec_1{a1},Vec_1{a2},Vec_1{a3}}));
        //t1 = t1 + 2*t2*(x1-x0) + 3*t3*(x1-x0)*(x1-x0);
    }
    return 0;
}

int cubic_notAknot(const InterpConditions& _cond, Spline<1, 3, ppForm>& _res)
{
    /**
     * Boundary condition.
     * s'''(f;x) exists at x=x_2 and x=x_{N-1}
     */
    typedef Vec<double, 1> Vec_1;
    auto &x = _cond.x;
    auto &f = _cond.fx;
    const int N = x.size();

    vector_double DL, D, DU, b;
    auto &res_poly = _res.poly4ppForm;

    for(int i = 1 ; i < x.size() - 1 ; i ++)
    {
        double t = 6 * ( (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - (f[i][0]-f[i-1][0])/(x[i]-x[i-1]) ) 
                        / (x[i+1] - x[i-1]);
        if(i == 1)
        {
            double tmp1 = 2 + (x[1]-x[0])/(x[2]-x[1]);
            double tmp2 = -std::pow((x[1]-x[0]),2)/((x[2]-x[0])*(x[2]-x[1])) + (x[2]-x[1])/(x[2]-x[0]);
            b.push_back(t);
            D.push_back(tmp1);
            DU.push_back(tmp2);
        }
        else if(i == x.size() - 2) 
        {
            double tmp1 = -std::pow((x[N-1]-x[N-2]),2)/((x[N-1]-x[N-3])*(x[N-2]-x[N-3])) + (x[N-2]-x[N-3])/(x[N-1]-x[N-3]);
            double tmp2 = 2 + (x[N-1]-x[N-2])/(x[N-2]-x[N-3]);
            b.push_back(t);
            D.push_back(tmp2);
            DL.push_back(tmp1);
        }
        else
        {
            double mu = (x[i] - x[i-1]) / (x[i+1] - x[i-1]);
            double lambda = 1 - mu;
            b.push_back(t);
            DU.push_back(lambda);
            D.push_back(2);
            DL.push_back(mu);
        }
    }

    solve_tridiag(DL, D, DU, b);
    double M1 = (x[2]-x[0])/(x[2]-x[1])*b[0] - (x[1]-x[0])/(x[2]-x[1])*b[1];
    b.insert(b.begin(), M1);
    double MN = -(x[N-1]-x[N-2])/(x[N-2]-x[N-3])*b[N-3] + (x[N-1]-x[N-3])/(x[N-2]-x[N-3])*b[N-2];
    b.push_back(MN);

    double x0, x1, t0, t1, t2, t3, a0, a1, a2, a3;
    for(int i = 0 ; i < b.size() - 1; i ++)
    {
        /**
         * p(x) = t0 + t1(x-x0) + t2(x-x0)^2 + t3(x-x0)^3
         *      = a0 + a1 x + a2 x^2 + a3 x^3
         */
        x0 = x[i];
        t0 = f[i][0];
        t1 = (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - b[i]*(x[i+1]-x[i])/2 - (x[i+1]-x[i])/6*(b[i+1]-b[i]);
        t2 = b[i] / 2;
        t3 = (b[i+1] - b[i]) / (x[i+1] - x[i]) / 6;
        a0 = t0 - t1*x0 + t2*x0*x0 - t3*x0*x0*x0;
        a1 = t1 - 2*x0*t2 + 3*t3*x0*x0;
        a2 = t2 - 3*t3*x0;
        a3 = t3;
        res_poly.push_back(Polynomial<3, 1>
            (std::vector<Vec_1>{Vec_1{a0},Vec_1{a1},Vec_1{a2},Vec_1{a3}}));
    }
    return 0;
}

int cubic_periodic(const InterpConditions& _cond, Spline<1, 3, ppForm>& _res)
{
    /**
     * Boundary condition.
     * s(f;b) = s(f;a) & s'(f;b) = s'(f;a) & s''(f;b) = s''(f;a)
     */
    typedef Vec<double, 1> Vec_1;
    auto &x = _cond.x;
    auto f = _cond.fx;
    const int N = x.size();
    f[N-1][0] = f[0][0];

    vector2_double A;
    vector_double b;
    auto &res_poly = _res.poly4ppForm;

    for(int i = 0 ; i < x.size(); i ++)
    {
        
        if(i == 0)
        {
            vector_double tmp;
            double t = (f[1][0]-f[0][0])/(x[1]-x[0])-(f[0][0]-f[N-2][0])/(x[N-1]-x[N-2]);
            double t1 = (x[N-1]-x[N-2]+x[1]-x[0])/3.0;
            double t2 = (x[1]-x[0])/6.0;
            double t3 = (x[N-1]-x[N-2])/6.0;
            tmp.push_back(t1); tmp.push_back(t2); tmp.insert(tmp.end(),N-4,0); tmp.push_back(t3);
            b.push_back(t);
            A.push_back(tmp);
        }
        else if(i == x.size() - 1)
        {
            vector_double tmp;
            tmp.push_back(1); tmp.insert(tmp.end(),N-2,0); tmp.push_back(-1);
            b.push_back(0);
            A.push_back(tmp);
        }
        else 
        {
            double t = 6 * ( (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - (f[i][0]-f[i-1][0])/(x[i]-x[i-1]) ) 
                        / (x[i+1] - x[i-1]);
            vector_double tmp;
            tmp.insert(tmp.begin(), i-1, 0);
            double mu = (x[i] - x[i-1]) / (x[i+1] - x[i-1]);
            double lambda = 1 - mu;
            tmp.push_back(mu); tmp.push_back(2); tmp.push_back(lambda);
            b.push_back(t);
            A.push_back(tmp);
        }
    }

    //std::cout << A.size() << " " << b.size() << std::endl;

    solve_general(A, b);

    double x0, x1, t0, t1, t2, t3, a0, a1, a2, a3;
    for(int i = 0 ; i < b.size() - 1; i ++)
    {
        /**
         * p(x) = t0 + t1(x-x0) + t2(x-x0)^2 + t3(x-x0)^3
         *      = a0 + a1 x + a2 x^2 + a3 x^3
         */
        x0 = x[i];
        t0 = f[i][0];
        t1 = (f[i+1][0]-f[i][0])/(x[i+1]-x[i]) - b[i]*(x[i+1]-x[i])/2 - (x[i+1]-x[i])/6*(b[i+1]-b[i]);
        t2 = b[i] / 2;
        t3 = (b[i+1] - b[i]) / (x[i+1] - x[i]) / 6;
        a0 = t0 - t1*x0 + t2*x0*x0 - t3*x0*x0*x0;
        a1 = t1 - 2*x0*t2 + 3*t3*x0*x0;
        a2 = t2 - 3*t3*x0;
        a3 = t3;
        res_poly.push_back(Polynomial<3, 1>
            (std::vector<Vec_1>{Vec_1{a0},Vec_1{a1},Vec_1{a2},Vec_1{a3}}));
    }
    return 0;
}

template<>
Spline<1, 3, cardinalB> interpolate<3, cardinalB>(const InterpConditions& _cond, BCType _BCType)
{
    auto &x = _cond.x;
    auto &f = _cond.fx;
    Spline<1, 3, cardinalB> res;
    auto &res_coef = res.coef4candinalB;

    const int N = x.size();
    vector_double DU(N-1 ,1), D(N,4), DL(N-1,1), b;
    DU[0] = 2; DL[DL.size()-1] = 2;
    for(int i = 1 ; i <= N ; i ++)
    {
        if(i == 1)
            b.push_back(6*f[0][0]+2*f[0][1]);
        else if(i == N)
            b.push_back(6*f[N-1][0]-2*f[N-1][1]);
        else
            b.push_back(6 * f[i-1][0]);
    }
    solve_tridiag(DL, D, DU, b);
    b.push_back(b[N-2]+2*f[N-1][1]);
    b.insert(b.begin(), b[1]-2*f[0][1]);
    /*for(int i = 0 ; i < b.size() ; i ++)
        std::cout << b[i] << " ";
    std::cout << std::endl;*/
    for(int i = -1 ; i <= N ; i ++)
        res_coef.insert(P_INT_DOUBLE(i+x[0]-1, b[i+1]));
    return res;
}

template<>
Spline<1, 2, cardinalB> interpolate<2, cardinalB>(const InterpConditions& _cond, BCType _BCType)
{
    auto &x = _cond.x;
    auto &f = _cond.fx;
    Spline<1, 2, cardinalB> res;
    auto &res_coef = res.coef4candinalB;

    const int N = x.size() - 1;
    vector_double DU(N-2 ,1), D, DL(N-2,1), b;
    D.push_back(5); D.insert(D.end(), N-3, 6); D.push_back(5);

    for(int i = 1 ; i <= N - 1; i ++)
    {
        if(i == 1)
            b.push_back(8*f[i][0] - 2*f[i-1][0]);
        else if(i == N-1)
            b.push_back(8*f[i][0] - 2*f[i+1][0]);
        else
            b.push_back(8*f[i][0]);
    }
    solve_tridiag(DL, D, DU, b);
    b.push_back(2*f[N][0] - b[N-2]);
    b.insert(b.begin(), 2*f[0][0] - b[0]);

    for(int i = 0 ; i <= N ; i ++)
        res_coef.insert(std::pair<int,double>(i+x[0]-1, b[i]));
    return res;
}

template<u_int _Dim, u_int _Degree, SplineType _t>
std::map<double, Vec<double,_Dim>>  
    Spline<_Dim, _Degree, _t>::scanning(double _begin, double _end, double _step)
{
    std::map<double, Vec<double,_Dim>> res;
    if(_begin == 0 && _end == 0)
    {
        if(_t == ppForm)
        {
            _begin = interpPoints[0];
            _end = *(interpPoints.end()-1);
        }
        else
            return res;
    }
    if((_begin >= _end) ||
       ((_t == ppForm) && ( _begin + EPSILON < *(interpPoints.begin()) || _end - EPSILON > *(interpPoints.end()-1) )))
        return res;
    for(double t = _begin; t <= _end; t += _step)
        res.insert(std::pair<double, Vec<double,_Dim>>(t, (*this)(t)));

    if(res.count(_end) == 0)
        res.insert(std::pair<double, Vec<double,_Dim>>(_end, (*this)(_end)));
    return res;
}

template<u_int _Dim, u_int _Degree, SplineType _t>
Vec<double, _Dim> Spline<_Dim, _Degree, _t>::operator()(double _x) const
{
    if(_t == ppForm)
    {
        if(interpPoints.empty()) 
            return D_MAX;
        if(_x < *(interpPoints.begin()))
            return (*(poly4ppForm.begin()))(_x);
        if(_x > *(interpPoints.end()-1))
            return (*(poly4ppForm.end()-1))(_x);
        auto it_p = poly4ppForm.begin();
        auto it_x = interpPoints.begin()+1;
        for(;it_p < poly4ppForm.end() && it_x < interpPoints.end();
             it_p++, it_x++)
        {
            if(_x >= *(it_x-1) && _x <= *it_x)
                return (*it_p)(_x);
        }
    }
    else ///< _t = cardinalB
    {
        double n = _Degree, sum = 0;
        auto it = coef4candinalB.begin();
        for(; it != coef4candinalB.end(); it++)
        {
            double i = it -> first;
            for(int k = -1 ; k <= n ; k ++)
                if(k + i > _x)
                    sum += (it -> second)*pow1(n-k)*combo(n+1,k+1)*std::pow(k+i-_x,n);
        }
        return Vec<double,_Dim>{sum / factorial(n)};
    }
}

template<u_int _Dim, u_int _Degree, SplineType _t>
std::ostream& operator<< (std::ostream& output, const Spline<_Dim, _Degree, _t>& _spline)
{
    if(_t == ppForm)
    {
        /**
         * Output for ppForm Spline.
         */
        auto it1 = (_spline.interpPoints).begin();
        auto it2 = (_spline.poly4ppForm).begin();
        for( ; it1 < (_spline.interpPoints).end()-1 && it2 < (_spline.poly4ppForm).end(); 
             it1 ++, it2 ++)
        {
            output << "Cubic polynomial between " << *it1 << " and " << *(it1 + 1) << ": " << std::endl;
            output << *it2;
        }
    }
    else
    {
        /**
         * Output for candinalB Spline.
         */
        ;
    }
    return output;
}

