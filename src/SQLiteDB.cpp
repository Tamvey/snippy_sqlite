#include "SQLiteDB.hpp"


struct RVDBState {
    RVDBConfig Config;
    std::unique_ptr<rvdb::SQLiteDataBase> SQLiteDB;
};

RVDBState* rvdb_initDatabase(const RVDBConfig *Config) {
    auto State = new RVDBState();
    State->Config = *Config; 
    State->SQLiteDB = std::make_unique<rvdb::SQLiteDataBase>(Config->dataBasePath);
    if (!State->SQLiteDB->open()) {
        delete State; // Clean up memory if opening fails
        return nullptr;
    }
    return State;
}

void rvdb_getOperandsByRows(RVDBState *State, 
    uint64_t rows,
    Order order,
    RVDBOpcodes opType
) {
    if (State && State->SQLiteDB) {
        State->SQLiteDB->getRows(rows, order, opType);
        return;
    }
    std::cerr << "Invalid state or database." << std::endl;
}

void rvdb_closeDatabase(RVDBState *State) {
    if (State) {
        State->SQLiteDB.reset(); 
        delete State;
    }
}

