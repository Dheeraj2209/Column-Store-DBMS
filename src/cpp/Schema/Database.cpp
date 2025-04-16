////
//// Created by Pradyun Devarakonda on 11/03/25.
////
//
#include "Database.h"
//
//// ---------- Database Implementation ----------
//
Database::Database(){}
Database::Database(const std::string& xmlFilePath){
  this->xmlFilePath = xmlFilePath;
}

string Database::getName() const {
    return name;
}
map<string,Relation*> Database::getRelations() const {
    return relations;
}
map<string,View*> Database::getViews() const {
    return views;
}
map<string,Constraint*> Database::getConstraints() const {
    return constraints;
}
string Database::getXmlFilePath() const {
    return xmlFilePath;
}
void Database::setName(const std::string& name) {
    this->name = name;
}
void Database::setRelations(const std::map<string,Relation*>& relations) {
    this->relations = relations;
}
void Database::setViews(const std::map<string,View*>& views) {
    this->views = views;
}
void Database::setConstraints(const std::map<string,Constraint*>& constraints) {
    this->constraints = constraints;
}
void Database::setXmlFilePath(const std::string& xmlFilePath) {
    this->xmlFilePath = xmlFilePath;
}
bool Database::addRelation(Relation* relation) {
    if (relations.find(relation->name) != relations.end()) {
        std::cerr << "Error: Relation " << relation->name << " already exists in database.\n";
        return false;
    }
    relations[relation->name] = relation;
    return true;
}
bool Database::addView(View* view) {
    if (views.find(view->name) != views.end()) {
        std::cerr << "Error: View " << view->name << " already exists in database.\n";
        return false;
    }
    views[view->name] = view;
    return true;
}
bool Database::addConstraint(Constraint* constraint) {
    if (constraints.find(constraint->name) != constraints.end()) {
        std::cerr << "Error: Constraint " << constraint->name << " already exists in database.\n";
        return false;
    }
    constraints[constraint->name] = constraint;
    return true;
}
bool Database::removeRelation(const std::string& relationName) {
    if (relations.find(relationName) == relations.end()) {
        std::cerr << "Error: Relation " << relationName << " not found in database.\n";
        return false;
    }
    relations.erase(relationName);
    return true;
}
bool Database::removeView(const std::string& viewName) {
    if (views.find(viewName) == views.end()) {
        std::cerr << "Error: View " << viewName << " not found in database.\n";
        return false;
    }
    views.erase(viewName);
    return true;
}
bool Database::removeConstraint(const std::string& constraintName) {
    if (constraints.find(constraintName) == constraints.end()) {
        std::cerr << "Error: Constraint " << constraintName << " not found in database.\n";
        return false;
    }
    constraints.erase(constraintName);
    return true;
}
Relation* Database::getRelation(const std::string& relationName) {
    if (relations.find(relationName) == relations.end()) {
        std::cerr << "Error: Relation " << relationName << " not found in database.\n";
        return NULL;
    }
    return relations[relationName];
}
View* Database::getView(const std::string& viewName) {
    if (views.find(viewName) == views.end()) {
        std::cerr << "Error: View " << viewName << " not found in database.\n";
        return NULL;
    }
    return views[viewName];
}
Constraint* Database::getConstraint(const std::string& constraintName) {
    if (this->constraints.find(constraintName) == constraints.end()) {
        std::cerr << "Error: Constraint " << constraintName << " not found in database.\n";
        return NULL;
    }
    return constraints[constraintName];
}
bool Database::create() const {
    // Create the main database directory under ../../Databases/DatabaseName.
    fs::path basePath = fs::path("../../Databases") / name;
    try {
        fs::create_directories(basePath);
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error creating database directory (" << name << "): " << e.what() << std::endl;
        return false;
    }

    // For each schema element, call its create() method.
    for (const auto &elem : relations) {
        if (!elem.second->create(basePath)) {
            std::cerr << "Failed to create schema element: " << elem.second->name << std::endl;
            return false;
        }
    }
    for (const auto &elem : views) {
        if (!elem.second->create(basePath)) {
            std::cerr << "Failed to create schema element: " << elem.second->name << std::endl;
            return false;
        }
    }
    for (const auto &elem : constraints) {
        if (!elem.second->create(basePath)) {
            std::cerr << "Failed to create schema element: " << elem.second->name << std::endl;
            return false;
        }
    }
    return true;
}
Database::~Database() {
    // Clean up allocated Schema_Element pointers. Strictly enforce the Composition relationship.
//    for (Schema_Element *elem : schemaElements) {
//        delete elem;
//    }
    for (auto& pair : relations) {
        delete pair.second;
    }
    for (auto& pair : views) {
        delete pair.second;
    }
    for (auto& pair : constraints) {
        delete pair.second;
    }

}
