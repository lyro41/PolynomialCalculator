#include "polynomial.h"


struct term {
  long long exponent;
  long long coefficient = 1;
  term *next = nullptr;
};


Polynomial::Polynomial() : head(nullptr), tail(nullptr) {}


double Polynomial::PointValue(double point) {
  double result = 0.0;
  term *now = this->head;

  if (now == nullptr) return 0.0;

  while (now->next != nullptr) {
    result += now->coefficient;
    result *= std::pow(point, now->exponent - now->next->exponent);
    now = now->next;
  }
  result += now->coefficient;
  result *= std::pow(point, now->exponent);

  return result;
}


QString Polynomial::QStringForm() {
  term *now = head;
  QString polynomial = "";
  while (now != nullptr) {
    if (now != head) polynomial += "+";
    polynomial += QString::number(now->coefficient);
    polynomial += variable;
    polynomial += QString("^") + QString::number(now->exponent);
  }

  return polynomial;
}
