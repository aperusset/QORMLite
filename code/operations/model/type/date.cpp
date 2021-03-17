#include "operations/model/type/date.h"

const QString QORM::Date::NOW = "date('now')";

QORM::Date::Date() : Type("date") {}
