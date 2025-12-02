#include <SymbolObserver.hpp>

void SymbolTableManager::onVariableDeclared(const VariableInfo& var) {
    varTable.push_back(var);
}

void SymbolTableManager::onFunctionDeclared(FunctionInfo& func) {
    proTable.push_back(func);
    functionMap[func.name] = &proTable.back();
}

void SymbolTableManager::updateFunctionRange(const std::string& funcName, int startPos, int endPos) {
    auto it = functionMap.find(funcName);
    if (it != functionMap.end()) {
        it->second->varStart = startPos;
        it->second->varEnd = endPos;
    }
}

void SymbolTableManager::generateFiles(const std::string& baseName) {
    std::ofstream varFile(baseName + ".var");
    if (varFile) {
        varFile << "vname\tvproc\tvkind\tvtype\tvlev\tvadr\n";
        for (const auto& var : varTable) {
            varFile << var.name << "\t" 
                    << var.owner << "\t"
                    << var.category << "\t"
                    << var.type << "\t"
                    << var.level << "\t"
                    << var.position << "\n";
        }
    }
    
    std::ofstream proFile(baseName + ".pro");
    if (proFile) {
        proFile << "pname\tptype\tplev\tfinterval\n";
        for (const auto& func : proTable) {
            proFile << func.name << "\t"
                    << func.type << "\t"
                    << func.level << "\t"
                    << "[" << func.varStart << "," << func.varEnd << "]\n";
        }
    }
}