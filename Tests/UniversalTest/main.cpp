
#include <TupleArray.h>

#include <iostream>

int
main()
{
  TupleArray<int, 3> intArray(1, 2, 3);
  std::cout << "intArray[0]: " << intArray.at(0) << std::endl;
  std::cout << "intArray[1]: " << intArray.at(1) << std::endl;
  std::cout << "intArray[2]: " << intArray.at(2) << std::endl;

  TupleArray<double, 2> doubleArray(1.1, 2.2);
  std::cout << "doubleArray[0]: " << doubleArray.at(0) << std::endl;
  std::cout << "doubleArray[1]: " << doubleArray.at(1) << std::endl;

  TupleArray<std::common_type_t<int, double>, 2> mixedArray(1, 2.2);
  std::cout << "mixedArray[0]: " << mixedArray.at(0) << std::endl;
  std::cout << "mixedArray[1]: " << mixedArray.at(1) << std::endl;

  return 0;
}
