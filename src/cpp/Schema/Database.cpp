//
// Created by Pradyun Devarakonda on 11/03/25.
//

#include "Database.h"

// ---------- Database Implementation ----------

Database::Database(){}
Database::Database(const std::string& xmlFilePath){
  this->xmlFilePath = xmlFilePath;
}

Database::string getName() const {
    return name;
}
Database::std::map<string,Relation*> getRelations() const {
    return relations;
}
Database::std::map<string,View*> getViews() const {
    return views;
}
Database::std::map<string,Constraint*> getConstraints() const {
    return constraints;
}
Database::std::string getXmlFilePath() const {
    return xmlFilePath;
}
Database::void setName(const std::string& name) {
    this->name = name;
}
Database::void setRelations(const std::map<string,Relation*>& relations) {
    this->relations = relations;
}
Database::void setViews(const std::map<string,View*>& views) {
    this->views = views;
}
Database::void setConstraints(const std::map<string,Constraint*>& constraints) {
    this->constraints = constraints;
}
Database::void setXmlFilePath(const std::string& xmlFilePath) {
    this->xmlFilePath = xmlFilePath;
}
Database::bool addRelation(Relation* relation) {
    if (relations.find(relation->name) != relations.end()) {
        std::cerr << "Error: Relation " << relation->name << " already exists in database.\n";
        return false;
    }
    relations[relation->name] = relation;
    return true;
}
Database::bool addView(View* view) {
    if (views.find(view->name) != views.end()) {
        std::cerr << "Error: View " << view->name << " already exists in database.\n";
        return false;
    }
    views[view->name] = view;
    return true;
}
Database::bool addConstraint(Constraint* constraint) {
    if (constraints.find(constraint->name) != constraints.end()) {
        std::cerr << "Error: Constraint " << constraint->name << " already exists in database.\n";
        return false;
    }
    constraints[constraint->name] = constraint;
    return true;
}
Database::bool removeRelation(const std::string& relationName) {
    if (relations.find(relationName) == relations.end()) {
        std::cerr << "Error: Relation " << relationName << " not found in database.\n";
        return false;
    }
    relations.erase(relationName);
    return true;
}
Database::bool removeView(const std::string& viewName) {
    if (views.find(viewName) == views.end()) {
        std::cerr << "Error: View " << viewName << " not found in database.\n";
        return false;
    }
    views.erase(viewName);
    return true;
}
Database::bool removeConstraint(const std::string& constraintName) {
    if (constraints.find(constraintName) == constraints.end()) {
        std::cerr << "Error: Constraint " << constraintName << " not found in database.\n";
        return false;
    }
    constraints.erase(constraintName);
    return true;
}
Database::Relation* getRelation(const std::string& relationName) {
    if (relations.find(relationName) == relations.end()) {
        std::cerr << "Error: Relation " << relationName << " not found in database.\n";
        return NULL;
    }
    return relations[relationName];
}
Database::View* getView(const std::string& viewName) {
    if (views.find(viewName) == views.end()) {
        std::cerr << "Error: View " << viewName << " not found in database.\n";
        return NULL;
    }
    return views[viewName];
}
Database::Constraint* getConstraint(const std::string& constraintName) {
    if (constraints.find(constraintName) == constraints.end()) {
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
    for (const Schema_Element *elem : schemaElements) {
        if (!elem->create(basePath)) {
            std::cerr << "Failed to create schema element: " << elem->name << std::endl;
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
