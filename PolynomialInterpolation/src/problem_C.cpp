#include "PolyInterp.h"

double func(double x)
{
    return 1 / (1 + 25 * x * x);
}

int main(int argc, char** argv)
{
    std::string path("../output/4octave/C.txt");
    std::ofstream cleaning;
    cleaning.open(path, std::ios::out);
    cleaning.close();
    for(int n = 5; n <= 20; n += 5)
    {
        ///< compute interpolation points
        InterpConditions cond;
        for(int i = 1 ; i <= n ; i ++)
        {
            double xi = std::cos((2*i-1)/(double)(2*n)*M_PI);
            double_array fxi;
            (cond.x).push_back(xi);
            fxi.push_back(func(xi));
            (cond.fx).push_back(fxi);
        }

        ///< interpolation
        NewtonInterp myInterp;
        myInterp.Newton_overwrite(cond);
        class Polynomial p(myInterp.get_Polynomial());
        printf("While n = %d, the interpolation polynomial is\n", n);
        std::cout << p;
        p.output4Matlab(path, n);
    }
    return 0;
}