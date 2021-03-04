#ifndef Q_ORM_UTILS_H
#define Q_ORM_UTILS_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QDate>
#include <list>
#include <algorithm>
#include "operations/query/selection.h"

namespace QORMUtils {

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
}  // namespace QORMUtils

#endif  // Q_ORM_UTILS_H
