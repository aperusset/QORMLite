#ifndef Q_ORM_UTILS_H
#define Q_ORM_UTILSS_H

#include <QString>
#include <QDate>
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
     * @brief Transform a field name so that it will be useable as parameter in a
     * parametrized query. Convert to lower case, remove (). and space characters.
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
    auto dateToDay(const QString &fieldName, const QString &renameTo) -> Selection;

    /**
     * @brief Generate a SQL selection to extract the month from a date field
     * @param fieldName the field name
     * @param renameTo the alias name
     * @return the selection
     */
    auto dateToMonth(const QString &fieldName, const QString &renameTo) -> Selection;

    /**
     * @brief Generate a SQL selection to extract the year from a date field
     * @param fieldName the field name
     * @param renameTo the alias name
     * @return the selection
     */
    auto dateToYear(const QString &fieldName, const QString &renameTo) -> Selection;
}

#endif // Q_ORM_UTILS_H
