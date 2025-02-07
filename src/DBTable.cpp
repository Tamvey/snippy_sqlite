#include "DBTable.h"
#include "SQLiteDB.hpp"

unsigned char RVDBAPI_VERSION_SYMBOL = RVDBAPI_CURRENT_INTERFACE_VERSION;

extern const rvdb::RVDB_FunctionPointers RVDBAPI_ENTRY_POINT_SYMBOL = {
    .initDatabase = &rvdb_initDatabase,
    .getOperandsByRows = &rvdb_getOperandsByRows,
    .closeDatabase = &rvdb_closeDatabase
};
