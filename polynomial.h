#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
#include <QString>

struct term;


class Polynomial {
 private:
  term *head = nullptr;
  term *tail = nullptr;
  QString variable = "x";

 public:
  Polynomial();
  double PointValue(double);
  void FindIntRoots();
  QString QStringForm();
  void PushBack(term *);
  void Clear();
  Polynomial Differentiate();

  Polynomial operator +(Polynomial);
  Polynomial operator *(Polynomial);
  Polynomial operator /(Polynomial);
  bool operator ==(Polynomial);
};


Polynomial *Checker(QString expression);

#endif // POLYNOMIAL_H
