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

auto QORM::Utils::null() -> QVariant {
    return QVariant();
}

auto QORM::Utils::qualifyFieldName(const QString &qualifier,
                                   const QString &fieldName) -> QString {
    return qualifier + "." + fieldName;
}

auto QORM::Utils::getBoolOrDefault(const QSqlRecord &record,
                                   const QString &fieldName,
                                   bool defaultValue) -> bool {
    return getOrDefault<bool>(record, fieldName, defaultValue,
                              &QVariant::toBool);
}

auto QORM::Utils::getStringOrDefault(const QSqlRecord &record,
                                     const QString &fieldName,
                                     const QString &defaultValue) -> QString {
    return getOrDefault<QString>(record, fieldName, defaultValue,
                                 &QVariant::toString);
}

auto QORM::Utils::getDateTimeOrDefault(const QSqlRecord &record,
                                       const QString &fieldName,
                                       const QDateTime &defaultValue)
    -> QDateTime {
    return getOrDefault<QDateTime>(record, fieldName, defaultValue,
                                   &QVariant::toDateTime);
}

auto QORM::Utils::getUIntOrDefault(const QSqlRecord &record,
                                   const QString &fieldName,
                                   uint32_t defaultValue) -> uint32_t {
    return getOrDefault<uint32_t>(record, fieldName, defaultValue,
                                  [](const QVariant &variant) -> uint32_t {
                                    return variant.toUInt();
                                  });
}

auto QORM::Utils::getIntOrDefault(const QSqlRecord &record,
                                  const QString &fieldName,
                                  int32_t defaultValue) -> int32_t {
    return getOrDefault<int32_t>(record, fieldName, defaultValue,
                                 [](const QVariant &variant) -> int32_t {
                                   return variant.toInt();
                                 });
}

auto QORM::Utils::getDoubleOrDefault(const QSqlRecord &record,
                                     const QString &fieldName,
                                     double defaultValue) -> double {
    return getOrDefault<double>(record, fieldName, defaultValue,
                                [](const QVariant &variant) -> double {
                                  return variant.toDouble();
                                });
}

auto const validString = [](const QString &value) {
    return !value.isEmpty();
};

auto QORM::Utils::notBlankOrNull(const QString &value) -> QVariant {
    return validOrNull<QString>(value.trimmed(), validString);
}

auto QORM::Utils::notBlankOrThrow(const QString &value) -> QVariant {
    return validOrThrow<QString>(value.trimmed(),
                                 "A not blank string is expected", validString);
}

auto QORM::Utils::validOrNull(const QDateTime &value) -> QVariant {
    return validOrNull<QDateTime>(value, &QDateTime::isValid);
}

auto QORM::Utils::validOrThrow(const QDateTime &value) -> QVariant {
    return validOrThrow<QDateTime>(value, "A valid date time is expected",
                                   &QDateTime::isValid);
}
