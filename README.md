# Column-Store DBMS: Project Overview

This document provides a comprehensive overview of the Column-Store DBMS project, its architecture, core classes, methods, data flow, and usage instructions. Paste this directly as **README.md** in your repository.

---

## 1. Project Context

* **Goal**: Build a lightweight, file-based column-store database management system (DBMS) in C++ from scratch.
* **Schema Definition**:

  * XML instance documents conforming to the provided XSD describe databases, relations, attributes, primary keys, foreign keys, and unique constraints.
  * Parsed by **DDLEngine** (using TinyXML2).
* **Storage Layout**:

  * Under `Databases/<DBName>/<RelationName>/`, each column attribute has its own `.dat` file.
  * Records stored as binary:

    ```
    [isDeleted:uint8_t][payload bytes] [isDeleted][payload] … 
    ```
* **Data Manipulation**:

  * Bulk CSV imports via **DataLoader** (Tbl.hpp parser).
  * In-memory PK/UK/FK constraint enforcement before appending.
  * Single-row insert, update (soft delete + append), delete/undelete (flag flip), print, and query.
* **Query Processing**:

  * Simple single-table `SELECT` support via **QueryManager** + **DataStitcher**.

---

## 2. Project Structure

```
Project_Root/
├─ Databases/                   # runtime storage
├─ src/
│  ├─ Engines/
│  │   DDLEngine.{h,cpp}        # DDL: XML → directory & .dat creation
│  │   DMLEngine.{h,cpp}        # Facade for load/insert/update/delete/print/query
│  │   DataLoader.{h,cpp}       # CSV → .dat files, PK/UK/FK checks
│  │   DataManipulator.{h,cpp}  # update logic
│  │   DataDeleter.{h,cpp}      # delete/undelete logic
│  │   DataStitcher.{h,cpp}     # reconstruct rows from columns
│  │   QueryManager.{h,cpp}     # execute SELECT queries
│  │   ViewManager.{h,cpp}      # manage named views
│  ├─ Schema/
│  │   Database.{h,cpp}
│  │   Relation.{h,cpp}
│  │   CAttribute.{h,cpp}
│  │   Constraint.{h,cpp}
│  │   PrimaryKeyConstraint.{h,cpp}
│  │   UniqueKeyConstraint.{h,cpp}
│  │   ForeignKeyConstraint.{h,cpp}
│  │   PrimaryKey.{h,cpp}
│  │   View.{h,cpp}
│  │   Schema_Element.{h,cpp}
│  ├─ ComputationObjects/
│  │   Query.{h,cpp}
│  ├─ CustomTypes/
│  │   Date_DDMMYYYY_Type.{h,cpp}
│  ├─ Data_Objects/
│  │   ColVal.{h,cpp}
│  │   ColPage.{h,cpp}
│  │   ColContainer.{h,cpp}
│  │   Row.{h,cpp}
│  │   Table.{h,cpp}
│  ├─ include/
│  │   external_includes.h
│  ├─ main.cpp                  # createDBOOPS
│  ├─ dml_main.cpp              # load
│  ├─ insert_main.cpp           # insertRow
│  ├─ update_main.cpp           # updateRow
│  ├─ delete_main.cpp           # deleteRow
│  ├─ undelete_main.cpp         # undeleteRow
│  ├─ query_main.cpp            # queryRow
│  ├─ print_main.cpp            # printTable
│  └─ showTables_main.cpp       # showTables
└─ Makefile                     # build targets
```

---

## 3. Core Components

### 3.1 Schema & Constraints

* **CAttribute**: `name`, `type` (integer/string/decimal/date/boolean), `isNullable`, `isUnique`, `isPK`.
* **PrimaryKeyConstraint**, **UniqueKeyConstraint**, **ForeignKeyConstraint**: metadata and on-disk persistence.
* **Relation**: holds maps of `CAttribute*` and constraints; methods to enumerate attributes and constraints.
* **Database**: manages relations, views, and constraints; provides lookup by name.

### 3.2 DDL Engine (`DDLEngine`)

* **`loadSchemaFromXML(xmlPath)`**

  * Parses XML, creates `Databases/<DB>/…` directories, empty binary `.dat` for each column, and writes schema XML.

### 3.3 Data Loading (`DataLoader`)

* **`loadDataFromCSV(db, relationName, csvPath)`**:

  1. Read CSV into string, parse via **Tbl.hpp**.
  2. Verify column-count vs. schema.
  3. Build in-memory sets for PK/UK; load parent keys for FK via `getReferencedKeySet`.
  4. For each row:

     * Extract each cell’s raw string.
     * Enforce PK/UK uniqueness, FK membership.
     * Buffer `(isDeleted=0, payload)` for each column.
  5. Append to each column’s `.dat`.

* **`getReferencedKeySet(db, fkConstraint)`**

  * Reads parent column file, skipping deleted bytes, deserializes payloads, returns `unordered_set<string>`.

### 3.4 DML Operations

* **DMLEngine**:

  * **`insertRow(rel, vector<string> vals, db)`**: wraps values into `Row`/`ColVal`, calls `DataLoader::insertRow()`.
  * **`updateRow(rel, pkValue, vector<string> newVals, db)`**: calls `DataManipulator::updateRow()`.
  * **`row_delete(dbName, relName, pkValue)`**: sets `isDeleted=1` on matching row.
  * **`undeleteRow(...)`**: flips `isDeleted` back to 0.
  * **`printTable(dbName, relName)`**: reads all column files, skips deleted entries, reconstructs and prints rows.

* **`DataManipulator::updateRow(rel, Row*)`**: marks old row deleted + appends new values.

* **`DataDeleter::deleteRow(rel, pkValue)`**: finds matching row index, sets its flag to 1.

### 3.5 Query Processing

* **Query**: holds parsed SQL-like query parts (`SELECT`, `FROM`, `WHERE`, `ORDER BY`).
* **QueryManager**:

  * `addQuery(q)`,
  * `executeQuery(q)` reads column files, applies filters, projects columns, returns new `Relation*`.

### 3.6 Data Structures

* **ColVal**: holds one cell value and its attribute; supports `operator==` & `std::hash` for sets.
* **Row**: list of `ColVal*`; represents a tuple.
* **Table**: list of `Row*`; in-memory result table.
* **DataStitcher**: reconstructs a tuple from separate column files for display or query output.

---

## 4. Build & Run

### Prerequisites

* C++17 compiler (`g++`, `clang++`)
* **tinyxml2**
* **Tbl.hpp** header in `Engines/` or `include/`

### Building

```bash
cd src/cpp
make mac    # on macOS (homebrew paths)
# or
make wsl    # on Linux/WSL
```

**Targets**:

* `createDBOOPS`
* `load`
* `insertRow`
* `deleteRow`
* `undeleteRow`
* `updateRow`
* `printTable`
* `queryRow`
* `showTables`

### Examples

```bash
# 1) Create schema
./createDBOOPS

# 2) Bulk load
./load ECommerceDB_main Customer ../../example_CSVs/customers.csv

# 3) Insert a row
./insertRow ECommerceDB_main Customer 5 charlie@funnyfilms.com "Charlie Chaplin"

# 4) Delete a row
./deleteRow ECommerceDB_main Customer 5

# 5) Undelete a row
./undeleteRow ECommerceDB_main Customer 5

# 6) Update a row
./updateRow ECommerceDB_main Customer 2 "2","jane.new@", "Jane New"

# 7) Print a table
./printTable ECommerceDB_main Customer

# 8) Simple query
./queryRow ECommerceDB_main "SELECT CustomerID,Name FROM Customer WHERE CustomerID>2;"

# 9) List all relations
./showTables ECommerceDB_main
```

---

## 5. Future Directions

* Disk-based **B-tree** or **Hash** indexes for faster lookups
* Multi-relation **joins**, **aggregations**, and **GROUP BY**
* **Transactions** and **Write-Ahead Logging** (WAL)
* Column **compression**, **vectorized** execution, and caching strategies

---

This README should give any developer or AI engine a clear understanding of the codebase, its components, and how to build and use the Column-Store DBMS.
