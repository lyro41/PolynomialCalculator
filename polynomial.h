#pragma once

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
#include <QString>

struct term;


class Polynomial {
 private:
  term *head;
  term *tail;
  QString variable;

 public:
  Polynomial();
  double PointValue(double point);
  void FindIntRoots();
  QString QStringForm();

  Polynomial operator +(Polynomial);
  Polynomial operator *(Polynomial);
  Polynomial operator /(Polynomial);
};


Polynomial *Checker(QString expression);

Polynomial *Differentiate(Polynomial &polynomial);

#endif // POLYNOMIAL_H
