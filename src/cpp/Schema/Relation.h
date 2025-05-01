//
// Created by Pradyun Devarakonda on 11/03/25.
//

#ifndef RELATION_H
#define RELATION_H
#include "../include/fsnamespace.h"
#include "../include/external_includes.h"
#include "Schema_Element.h"
#include "CAttribute.h"
#include "PrimaryKey.h"
#include "Constraint.h"
#include "ForeignKeyConstraint.h"
#include "UniqueKeyConstraint.h"
#include "PrimaryKeyConstraint.h"
//#include "Database.h"
class Database; // forward declaration
class ForeignKeyConstraint;
class UniqueKeyConstraint;
class PrimaryKeyConstraint;

//Database* database; //forward declaration
//using namespace std;
// Relation: a table in the database.
class Relation : public Schema_Element {
  public:
  std::map<std::string,CAttribute*> cattributes;
  PrimaryKey primaryKey;
  std::string name; // Added 'name' member
   Database* database;
  std::map<std::string,PrimaryKeyConstraint*> pks;
  std::map<std::string,UniqueKeyConstraint*> uks;
  std::map<std::string,ForeignKeyConstraint*> fks;

  std::map<std::string,CAttribute*> getCAttributes() const;
  PrimaryKey getPrimaryKey() const;
  Relation(const std::string& name, Database* database) : name(name), database(database) {}
    Relation(const std::string& name, Database* database, const std::map<std::string,CAttribute*>& attributes)
        :      cattributes(attributes), name(name), database(database) {}
    Relation(const std::string& name, Database* database, const std::map<std::string,CAttribute*>& attributes,
             const PrimaryKey& primaryKey)
        :  cattributes(attributes), primaryKey(primaryKey), name(name), database(database)
 {}
    Relation(const std::string& name, Database* database, const std::map<std::string,CAttribute*>& attributes,
                 const PrimaryKey& primaryKey, const std::map<std::string,ForeignKeyConstraint*>& fks,
                 const std::map<std::string,UniqueKeyConstraint*>& uks,
                 const std::map<std::string,PrimaryKeyConstraint*>& pks)
        : cattributes(attributes), primaryKey(primaryKey), name(name), database(database), pks(pks), uks(uks), fks(fks) {}
   Relation(){}
  bool setCAttributes(const std::map<std::string, CAttribute*>& attributes);
  bool setPrimaryKey(const PrimaryKey& primaryKey);
  bool addCAttribute(const CAttribute* attribute);
  bool removeCAttribute(const std::string& attributeName);
  CAttribute* getCAttribute(const std::string& attributeName);
    bool addPrimaryKeyConstraint(PrimaryKeyConstraint* pkconstraint);
    bool addForeignKeyConstraint(ForeignKeyConstraint* fkconstraint);
    bool addUniqueKeyConstraint(UniqueKeyConstraint* ukconstraint);
  std::map<std::string,ForeignKeyConstraint*> getfks();
  std::map<std::string,UniqueKeyConstraint*> getuks();
  std::map<std::string,PrimaryKeyConstraint*> getpks();
  std::string getName() const; // Ensure getName() is declared
  std::string getDBName() const;
  void setName(const std::string& name); // Added setter for name
    Database * getDatabase() const {
        return database;
    }
  // The create() method creates a directory for the relation and a .dat file for each attribute.
  virtual bool create(const fs::path &basePath) const override;
  ~Relation();
//  string getDBName() const {
//      return database->getName();
//  }
    std::string getRelationName() const {
        return name;
    }

    int getNumRows();

};

#endif //RELATION_H
