#pragma once

#ifndef DATABASE_H
#define DATABASE_H


#include <QString>
#include <QFile>
#include <QTextStream>
#include "polynomial.h"


struct field;


class DataBase {
 private:
  long long size;
  field *head;
  field *tail;

 public:
  DataBase();
  void Insert(Polynomial *expression);
  void Delete(long long id);
  void Load(QString path);
  void Save(QString path);
};


#endif // DATABASE_H
