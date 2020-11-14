#include "qormutils.h"
#include <QRandomGenerator>
#include <limits>

const QString DATE_FORMAT_SQL = "yyyy-MM-dd";
const QString SEPARATOR = "_";

auto QORMUtils::formatSQLiteDate(const QDate &date) -> QString {
    return date.toString(DATE_FORMAT_SQL);
}

auto QORMUtils::backupFileName(const QString& databaseName) -> QString {
    return "backup" + SEPARATOR + databaseName + SEPARATOR + formatSQLiteDate(QDate::currentDate()) + ".db";
}
