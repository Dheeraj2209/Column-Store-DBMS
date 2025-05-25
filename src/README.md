# Column-Store DBMS: Project Overview 

This document provides a comprehensive overview of the Column-Store DBMS project, its architecture, core classes, methods, and data flow. It is designed to help an AI engine (or any new developer) understand and interact with the system.

---

## 1. Project Context

- **Goal**: Build a lightweight, file-based column-store database management system (DBMS) in C++.
- **Data Definition**: Schema described via XML (conforming to a provided XSD), parsed by `DDLEngine`.
- **Storage Layout**: Under `../../Databases/<DBName>/<RelationName>/`, each column attribute is stored as a `.dat` file in binary format.
- **Data Manipulation**: CSV imports (`DataLoader`), enforcing PK/UK/FK constraints in-memory, writing to column files.
- **Query Processing**: Simple single-table SELECT support via `QueryManager` + `DataStitcher`.
- **Utilities**: `DataManipulator` (update stub), `DataDeleter` (delete stub).

---

## 2. Project Structure

```text
Project_Root/
├── src/
│   ├── Engines/
│   │   ├── DDLEngine.{h,cpp}
│   │   ├── DMLEngine.{h,cpp}
│   │   ├── DataLoader.{h,cpp}
│   │   ├── DataStitcher.{h,cpp}
│   │   ├── DataManipulator.{h,cpp}
│   │   ├── DataDeleter.{h,cpp}
│   │   ├── QueryManager.{h,cpp}
│   │   └── ViewManager.{h,cpp}
│   ├── ComputationObjects/
│   │   └── Query.{h,cpp}
│   ├── CustomTypes/
│   │   └── Date_DDMMYYYY_Type.{h,cpp}
│   ├── Schema/
│   │   ├── Database.{h,cpp}
│   │   ├── Relation.{h,cpp}
│   │   ├── CAttribute.{h,cpp}
│   │   ├── PrimaryKeyConstraint.{h,cpp}
│   │   ├── UniqueKeyConstraint.{h,cpp}
│   │   ├── ForeignKeyConstraint.{h,cpp}
│   │   ├── Schema_Element.{h,cpp}
│   │   ├── PrimaryKey.{h,cpp}
│   │   ├── View.{h,cpp}
│   │   └── ViewManager.{h,cpp}
│   ├── Data_Objects/
│   │   ├── ColVal.{h,cpp}
│   │   ├── ColPage.{h,cpp}
│   │   ├── ColContainer.{h,cpp}
│   │   ├── Row.{h,cpp}
│   │   └── Table.{h,cpp}
│   ├── include/
│   │   └── external_includes.h
│   ├── createDB.{h,cpp}
│   └── main.cpp
└── Databases/
```

---

## 3. Core Classes & Methods

### 3.1 Schema Layer

- **`CAttribute`**: Represents a column; members: `name`, `type`, `isNullable`, `isUnique`, `isPK`.
- **`PrimaryKeyConstraint`, `UniqueKeyConstraint`, `ForeignKeyConstraint`**: Store metadata for constraints.
- **`PrimaryKey`**: Links a relation to its PK attribute(s).
- **`Relation`**: Holds maps of `CAttribute*`, `pks`, `uks`, `fks`; methods: `getCAttributes()`, `getName()`, `getNumRows()`, `createEmptyClone()`, `appendValue()`.
- **`Database`**: Manages relations, views, and constraints; methods: `getRelation()`, `create()`, `getForeignKeyConstraintsForRelation()`.

### 3.2 DDL Engine (`DDLEngine`)

- **`loadSchemaFromXML(string xmlPath)`**: Parses XML via TinyXML2, builds directory structure, creates empty `.dat` files for each column.

### 3.3 DML Engine & Loader (`DataLoader`)

- **`loadDataFromCSV(Database*, string csvPath, string relationName)`**:
    1. Parses CSV string with **Tbl**.
    2. Builds in-memory sets for `pks` and `uks`, loads parent keys for `fks` via `getReferencedKeySet()`.
    3. Row-by-row: enforce PK/UK/FK, serialize values, append to column files.
- **`getReferencedKeySet(Database*, ForeignKeyConstraint*)`**: Reads parent column file, deserializes values, returns `unordered_set<string>`.

### 3.4 Query Processing

- **`Query`**: Parses SQL-like `SELECT` statements; holds vectors: `resultcols`, `participating_relations`, `conditions`, `orderbycols`.
- **`QueryManager`**:
    - `addQuery(Query)` stores queries.
    - `executeQuery(Query)`: Supports single-relation SELECT with simple `WHERE` and projection.
    - `executeQueries()` loops over stored queries.

### 3.5 Tuple Stitching & Utilities

- **`DataStitcher`**: `stitchData(Relation&, int rowIndex)` reads each column’s file and concatenates values into a string.
- **`DataManipulator`**: `updateTuple(Relation*, int rowIndex, vector<string>)` stub for updates.
- **`DataDeleter`**: `deleteTuple(Relation*, int rowIndex)` stub for deletions.

### 3.6 Views and View Management

- **`View`**: Extends `Schema_Element`; holds `string name` and `Query* query`; `create(path)` writes definition to file.
- **`ViewManager`**: Manages a map of `Query*` representing named views; methods to add, retrieve, and materialize views.

### 3.7 Data Objects: ColVal, ColPage, ColContainer, Row, Table

- **`ColVal`**: Encapsulates a single column value (`string`, `int`, `double`, `Date_DDMMYYYY_Type`, or NULL) tied to a `CAttribute*`.
- **`ColPage`**: Represents a page of up to `PAGE_MAX_OBJS` `ColVal*` for a single column; methods: `addData(string)`, `removeData(string)`.
- **`ColContainer`**: Holds multiple `ColPage*` for a single column attribute; manages paging of column data.
- **`Row`**: Collection of `ColVal*` for all columns in a relation; methods to add/get/set/remove `ColVal`.
- **`Table`**: Collection of `Row*` for a relation; methods: `addRow(Row*)`, `getRow(int)`, `getRows()`, `removeRow(int)`, `toString()`, `printTable()`.

---

## 4. Data Flow & Usage

1. **Schema creation**: `createDB schema.xml MyDB` → `DDLEngine` builds `Databases/MyDB/...` structure.
2. **Data loading**: `dml_main MyDB CSVfile Relation` → `DataLoader` enforces PK/UK/FK, writes to `.dat` files.
3. **Query execution**: `QueryManager qm(db); qm.addQuery(q); auto res = qm.executeQuery(q);` → new `Relation*` with result set.

---

## 5. Future Directions

- **Disk-based Indexes**: Implement hash/B-tree indexes for constraints & faster queries.
- **Join Support**: Extend `executeQuery` for multi-table joins.
- **Transactions & Logging**: WAL, atomicity, crash recovery.
- **Optimizations**: Compression, vectorized execution, paging strategies.

---

This overview provides the **complete class context**, methods, and data flow for your Column‑Store DBMS, enabling an AI engine (or new developer) to navigate the codebase, understand responsibilities, and extend functionality. Let me know if you need deeper dives into any component!

---

