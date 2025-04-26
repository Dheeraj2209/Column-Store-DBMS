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

using namespace std;
// Relation: a table in the database.
class Relation : public Schema_Element {
  std::map<string,CAttribute*> cattributes;
  PrimaryKey primaryKey;
  std::string name; // Added 'name' member
   Database* database;
public:
  std::map<string,CAttribute*> getCAttributes() const;
  PrimaryKey getPrimaryKey() const;
  bool setCAttributes(const std::map<std::string, CAttribute*>& attributes);
  bool setPrimaryKey(const PrimaryKey& primaryKey);
  bool addCAttribute(const CAttribute* attribute);
  bool removeCAttribute(const std::string& attributeName);
  CAttribute* getCAttribute(const std::string& attributeName);
  std::map<string,PrimaryKeyConstraint*> pks;
  std::map<string,UniqueKeyConstraint*> uks;
  std::map<string,ForeignKeyConstraint*> fks;
  std::map<string,ForeignKeyConstraint*> getfks();
  std::map<string,UniqueKeyConstraint*> getuks();
  std::map<string,PrimaryKeyConstraint*> getpks();
  std::string getName() const; // Ensure getName() is declared
  std::string getDBName() const;
  void setName(const std::string& name); // Added setter for name
  // The create() method creates a directory for the relation and a .dat file for each attribute.
  virtual bool create(const fs::path &basePath) const override;
  ~Relation();
};

#endif //RELATION_H
