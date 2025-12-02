#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

#include <Info.hpp>

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
    void onVariableDeclared(const VariableInfo& var);
    void onFunctionDeclared(FunctionInfo& func);
    void updateFunctionRange(const std::string& funcName, int startPos, int endPos);
    void generateFiles(const std::string& baseName);
};