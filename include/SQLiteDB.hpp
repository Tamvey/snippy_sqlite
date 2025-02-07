#pragma once
#include "SnippyDB.h"
#include "SQLiteCpp/Statement.h"
#include "SQLiteCpp/Database.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <memory>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus



namespace llvm {
namespace snippy {
namespace database {

    class SQLiteDB : public SnippyDB {
        std::string path;
        std::unique_ptr<SQLite::Database> db;
    public:
        SQLiteDB(std::string path) : path(std::move(path)), db(nullptr) {}
        ~SQLiteDB() { this->close(); }

        bool open() {
            try {
                db = std::make_unique<SQLite::Database>(path, SQLite::OPEN_READONLY);
                return true;
            } catch (const std::exception& e) {
                std::cerr << "Failed to open database: " << e.what() << std::endl;
                return false;
            }
        }

        void close() {
            db.reset();
        }

        void getRows(uint64_t rows, const struct Operands* ops, Order order, uint64_t opType) {
            if (!db) {
                std::cerr << "Database is not open." << std::endl;
                return;
            }

            try {
                std::string queryStr;
                if (order == Order::Rand) {
                    queryStr = "SELECT * FROM data_" + std::to_string(ops->Num) + " WHERE op_type=? ORDER BY RANDOM() LIMIT ?;";
                } else {
                    queryStr = "SELECT * FROM data_" + std::to_string(ops->Num) + " WHERE op_type=? LIMIT ?;";
                }

                SQLite::Statement query(*db, queryStr);
                query.bind(1, (int64_t)opType);
                query.bind(2, (int64_t)rows);
                
                uint64_t index = 0; 
                while (query.executeStep() && index < rows) {
                    for (auto i = 2; i < ops->Num + 2; i++) { 
                        uint64_t value = query.getColumn(i).getInt64();
                        ops->Data[index * ops->Num + (i - 2)] = value;
                    }
                    index++;
                }
            } catch (const std::exception& e) {
                std::cerr << "Exception: " << e.what() << std::endl;
            }
        }
    };
} // namespace database
} // namespace snippy
} // namespace llvm

namespace rvdb {
    struct RVDBState {
        RVDBConfig Config;
        std::unique_ptr<llvm::snippy::database::SQLiteDB> SQLiteDB;
    };
}

rvdb::RVDBState* rvdb_initDatabase(const rvdb::RVDBConfig *Config) {
    auto State = new rvdb::RVDBState();
    State->Config = *Config; 
    State->SQLiteDB = std::make_unique<llvm::snippy::database::SQLiteDB>(Config->dataBasePath);
    if (!State->SQLiteDB->open()) {
        delete State; // Clean up memory if opening fails
        return nullptr;
    }
    return State;
}

void rvdb_getOperandsByRows(
    const rvdb::RVDBState *State, 
    const struct llvm::snippy::database::SnippyDB::Operands* ops,
    uint64_t rows,
    llvm::snippy::database::SnippyDB::Order order,
    uint64_t opType
) {
    if (State && State->SQLiteDB) {
        State->SQLiteDB->getRows(rows, ops, order, opType);
        return;
    }
    std::cerr << "Invalid state or database." << std::endl;
}

void rvdb_closeDatabase(rvdb::RVDBState *State) {
    if (State) {
        State->SQLiteDB.reset(); 
        delete State;
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus
