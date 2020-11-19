#ifndef QUERY_H
#define QUERY_H

#include "operation.h"
#include <QString>
#include <QVariant>
#include <map>

class Bindable;
class QSqlQuery;

class Query : public Operation {

    std::map<QString, QVariant> bindables;

protected:
    void addBindable(const Bindable&);

public:
    void bind(QSqlQuery &query) const;
};

#endif // QUERY_H
