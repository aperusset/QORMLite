#include "qormutils.h"
#include <QRandomGenerator>
#include <QRegExp>

auto QORMUtils::formatSQLiteDate(const QDate &date) -> QString {
    return date.toString("yyyy-MM-dd");
}

auto QORMUtils::backupFileName(const QString& databaseName) -> QString {
    return "backup_" + databaseName + "_" + formatSQLiteDate(QDate::currentDate()) + ".db";
}

auto QORMUtils::parametrize(const QString &field) -> QString {
    return ":" + field.toLower().remove(QRegExp("[.() ]"));
}

auto formatSQLDate(const QString &format, const QString &fieldName, const QString &renameTo) -> Selection {
    return DateFormatter(format, fieldName, renameTo);
}

auto QORMUtils::dateToDay(const QString &fieldName, const QString &renameTo) -> Selection {
    return formatSQLDate("%d", fieldName, renameTo);
}

auto QORMUtils::dateToMonth(const QString &fieldName, const QString &renameTo) -> Selection {
    return formatSQLDate("%m", fieldName, renameTo);
}

auto QORMUtils::dateToYear(const QString &fieldName, const QString &renameTo) -> Selection {
    return formatSQLDate("%Y", fieldName, renameTo);
}

auto QORMUtils::null(QVariant::Type type) -> QVariant {
    return QVariant(type);
}
