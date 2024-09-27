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
    // const & �ұ߿�����lvalue����rvalue
    // & �ұ�ֻ����lvalue
    // && �ұ�ֻ����rvalue
    A &&a = funcTest();
    int c;
    int && b = 10;

    //�������ã����һ���������߲���������ΪT&&������T�Ǳ��Ƶ������ͣ�������������߲�������һ��universal reference
    testForward(1); // case 1
    int x = 1;
    testForward(x); // case 2
    const int& rx = x;
    testForward(rx); // case 2

    return 0;
}

