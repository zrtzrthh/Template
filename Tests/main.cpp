#include <AutoDifferential.h>

int 
main() 
{

    //AutoDiff<double, double> x(2.0, 0.0); 
    //x.setDerivative<0>(1.0); 

    //AutoDiff<double, double> y(0.0, 3.0); 
    //y.setDerivative<1>(1.0); 

    //AutoDiff<double, double> z = x * x + y * y;

    //std::cout << "f(x, y) = " << std::get<0>(z.values) + std::get<1>(z.values) << std::endl;
    //std::cout << "df/dx = " << std::get<0>(z.derivatives) << std::endl;
    //std::cout << "df/dy = " << std::get<1>(z.derivatives) << std::endl;

    print();

    return 0;
}
