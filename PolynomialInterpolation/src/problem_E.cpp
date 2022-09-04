#include "PolyInterp.h"

int main(int argc, char** argv)
{
    std::string path("../output/4octave/E.txt");
    std::ofstream cleaning;
    cleaning.open(path, std::ios::out);
    cleaning.close();
    InterpConditions cond;
    double day[7] = {0,6,10,13,17,20,28};
    double sp[2][7] = {{6.67, 17.3, 42.7, 37.3, 30.1, 29.3, 28.7},
                       {6.67, 16.1, 18.9, 15.0, 10.6, 9.44, 8.89}};
    for(int i = 0 ; i < 7 ; i ++)
        (cond.x).push_back(day[i]);
    for(int n = 0 ; n <= 1 ; n ++)
    {
        (cond.fx).clear();
        for(int i = 0 ; i < 7 ; i ++)
        {
            double_array tmp = {sp[n][i]};
            (cond.fx).push_back(tmp);
        }
        NewtonInterp myInterp;
        myInterp.Newton_overwrite(cond);
        Polynomial p(myInterp.get_Polynomial());
        p.output4Matlab(path, n+1);
        std::cout << "For sample " <<n+1 <<", we get the interpolation polynomial:" << std::endl;
        std::cout << p;
    }
    
    return 0;
}