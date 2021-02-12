#ifndef QORMLITE_H
#define QORMLITE_H

#include <QString>
#include "qormcreator.h"
#include "qormdatabase.h"

namespace QORMLite {

    auto isInitialized(const QString &name) -> bool;
    void initialize(const QString &name, const QORMCreator&, bool verbose = false, bool test = false);
    auto get(const QString &name) -> QORMDatabase&;
    void destroy(const QString &name);
    void destroyAll();
}

#endif // QORMLITE_H
