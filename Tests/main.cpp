#include <AutoDifferential.h>

class A
{
public:
    A()
    {
        std::cout << "construct" << std::endl;
    }
    A(A &a)
    {
        std::cout << "copy construct" << std::endl;
    }
    A(A&& a)
    {
        std::cout << "move construct" << std::endl;
    }
};

A funcTest()
{
    A a;
    return std::move(a);
}


template<typename T>
void testForward(T&& v) {}

int 
main() 
{
    // const & 右边可以是lvalue或者rvalue
    // & 右边只能是lvalue
    // && 右边只能是rvalue
    A &&a = funcTest();
    int c;
    int && b = 10;

    //万能引用，如果一个变量或者参数被声明为T&&，其中T是被推导的类型，那这个变量或者参数就是一个universal reference
    testForward(1); // case 1
    int x = 1;
    testForward(x); // case 2
    const int& rx = x;
    testForward(rx); // case 2


    return 0;
}

