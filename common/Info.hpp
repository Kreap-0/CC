#include <string>

struct VariableInfo {
    std::string name;
    std::string owner;
    std::string category;
    std::string type;
    int level;
    int position;
};

struct FunctionInfo {
    std::string name;
    std::string type;
    int level;
    int varStart;
    int varEnd;
    
    FunctionInfo(std::string n, std::string t, int l) 
        : name(move(n)), type(move(t)), level(l), varStart(-1), varEnd(-1) {}
};