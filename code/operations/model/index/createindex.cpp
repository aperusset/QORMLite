#include "createindex.h"
#include <utility>
#include "./utils.h"

QORM::CreateIndex::CreateIndex(const QString &tableName,
            std::list<QString> fields, bool unique) :
        TableQuery(tableName), fields(std::move(fields)), unique(unique) {
    if (this->fields.empty()) {
        throw std::invalid_argument("Index name must have at least one field");
    }
    const auto hasBlankFields = std::any_of(this->fields.begin(),
            this->fields.end(), [](const auto &v) {
        return v.trimmed().isEmpty();
    });
    if (hasBlankFields) {
        throw std::invalid_argument("All fields must not be blank");
    }
}

QORM::CreateIndex::CreateIndex(const QString &tableName,
        const std::list<Field> &fields, bool unique) :
    CreateIndex(tableName, [&] {
        std::list<QString> generatedFields;
        for (const auto& field : fields) {
            generatedFields.emplace_back(field.getName());
        }
        return generatedFields;
    }(), unique) {
}

auto QORM::CreateIndex::getName() const -> QString {
    return this->getTableName() + "__" +
           Utils::joinToString(this->fields, "-") + "_index";
}

auto QORM::CreateIndex::generate() const -> QString {
    return QString("create ") + (this->unique ? "unique " : "") +
           "index if not exists " + this->getName() + " on " +
           this->getTableName() + " (" +
           Utils::joinToString(this->fields, ", ") + ")";
}
