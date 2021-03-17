#include "operations/model/type/varchar.h"

const QString QORM::Varchar::EMPTY = "''";

QORM::Varchar::Varchar(const int size) :
    Type("varchar(" + QString::number(size) + ")") {}
