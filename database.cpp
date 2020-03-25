#include "database.h"


struct field {
  long long id;
  Polynomial *polynomial;
  field *next = nullptr;
};

DataBase::DataBase() : head(nullptr), tail(nullptr), size(0) {}


void DataBase::Insert(Polynomial *expression) {
  if (size == 0) {
    head = new field;
    head->id = 0;
    head->polynomial = expression;
    tail = head;
    return;
  }

  tail->next = new field;
  tail = tail->next;
  tail->id = size;
  tail->polynomial = expression;
  ++size;
  return;
}


void DataBase::Delete(long long id) {
  field *now = head;
  long long i = 0;
  for (; i + 1 < id; ++i) {
    now = now->next;
  }
  field *trash = now->next;
  if (id == size - 1) {
    now->next = nullptr;
  } else {
    now->next = trash->next;
  }
  delete trash;
  --size;
  for (; i < size; ++i) {
    now->id = i;
    now = now->next;
  }
  return;
}


void DataBase::Load(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) throw QString("LOADING_ERROR: FILE_DOES_NOT_EXIST");
  QTextStream instream(&file);
  Polynomial *expression;
  while (!file.atEnd()) {
    try {
      expression = Checker(instream.readLine());
    } catch (QString) {
      continue;
    }
    this->Insert(expression);
  }
  return;
}


void DataBase::Save(QString path) {
  QFile file(path);
  field *now = head;
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) throw QString("SAVING_ERROR: PATH_DOES_NOT_EXIST");
  QTextStream outstream(&file);
  while (now != nullptr) {
    outstream << now->polynomial->QStringForm() << '\n';
    now = now->next;
  }
  return;
}
