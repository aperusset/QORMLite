#ifndef UTILS_H_
#define UTILS_H_

#include <QDate>
#include <QDateTime>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <utility>
#include "entities/baseentity.h"
#include "operations/query/selection/selection.h"

namespace QORM::Utils {

    struct identity {
        template <typename T>
        constexpr T&& operator()(T&& t) const noexcept {
            return std::forward<T>(t);
        }
    };

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
     * a parametrized query. Convert to lower case and remove any characters
     * like .()'%,-[]!?$\
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
     * @brief Generate a null QVariant SQL value
     * @return the null value
     */
    auto null() -> QVariant;

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
     * @brief Define if a container contains or not an element.
     * @return true : contains, false : does not contain
     */
    template<typename Container, typename T>
    auto contains(const Container &list, const T &element) {
        return std::find(list.begin(), list.end(), element) != list.end();
    }

    /**
     * @brief Define if a list initializer contains or not an element.
     * @return true : contains, false : does not contain
     */
    template<typename T>
    auto contains(std::initializer_list<T> list, const T &element) {
        return std::find(list.begin(), list.end(), element) != list.end();
    }

    /**
     * @brief Join a container of elements into a QString with a separator
     * @param elements the elements to join
     * @param separator the separator to use
     * @param transformer the function that transform to QString
     * @return the elements joined into a single QString with the separator
     */
    template<typename Container, typename Transformer = identity>
    auto joinToString(const Container &elements, const QString &separator,
                      Transformer &&transformer = {}) {
        QStringList transformed;
        transformed.reserve(elements.size());
        std::transform(elements.begin(), elements.end(),
                       std::back_inserter(transformed),
                       std::forward<Transformer>(transformer));
        return transformed.join(separator);
    }

    /**
     * @brief Join an initializer of elements into a QString with a separator
     * @param elements the elements to join
     * @param separator the separator to use
     * @param transformer the function that transform to QString
     * @return the elements joined into a single QString with the separator
     */
    template<typename T, typename Transformer = identity>
    auto joinToString(std::initializer_list<T> elements,
                      const QString &separator,
                      Transformer &&transformer = {}) {
        return joinToString<std::initializer_list<T>>(elements, separator,
            std::forward<Transformer>(transformer));
    }

    /**
     * @brief Extract keys from a list of entities
     * @param entities the entities to extract the keys
     * @return an unordered set containing the keys of the entities
     */
    template<class Entity, typename Key = int>
    [[nodiscard]] auto extractKeys(const QORM::RefList<Entity> &entities) {
        static_assert(
            std::is_base_of_v<Entities::BaseEntity<Key>, Entity>,
            "Entity must extend QORM::Entities::BaseEntity<Key>");
        std::unordered_set<Key> keys;
        keys.reserve(entities.size());
        std::transform(entities.begin(), entities.end(),
            std::inserter(keys, keys.end()), [](const auto &e) {
                return e.get().getKey();
            });
        return keys;
    }

    /**
     * @brief Extract a T value from a QSqlRecord or, if null, throw an
     * std::invalid_argument with a given error message
     * @param record the record from which to extract the value
     * @param fieldName the name of the field to extract from the record
     * @param errorMessage the error message if value is null
     * @param extractor the function that transform from QVariant to T
     * @return extracted T value
     * @throw std::invalid_argument if the value is invalid
     */
    template<typename T, typename Extractor>
    auto getOrThrow(const QSqlRecord &record, const QString &fieldName,
                    const std::string &errorMessage, Extractor &&extractor) {
        if (record.isNull(fieldName)) {
            throw std::invalid_argument(errorMessage.c_str());
        }
        if constexpr (std::is_member_function_pointer_v<Extractor>) {
            return (record.value(fieldName).*extractor)();
        } else {
            return extractor(record.value(fieldName));
        }
    }

    /**
     * @brief Extract a T value from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default T value
     * @param extractor the function that transform from QVariant to T
     * @return extracted T value
     */
    template<typename T, typename Extractor>
    auto getOrDefault(const QSqlRecord &record, const QString &fieldName,
                      const T &defaultValue, Extractor &&extractor) {
        if (record.isNull(fieldName)) {
            return defaultValue;
        }
        if constexpr (std::is_member_function_pointer_v<Extractor>) {
            return (record.value(fieldName).*extractor)();
        } else {
            return extractor(record.value(fieldName));
        }
    }

    /**
     * @brief Extract a pointer to T value from a QSqlRecord or nullptr
     * @param record the record from which to extract the pointer
     * @param fieldName the name of the field to extract from the record
     * @param extractor the function that transform from QVariant to T*
     * @return extracted pointer to T or nulltpr
     */
    template<typename T, typename Extractor>
    auto getOrNull(const QSqlRecord &record, const QString &fieldName,
                   Extractor &&extractor) {
        return getOrDefault<T*>(record, fieldName, nullptr, extractor);
    }

    /**
     * @brief Extract a bool from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the bool value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default bool value
     * @return extracted bool value
     */
    auto getBoolOrDefault(const QSqlRecord &record, const QString &fieldName,
                          bool defaultValue) -> bool;

    /**
     * @brief Extract a bool from a QSqlRecord or, if null or a invalid, throw
     * an exception
     * @param record the record from which to extract the bool value
     * @param fieldName the name of the field to extract from the record
     * @return extracted bool value
     */
    auto getBoolOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> bool;

    /**
     * @brief Extract a QString from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the QString value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default QString value
     * @return extracted QString value
     */
    auto getStringOrDefault(const QSqlRecord &record, const QString &fieldName,
                            const QString &defaultValue) -> QString;

    /**
     * @brief Extract a QString from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the QString value
     * @param fieldName the name of the field to extract from the record
     * @return extracted QString value
     */
    auto getStringOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> QString;

    /**
     * @brief Extract a QDate from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the QDate value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default QDate value
     * @return extracted QDate value
     */
    auto getDateOrDefault(const QSqlRecord &record, const QString &fieldName,
                          const QDate &defaultValue) -> QDate;

    /**
     * @brief Extract a QDate from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the QDate value
     * @param fieldName the name of the field to extract from the record
     * @return extracted QDate value
     */
    auto getDateOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> QDate;

    /**
     * @brief Extract a QDateTime from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the QDateTime value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default QDateTime value
     * @return extracted QDateTime value
     */
    auto getDateTimeOrDefault(const QSqlRecord &record,
                              const QString &fieldName,
                              const QDateTime &defaultValue) -> QDateTime;

    /**
     * @brief Extract a QDateTime from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the QDateTime value
     * @param fieldName the name of the field to extract from the record
     * @return extracted QDateTime value
     */
    auto getDateTimeOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> QDateTime;

    /**
     * @brief Extract a uint32_t from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the uint32_t value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default uint32_t value
     * @return extracted uint32_t value
     */
    auto getUIntOrDefault(const QSqlRecord &record, const QString &fieldName,
                          uint32_t defaultValue) -> uint32_t;

    /**
     * @brief Extract a uint32_t from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the uint32_t value
     * @param fieldName the name of the field to extract from the record
     * @return extracted uint32_t value
     */
    auto getUIntOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> uint32_t;

    /**
     * @brief Extract a int32_t from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the int32_t value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default int32_t value
     * @return extracted int32_t value
     */
    auto getIntOrDefault(const QSqlRecord &record, const QString &fieldName,
                         int32_t defaultValue) -> int32_t;

    /**
     * @brief Extract a int32_t from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the int32_t value
     * @param fieldName the name of the field to extract from the record
     * @return extracted int32_t value
     */
    auto getIntOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> int32_t;

    /**
     * @brief Extract a double from a QSqlRecord or, if null, a default value
     * @param record the record from which to extract the double value
     * @param fieldName the name of the field to extract from the record
     * @param defaultValue the default double value
     * @return extracted double value
     */
    auto getDoubleOrDefault(const QSqlRecord &record, const QString &fieldName,
                            double defaultValue) -> double;

    /**
     * @brief Extract a double from a QSqlRecord or, if null or a invalid,
     * throw an exception
     * @param record the record from which to extract the double value
     * @param fieldName the name of the field to extract from the record
     * @return extracted double value
     */
    auto getDoubleOrThrow(const QSqlRecord &record, const QString &fieldName)
        -> double;

    /**
     * @brief Return a value wrapped in a QVariant if valid, based on a given
     * predicate, or return a null QVariant.
     * @param value the value to validate and wrap
     * @param predicate a function to determine if the value is valid or not
     * @return the wrapped value (or null QVariant)
     */
    template <typename T>
    auto validOrNull(const T &value,
            const std::function<bool(const T&)> &predicate) -> QVariant {
        return predicate(value) ? QVariant::fromValue(value) : null();
    }

    /**
     * @brief Return a value wrapped in a QVariant if valid, based on a given
     * predicate, or throw the given error message wrapped int an exception.
     * @param value the value to validate and wrap
     * @param predicate a function to determine if the value is valid or not
     * @return the wrapped value
     * @throw std::invalid_argument if the value is not valid
     */
    template <typename T>
    auto validOrThrow(const T &value, const std::string &errorMessage,
            const std::function<bool(const T&)> &predicate) {
        if (predicate(value)) {
            return QVariant::fromValue(value);
        }
        throw std::invalid_argument(errorMessage.c_str());
    }

    /**
     * @brief Return a trimmed QString wrapped in a QVariant or a null QVariant
     * if the QString is blank.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     */
    auto notBlankOrNull(const QString &value) -> QVariant;

    /**
     * @brief Return a trimmed QString wrapped in a QVariant or throw an
     * exception if the QString is blank.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     * @throw std::invalid_argument if the QString is blank
     */
    auto notBlankOrThrow(const QString &value) -> QVariant;

    /**
     * @brief Return a QDate wrapped in a QVariant or a null QVariant if the
     * QDate is not valid.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     */
    auto validOrNull(const QDate &value) -> QVariant;

    /**
     * @brief Return a QDate wrapped in a QVariant or throw an exception if
     * the QDate is invalid.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     * @throw std::invalid_argument if the QDate is invalid
     */
    auto validOrThrow(const QDate &value) -> QVariant;

    /**
     * @brief Return a QDateTime wrapped in a QVariant or a null QVariant if the
     * QDateTime is not valid.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     */
    auto validOrNull(const QDateTime &value) -> QVariant;

    /**
     * @brief Return a QDateTime wrapped in a QVariant or throw an exception if
     * the QDateTime is invalid.
     * @param value the value to validate and wrap
     * @return the wrapped value (or null QVariant)
     * @throw std::invalid_argument if the QDateTime is invalid
     */
    auto validOrThrow(const QDateTime &value) -> QVariant;

}  // namespace QORM::Utils

#endif  // UTILS_H_
