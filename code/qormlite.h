#ifndef QORMLITE_H
#define QORMLITE_H

#include <QString>
#include "./creator.h"
#include "./database.h"

namespace QORM {

    auto isInitialized(const QString &name) -> bool;
    void initialize(const QString &name, const Creator&, bool verbose = false,
                    bool test = false);
    auto get(const QString &name) -> Database&;
    void destroy(const QString &name);
    void destroyAll();
}

#endif  // QORMLITE_H
