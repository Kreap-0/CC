#include <string>

class SymbolObserver {
public:
    virtual void onVariableDeclared(const class VariableInfo& var) = 0;
    virtual void onFunctionDeclared(class FunctionInfo& func) = 0;
    virtual void updateFunctionRange(const std::string& funcName, int startPos, int endPos) = 0;
    virtual ~SymbolObserver() = default;
};

class SymbolTableManager : public SymbolObserver {
    std::vector<VariableInfo> varTable;
    std::vector<FunctionInfo> proTable;
    std::map<std::string, FunctionInfo*> functionMap;
    
public:
    void onVariableDeclared(const VariableInfo& var) override {
        varTable.push_back(var);
    }
    
    void onFunctionDeclared(FunctionInfo& func) override {
        proTable.push_back(func);
        functionMap[func.name] = &proTable.back();
    }
    
    void updateFunctionRange(const std::string& funcName, int startPos, int endPos) override {
        auto it = functionMap.find(funcName);
        if (it != functionMap.end()) {
            it->second->varStart = startPos;
            it->second->varEnd = endPos;
        }
    }
    
    void generateFiles(const std::string& baseName) {
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
};