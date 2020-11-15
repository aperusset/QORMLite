#include "qormutils.h"
#include <QRandomGenerator>
#include <QRegExp>

const QString DATE_FORMAT_SQL = "yyyy-MM-dd";
const QString SEPARATOR = "_";
const QString PARAMETRIZED_PREFIX = ":";
const QString CHARACTERS_FILTER_REGEXP = "[.() ]";

auto QORMUtils::formatSQLiteDate(const QDate &date) -> QString {
    return date.toString(DATE_FORMAT_SQL);
}

auto QORMUtils::backupFileName(const QString& databaseName) -> QString {
    return "backup" + SEPARATOR + databaseName + SEPARATOR + formatSQLiteDate(QDate::currentDate()) + ".db";
}

auto QORMUtils::parametrize(const QString &field) -> QString {
    return PARAMETRIZED_PREFIX + field.toLower().remove(QRegExp(CHARACTERS_FILTER_REGEXP));
}
