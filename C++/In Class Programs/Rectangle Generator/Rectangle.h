/** Parisa Nawar - PXN210032
  * Charles Carraher - CEC210005
  */
#include <cstring>
#include <iostream>

double length;
double width;

Rectangle();

Rectangle(double len, double wid);

Rectangle(const Rectangle& rec);

Rectangle operator+(const Rectangle& rec);

Rectangle Rectangle::operator-(const Rectangle& rec);

Rectangle Rectangle::operator++();

Rectangle Rectangle::operator++(int);

bool Rectangle::operator>(const Rectangle& rec);

bool Rectangle::operator<(const Rectangle& rec);
 
std::ostream& operator<<(std::ostream& out, const Rectangle& rec);
