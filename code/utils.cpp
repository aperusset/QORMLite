#include "utils.h"
#include <QRandomGenerator>
#include <QRegularExpression>
#include "operations/query/selection/dateformatter.h"

namespace {

auto formatSQLDate(const QString &format, const QString &fieldName,
                   const QString &renameTo) -> QORM::Selection {
    return QORM::DateFormatter(format, fieldName, renameTo);
}

static const auto parametrizeRegExp = QRegularExpression("[^a-z0-9]");

static const auto uIntExtractor = [](const auto &variant) -> uint32_t {
    return variant.toUInt();
};

static const auto intExtractor = [](const auto &variant) -> int32_t {
    return variant.toInt();
};

static const auto doubleExtractor = [](const auto &variant) -> double {
    return variant.toDouble();
};

static const auto validString = [](const auto &value) {
    return !value.isEmpty();
};

static const auto validDate = [](const QDate &value) {
    return value.isValid();
};

}  // namespace

auto QORM::Utils::formatSQLiteDate(const QDate &date) -> QString {
    return date.toString("yyyy-MM-dd");
}

auto QORM::Utils::backupFileName(const QString& databaseName) -> QString {
    return "backup_" + databaseName + "_" +
            formatSQLiteDate(QDate::currentDate()) + ".db";
}

auto QORM::Utils::parametrize(const QString &field) -> QString {
    return ":" + field.toLower().remove(parametrizeRegExp);
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

auto QORM::Utils::getBoolOrThrow(const QSqlRecord &record,
                                 const QString &fieldName) -> bool {
    return getOrThrow<bool>(record, fieldName, "A valid bool is expected",
                            &QVariant::toBool);
}

auto QORM::Utils::getStringOrDefault(const QSqlRecord &record,
                                     const QString &fieldName,
                                     const QString &defaultValue) -> QString {
    return getOrDefault<QString>(record, fieldName, defaultValue,
                                 &QVariant::toString);
}

auto QORM::Utils::getStringOrThrow(const QSqlRecord &record,
                                 const QString &fieldName) -> QString {
    return getOrThrow<QString>(record, fieldName, "A valid QString is expected",
                               &QVariant::toString);
}

auto QORM::Utils::getDateOrDefault(const QSqlRecord &record,
                                   const QString &fieldName,
                                   const QDate &defaultValue) -> QDate {
    return getOrDefault<QDate>(record, fieldName, defaultValue,
                               &QVariant::toDate);
}

auto QORM::Utils::getDateOrThrow(const QSqlRecord &record,
                                 const QString &fieldName) -> QDate {
    return getOrThrow<QDate>(record, fieldName, "A valid QDate is expected",
                             &QVariant::toDate);
}

auto QORM::Utils::getDateTimeOrDefault(const QSqlRecord &record,
                                       const QString &fieldName,
                                       const QDateTime &defaultValue)
    -> QDateTime {
    return getOrDefault<QDateTime>(record, fieldName, defaultValue,
                                   &QVariant::toDateTime);
}

auto QORM::Utils::getDateTimeOrThrow(const QSqlRecord &record,
                                 const QString &fieldName) -> QDateTime {
    return getOrThrow<QDateTime>(record, fieldName,
                    "A valid QDateTime is expected", &QVariant::toDateTime);
}

auto QORM::Utils::getUIntOrDefault(const QSqlRecord &record,
                                   const QString &fieldName,
                                   uint32_t defaultValue) -> uint32_t {
    return getOrDefault<uint32_t>(record, fieldName, defaultValue,
                                  uIntExtractor);
}

auto QORM::Utils::getUIntOrThrow(const QSqlRecord &record,
                                 const QString &fieldName) -> uint32_t {
    return getOrThrow<uint32_t>(record, fieldName,
                    "A valid unsigned int is expected", uIntExtractor);
}

auto QORM::Utils::getIntOrDefault(const QSqlRecord &record,
                                  const QString &fieldName,
                                  int32_t defaultValue) -> int32_t {
    return getOrDefault<int32_t>(record, fieldName, defaultValue, intExtractor);
}

auto QORM::Utils::getIntOrThrow(const QSqlRecord &record,
                                const QString &fieldName) -> int32_t {
    return getOrThrow<int32_t>(record, fieldName, "A valid int is expected",
                               intExtractor);
}

auto QORM::Utils::getDoubleOrDefault(const QSqlRecord &record,
                                     const QString &fieldName,
                                     double defaultValue) -> double {
    return getOrDefault<double>(record, fieldName, defaultValue,
                                doubleExtractor);
}

auto QORM::Utils::getDoubleOrThrow(const QSqlRecord &record,
                                   const QString &fieldName) -> double {
    return getOrThrow<double>(record, fieldName, "A valid double is expected",
                              doubleExtractor);
}

auto QORM::Utils::notBlankOrNull(const QString &value) -> QVariant {
    return validOrNull<QString>(value.trimmed(), validString);
}

auto QORM::Utils::notBlankOrThrow(const QString &value) -> QVariant {
    return validOrThrow<QString>(value.trimmed(),
                                 "A not blank string is expected", validString);
}

auto QORM::Utils::validOrNull(const QDate &value) -> QVariant {
    return validOrNull<QDate>(value, validDate);
}

auto QORM::Utils::validOrThrow(const QDate &value) -> QVariant {
    return validOrThrow<QDate>(value, "A valid date is expected", validDate);
}

auto QORM::Utils::validOrNull(const QDateTime &value) -> QVariant {
    return validOrNull<QDateTime>(value, &QDateTime::isValid);
}

auto QORM::Utils::validOrThrow(const QDateTime &value) -> QVariant {
    return validOrThrow<QDateTime>(value, "A valid date time is expected",
                                   &QDateTime::isValid);
}
