/** Parisa Nawar - PXN210032
  */
#include <iostream>
#include "Rectangle.h"

using namespace std;

int main() {
  Rectangle rect1(12.0, 2.0);
  Rectangle rect2 = rect1;

  rect1.setLength(3.0);
  rect1.setWidth(5.0);

  cout << "Rectangle 1:" << rect1;
  cout << "Rectangle 2:" << rect2;

  cout << "Testing Addition" << endl;
  cout << (rect1 + rect2) << endl;

  cout << "Testing Subtraction" << endl;
  cout << (rect1 - rect2) << endl;

  cout << "Testing Prefix ++" << endl;
  cout << (++rect1) << endl;

  cout << "Testing Postfix ++" << endl;
  cout << (rect1++) << endl;

  cout << "Testing Lesser THan" << endl;
  cout << (rect1 < rect2) << endl;

  cout << "Testing Greater Than" << endl;
  cout << (rect1 > rect2) << endl;

  cout << "Rectangle 1 Area:" << endl;
  cout << (rect1.getLength() * rect1.getWidth()) << endl;

  cout << "Rectangle 2 Area:" << endl;
  cout << (rect2.getLength() * rect2.getWidth()) << endl;

  
}