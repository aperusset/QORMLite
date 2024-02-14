#ifndef UTILS_H_
#define UTILS_H_

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QDate>
#include <QSqlRecord>
#include <list>
#include <algorithm>
#include "operations/query/selection/selection.h"

namespace QORM {

namespace Utils {

    /**
     * @brief Format a QDate to database valid date
     * @param date the date to format
     * @return Return the date in 'yyyy-MM-dd' format
     */
    auto formatSQLiteDate(const QDate&) -> QString;

    /**
     * @brief Generate the backup file name for a database
     * @param databaseName the database name
     * @return the name of the backup file for a specific database
     */
    auto backupFileName(const QString &databaseName) -> QString;

    /**
     * @brief Transform a field name so that it will be useable as parameter in
     * aparametrized query. Convert to lower case, remove (). and space
     * characters.
     * @param field the field to parametrize
     * @return the parametrized field
     */
    auto parametrize(const QString &field) -> QString;

    /**
     * @brief Generate a SQL selection to extract the day from a date field
     * @param fieldName the field name
     * @param renameTo the alias name
     * @return the selection
     */
    auto dateToDay(const QString &fieldName,
                   const QString &renameTo) -> Selection;

    /**
     * @brief Generate a SQL selection to extract the month from a date field
     * @param fieldName the field name
     * @param renameTo the alias name
     * @return the selection
     */
    auto dateToMonth(const QString &fieldName,
                     const QString &renameTo) -> Selection;

    /**
     * @brief Generate a SQL selection to extract the year from a date field
     * @param fieldName the field name
     * @param renameTo the alias name
     * @return the selection
     */
    auto dateToYear(const QString &fieldName,
                    const QString &renameTo) -> Selection;

    /**
     * @brief Generate a null SQL value for specified type
     * @param type the type of the null value
     * @return the null value
     */
    auto null(QVariant::Type type) -> QVariant;

    /**
     * @brief Qualify a field name with a table, a view, or everything else. The
     * qualifier and the field name are concatenated with a dot ".".
     * @param qualifier the qualifier
     * @param fieldName the field name
     * @return the qualified field name
     */
    auto qualifyFieldName(const QString &qualifier,
                          const QString &fieldName) -> QString;

    /**
     * @brief Define if a STL list contains or not an element.
     * @return true : contains, false : does not contain
     */
    template<typename T>
    auto contains(const std::list<T> &list, const T &element) -> bool {
        return std::find(list.begin(), list.end(), element) != list.end();
    }

    /**
     * @brief Join a list of elements into a QString with a separator
     * @param elements the elements to join
     * @param separator the separator to use
     * @param transformer the function that transform from T to QString
     * @return the elements joined into a single QString with the separator
     */
    template<typename T>
    auto joinToString(const std::list<T> &elements, const QString &separator,
              const std::function<QString(const T&)> &transformer) -> QString {
        QStringList transformed;
        std::transform(elements.begin(), elements.end(),
                       std::back_inserter(transformed), transformer);
        return transformed.join(separator);
    }

    /**
     * @brief Extract a T value from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the value
     * @param defaultValue the default T value
     * @param extractor the function that transform from QVariant to T
     * @return extracted T value
     */
    template<typename T>
    auto getOrDefault(const QSqlRecord &record, const QString &fieldName,
                      const T &defaultValue,
                      const std::function<T(const QVariant&)> &extractor) -> T {
        if (record.isNull(fieldName)) {
            return defaultValue;
        } else {
            return extractor(record.value(fieldName));
        }
    }

    /**
     * @brief Extract a pointer to T value from a QSqlRecord or nullptr
     * @param record the record from which to extract the pointer
     * @param extractor the function that transform from QVariant to T*
     * @return extracted pointer to T or nulltpr
     */
    template<typename T>
    auto getOrNull(const QSqlRecord &record, const QString &fieldName,
                   const std::function<T*(const QVariant&)> &extractor) -> T* {
        return getOrDefault<T*>(record, fieldName, nullptr, extractor);
    }

    /**
     * @brief Extract a bool from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the bool value
     * @param defaultValue the default bool value
     * @return extracted bool value
     */
    auto getBoolOrDefault(const QSqlRecord &record, const QString &fieldName,
                          bool defaultValue) -> bool;

    /**
     * @brief Extract a QString from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the QString value
     * @param defaultValue the default QString value
     * @return extracted QString value
     */
    auto getStringOrDefault(const QSqlRecord &record, const QString &fieldName,
                            const QString &defaultValue) -> QString;

    /**
     * @brief Extract a QDateTime from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the QDateTime value
     * @param defaultValue the default QDateTime value
     * @return extracted QDateTime value
     */
    auto getDateTimeOrDefault(const QSqlRecord &record,
                              const QString &fieldName,
                              const QDateTime &defaultValue) -> QDateTime;

    /**
     * @brief Extract a uint32_t from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the uint32_t value
     * @param defaultValue the default uint32_t value
     * @return extracted uint32_t value
     */
    auto getUIntOrDefault(const QSqlRecord &record, const QString &fieldName,
                          uint32_t defaultValue) -> uint32_t;

    /**
     * @brief Extract a int32_t from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the int32_t value
     * @param defaultValue the default int32_t value
     * @return extracted int32_t value
     */
    auto getIntOrDefault(const QSqlRecord &record, const QString &fieldName,
                         int32_t defaultValue) -> int32_t;

    /**
     * @brief Extract a double from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the double value
     * @param defaultValue the default double value
     * @return extracted double value
     */
    auto getDoubleOrDefault(const QSqlRecord &record, const QString &fieldName,
                            double defaultValue) -> double;


}  // namespace Utils

}  // namespace QORM

#endif  // UTILS_H_
