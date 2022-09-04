#include "PolyInterp.h"

int main(int argc, char** argv)
{
    std::string path("../output/4octave/D.txt");
    std::ofstream cleaning;
    cleaning.open(path, std::ios::out);
    cleaning.close();
    InterpConditions cond;
    double time[5] = {0,3,5,8,13};
    double distance_speed[5][2] = {{0, 75},{225,77},{383,80},{623,74},{993,72}};
    for(int i = 0 ; i < 5 ; i ++)
    {
        double_array tmp = {distance_speed[i][0],distance_speed[i][1]};
        (cond.x).push_back(time[i]);
        (cond.fx).push_back(tmp);
    }
    NewtonInterp myInterp;
    myInterp.Newton_overwrite(cond);
    Polynomial p(myInterp.get_Polynomial());
    Polynomial diff_p(p.diff());
    ///< (a)
    std::cout << "The interpolation polynomial is" << std::endl;
    std::cout << p;
    printf("The approximate poisition of the car is %.5f.\n", p(10));
    printf("The approximate speed of the car is %.5f.\n", diff_p(10));
    ///< (b)    
    diff_p.output4Matlab(path);
    return 0;
}