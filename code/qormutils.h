#ifndef Q_ORM_UTILS_H
#define Q_ORM_UTILSS_H

#include <QString>
#include <QDate>

namespace QORMUtils {

    /**
     * @brief formatSQLiteDate
     * @param date the date to format
     * @return Return the date in 'yyyy-MM-dd' format
     */
    auto formatSQLiteDate(const QDate&) -> QString;

    /**
     * @brief backupFileName
     * @param databaseName the database name
     * @return the name of the backup file for a specific database
     */
    auto backupFileName(const QString& databaseName) -> QString;
}

#endif // Q_ORM_UTILS_H
