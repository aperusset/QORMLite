#include "coalesce.h"
#include <utility>
#include "utils.h"

QORM::Coalesce::Coalesce(const std::list<QString> &fields, QVariant defaultValue,
                         const QString &renamedTo) :
    Selection(QString{"coalesce(" + QORM::Utils::joinToString<QString>(fields, ",", [](const QString &value) -> QString { return value; }) + ")"}, renamedTo) {
}
