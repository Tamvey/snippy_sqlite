#include <cassert>
#include <stdlib.h>

#include "SQLiteDB.hpp"
#include "SnippyDB.h"

int main() {

  RVDBConfig Config{"./example.db3"};
  auto *State = rvdb_initDatabase(&Config);

  auto Ops = rvdb_getOperandsByRows(State, 1, Rand, RVDB_XOR);

  assert(Ops.Num == 2);
  std::vector<uint64_t> Vals(Ops.Data, Ops.Data + Ops.Num);

  for (auto Op : Vals)
    std::cout << "Op : " << Op << "\n";

  rvdb_closeDatabase(State);

  return 0;
}
