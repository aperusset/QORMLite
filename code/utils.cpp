#include "utils.h"
#include <QRandomGenerator>
#include <QRegExp>
#include "operations/query/selection/dateformatter.h"

namespace {

auto formatSQLDate(const QString &format, const QString &fieldName,
                   const QString &renameTo) -> QORM::Selection {
    return QORM::DateFormatter(format, fieldName, renameTo);
}

}  // namespace

auto QORM::Utils::formatSQLiteDate(const QDate &date) -> QString {
    return date.toString("yyyy-MM-dd");
}

auto QORM::Utils::backupFileName(const QString& databaseName) -> QString {
    return "backup_" + databaseName + "_" +
            formatSQLiteDate(QDate::currentDate()) + ".db";
}

auto QORM::Utils::parametrize(const QString &field) -> QString {
    return ":" + field.toLower().remove(QRegExp("[.() ]"));
}

auto QORM::Utils::dateToDay(const QString &fieldName,
                          const QString &renameTo) -> Selection {
    return formatSQLDate("%d", fieldName, renameTo);
}

auto QORM::Utils::dateToMonth(const QString &fieldName,
                            const QString &renameTo) -> Selection {
    return formatSQLDate("%m", fieldName, renameTo);
}

auto QORM::Utils::dateToYear(const QString &fieldName,
                           const QString &renameTo) -> Selection {
    return formatSQLDate("%Y", fieldName, renameTo);
}

auto QORM::Utils::null(QVariant::Type type) -> QVariant {
    return QVariant(type);
}
