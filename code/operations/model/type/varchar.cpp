#include "operations/model/type/varchar.h"

QORM::Varchar::Varchar(const int size) :
    Type("varchar(" + QString::number(size) + ")") {}
