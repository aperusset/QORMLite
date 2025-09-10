#ifndef QORMLITE_H_
#define QORMLITE_H_

#include <QString>
#include <list>
#include <memory>
#include "connectors/connector.h"
#include "schema/creator.h"
#include "./database.h"

namespace QORM {

    auto isInitialized(const QString &name) -> bool;
    void initialize(std::unique_ptr<Connector>, bool verbose);
    void initialize(std::unique_ptr<Connector>,
                    std::unique_ptr<Schema::Creator>,
                    std::list<std::unique_ptr<Schema::Upgrader>> = {},
                    bool verbose = false);
    auto get(const QString &name) -> std::shared_ptr<Database>;
    void destroy(const QString &name);
    void destroyAll();
}  // namespace QORM

#endif  // QORMLITE_H_
