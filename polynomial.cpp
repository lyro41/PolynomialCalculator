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


void Polynomial::PushBack(term *member) {
  if (tail == nullptr) {
    head = member;
    head->next = nullptr;
    tail = head;
    return;
  }
  tail->next = member;
  tail = tail->next;
  tail->next = nullptr;
  return;
}


void Polynomial::Clear() {
  term *buff;
  while (head != nullptr) {
    buff = head;
    head = head->next;
    delete buff;
  }
  tail = nullptr;
  return;
}


Polynomial Polynomial::Differentiate() {
  Polynomial result;
  term *pointer = this->head;
  term *buff;
  while (pointer != nullptr) {
    if (pointer->exponent != 0) {
      buff = new term;
      buff->exponent = pointer->exponent - 1;
      buff->coefficient = pointer->coefficient * pointer->exponent;
      buff->next = nullptr;
      result.PushBack(buff);
      pointer = pointer->next;
    }
  }
  return result;
}


Polynomial Polynomial::operator +(Polynomial operand) {
  Polynomial result;
  term *left = this->head;
  term *right = operand.head;
  term *buff;
  while (left != nullptr && right != nullptr) {
    buff = new term;
    if (left->exponent > right->exponent) {
      buff->exponent = left->exponent;
      buff->coefficient = left->coefficient;
      buff->next = nullptr;
      left = left->next;
    } else if (left->exponent < right->exponent) {
      buff->exponent = right->exponent;
      buff->coefficient = right->coefficient;
      buff->next = nullptr;
      right = right->next;
    } else {
      buff->exponent = left->exponent;
      buff->coefficient = left->coefficient + right->coefficient;
      buff->next = nullptr;
      left = left->next;
      right = right->next;
    }
    result.PushBack(buff);
  }
  while (left != nullptr) {
    buff = new term;
    buff->exponent = left->exponent;
    buff->coefficient = left->coefficient;
    result.PushBack(buff);
    left = left->next;
  }
  while (right != nullptr) {
    buff = new term;
    buff->exponent = right->exponent;
    buff->coefficient = right->coefficient;
    result.PushBack(buff);
    right = right->next;
  }
  return result;
}


Polynomial Polynomial::operator *(Polynomial operand) {
  Polynomial result;
  Polynomial partition;
  term *left = this->head;
  term *right = operand.head;
  term *buff;
  while (left != nullptr) {
    while (right != nullptr) {
      buff = new term;
      buff->exponent = left->exponent + right->exponent;
      buff->coefficient = left->coefficient * right->coefficient;
      buff->next = nullptr;
      partition.PushBack(buff);
      right = right->next;
    }
    result = result + partition;
    partition.Clear();
    left = left->next;
  }
  return result;
}


bool Polynomial::operator ==(Polynomial operand) {
  term *left = this->head;
  term *right = operand.head;
  while (left != nullptr && right != nullptr) {
    if (left->exponent != right->exponent || left->coefficient != right->coefficient) return 0;
    left = left->next;
    right = right->next;
  }
  return left == nullptr && right == nullptr;
}
