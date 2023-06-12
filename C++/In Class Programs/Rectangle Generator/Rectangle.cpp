/** Parisa Nawar - PXN210032
  */
#include "Rectangle.h"
#include <cstring>
#include <iostream>

double length;
double width;

Rectangle::Rectangle() {
  length = 0;
  width = 0;
};

Rectangle::Rectangle(double len, double wid) {
  length = len;
  width = wid;
}

Rectangle::Rectangle(const Rectangle& rec) {
  this->length = rec.length;
  this->width = rec.width;
}

Rectangle Rectangle::operator+(const Rectangle& rec) {
  Rectangle recTotal;

  recTotal.length = length + rec.length;
  recTotal.width = width + rec.width;

  return recTotal;
}

Rectangle Rectangle::operator-(const Rectangle& rec) {
  Rectangle recTotal;

  recTotal.length = length - rec.length;
  recTotal.width = width - rec.width;

  if (recTotal.length < 0) {
    recTotal.length = 0;
  }

  if (recTotal.width < 0) {
    recTotal.width = 0;
  }
  return recTotal;
}

Rectangle Rectangle::operator++() {
  length++;
  width++;
  return *this;
}

Rectangle Rectangle::operator++(int) {
  Rectangle temp = *this;
  this->length++;
  this->width++;
  return temp;
}

bool Rectangle::operator>(const Rectangle& rec) {
  return (width * length) > (rec.width * rec.length);
}

bool Rectangle::operator<(const Rectangle& rec) {
  return ((width * length) < (rec.width * rec.length));
}
 
std::ostream& operator<<(std::ostream& out, const Rectangle& rec) {
  double len;
  double wid;

  out << "Length: " << rec.getLength() << ", Width: " << rec.getWidth();
  
  return out;
}
