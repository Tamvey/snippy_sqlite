#pragma once

#include "SnippyDB.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct RVDBState;

RVDBState *rvdb_initDatabase(const RVDBConfig *Config);

struct Operands rvdb_getOperandsByRows(RVDBState *State, uint64_t rows,
                                       Order order, RVDBOpcodes opType);
void rvdb_closeDatabase(RVDBState *State);

#ifdef __cplusplus
}
#endif // __cplusplus
