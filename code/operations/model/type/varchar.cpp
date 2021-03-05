#include "operations/model/type/varchar.h"

const QString Varchar::EMPTY = "''";

Varchar::Varchar(const int size) :
    Type("varchar(" + QString::number(size) + ")") {}
