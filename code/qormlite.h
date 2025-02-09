#ifndef QORMLITE_H_
#define QORMLITE_H_

#include <QString>
#include "connectors/connector.h"
#include "schema/creator.h"
#include "./database.h"

namespace QORM {

    auto isInitialized(const QString &name) -> bool;
    void initialize(const Connector&, bool verbose);
    void initialize(const Connector&,
                    std::unique_ptr<QORM::Schema::Creator>&&,
                    std::list<std::unique_ptr<Schema::Upgrader>>,
                    bool verbose);
    auto get(const QString &name) -> Database&;
    void destroy(const QString &name);
    void destroyAll();
}

#endif  // QORMLITE_H_
