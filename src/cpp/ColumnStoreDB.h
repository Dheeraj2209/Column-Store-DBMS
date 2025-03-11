#ifndef COLUMNSTOREDB_H
#define COLUMNSTOREDB_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

//  Abstract Base Class Schema_Element
class Schema_Element {
public:
    std::string name;
    virtual bool create(const fs::path &basePath) const = 0;
    virtual ~Schema_Element() {}
};

// Components used by Relations
class Attribute {
public:
    std::string name;
    std::string type;
    bool isNullable;
    bool isUnique;
    
    Attribute(const std::string& name, const std::string& type, bool isNullable = true, bool isUnique = false);
};

class PrimaryKey {
public:
    std::vector<std::string> attributeRefs;
};

//  Derived Schema Elements 

// Relation: a table in the database.
class Relation : public Schema_Element {
public:
    std::vector<Attribute> attributes;
    PrimaryKey primaryKey;
    
    // The create() method creates a directory for the relation and a .dat file for each attribute.
    virtual bool create(const fs::path &basePath) const override;
};

// Constraint: represents a constraint. Here we use a single class to represent both foreign key and unique constraints.
// The 'type' member distinguishes them.
class Constraint : public Schema_Element {
public:
    std::string type;  // e.g., "ForeignKey" or "Unique"
    
    // For a foreign key constraint:
    std::string parentTable;
    std::string parentColumn;
    std::string childTable;
    std::string childColumn;
    
    // For a unique constraint:
    std::string relation; // relation name on which this unique constraint applies.
    std::vector<std::string> attributeRefs;
    
    // The create() method writes a summary entry into a constraints file.
    virtual bool create(const fs::path &basePath) const override;
};

// View : Named Query
class View : public Schema_Element {
public:
    std::string query;  // view definition (e.g. an SQL query)
    
    // The create() method writes the view definition into a file.
    virtual bool create(const fs::path &basePath) const override;
};

// Database Class
// The Database is a composition of Schema_Element objects.
class Database {
public:
    std::string name;
    std::vector<Schema_Element*> schemaElements; //Use a map instead of vector to store schema elements

    bool create() const;    

    ~Database();//Drop the database
};

#endif // COLUMNSTOREDB_H
