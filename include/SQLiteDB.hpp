#pragma once
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"
#include "SnippyDB.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

namespace rvdb {

class SnippyDataBase {
public:
  std::vector<uint64_t> Operands;

  virtual ~SnippyDataBase() = default;
  virtual bool open() = 0;
  virtual void close() = 0;
  virtual void getRows(uint64_t rows, Order order, RVDBOpcodes opType) = 0;
};

class SQLiteDataBase : public SnippyDataBase {
  std::string path;
  std::unique_ptr<SQLite::Database> db;
  // FIXME: Add to DB
  std::unordered_map<RVDBOpcodes, unsigned> map;

public:
  SQLiteDataBase(std::string path) : path(std::move(path)), db(nullptr) {
    map.emplace(RVDB_ADD, 2);
    map.emplace(RVDB_XOR, 2);
    map.emplace(RVDB_MUL, 2);
  }
  ~SQLiteDataBase() { this->close(); }

  bool open() {
    try {
      db = std::make_unique<SQLite::Database>(path, SQLite::OPEN_READONLY);
      return true;
    } catch (const std::exception &e) {
      std::cerr << "Failed to open database: " << e.what() << std::endl;
      return false;
    }
  }

  void close() { db.reset(); }

  void getRows(uint64_t rows, Order order, RVDBOpcodes opType) {
    if (!db) {
      std::cerr << "Database is not open." << std::endl;
      return;
    }

    try {
      std::string queryStr;
      auto Num = map[opType];
      if (order == Order::Rand) {
        queryStr = "SELECT * FROM data_" + std::to_string(Num) +
                   " WHERE op_type=? ORDER BY RANDOM() LIMIT ?;";
      } else {
        queryStr = "SELECT * FROM data_" + std::to_string(Num) +
                   " WHERE op_type=? LIMIT ?;";
      }

      SQLite::Statement query(*db, queryStr);
      query.bind(1, static_cast<int64_t>(opType));
      query.bind(2, static_cast<int64_t>(rows));

      while (query.executeStep()) {
        for (auto i = 0; i < Num; i++) {
          uint64_t value = query.getColumn(i + 2).getInt64();
          Operands.push_back(value);
        }
      }
    } catch (const std::exception &e) {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
  }
};
} // namespace rvdb

struct RVDBState;

RVDBState *rvdb_initDatabase(const RVDBConfig *Config);

void rvdb_getOperandsByRows(RVDBState *State, uint64_t rows, Order order,
                            RVDBOpcodes opType);
void rvdb_closeDatabase(RVDBState *State);

#ifdef __cplusplus
}
#endif // __cplusplus
