#include <stdlib.h>

#include "SQLiteDB.hpp"
#include "SnippyDB.h"

int main() {

  rvdb::SQLiteDataBase db("./example.db3");
  db.open();

  db.getRows(1, Rand, RVDB_XOR);

  auto &Ops = db.Operands;

  for (auto Op : Ops)
    std::cout << "Op : " << Op << "\n";

  return 0;
}
