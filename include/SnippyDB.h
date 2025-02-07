#pragma once

#include <cstdint>

#include <vector>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define RVDBAPI_ENTRY_POINT_SYMBOL RVDBVTable
#define RVDBAPI_VERSION_SYMBOL RVDBInterfaceVersion
#define RVDBAPI_CURRENT_INTERFACE_VERSION 1u

enum Order {Rand, SeqFromStart};
  
struct RVDBConfig;
typedef struct RVDBConfig RVDBConfig;

enum RVDBOpcodes {
  RVDB_ADD,
  RVDB_XOR,
  RVDB_MUL
};

struct RVDBConfig {
  const char* dataBasePath;
};

typedef struct RVDBState RVDBState;

typedef RVDBState* (*rvdb_initDatabase_t)(const RVDBConfig *);

typedef void (*rvdb_getOperandsByRows_t)(
  RVDBState *, uint64_t, enum Order, RVDBOpcodes
);

typedef void (*rvdb_closeDatabase_t)(RVDBState *);


#ifdef __cplusplus
}
#endif // __cplusplus

