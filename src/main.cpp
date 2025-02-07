#include <stdlib.h>

#include "SQLiteDB.hpp"

int main() {


    llvm::snippy::database::SQLiteDB db("./example.db3");
    db.open();
    llvm::snippy::database::SQLiteDB::Operands* ops = new llvm::snippy::database::SQLiteDB::Operands();
    ops->Num = 1;
    ops->Size = 8;
    int rows = 3;
    uint64_t* ptr = (uint64_t*) malloc(ops->Size * rows * ops->Num);

    ops->Data = ptr;
    db.getRows(rows, ops, llvm::snippy::database::SQLiteDB::Order::Rand, 1);
    for (int i = 0; i < ops->Num * rows; i++) {
        std::cout << ops->Data[i] << ' ';
        if ((i + 1) % ops->Num == 0) std::cout << std::endl;
    }
    
    return 0;
}
