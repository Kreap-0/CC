#pragma once

#include <vector>
#include <string>
#include <fstream>

class ErrorFileGenerator {
    std::vector<std::string> errors;
public:
    explicit ErrorFileGenerator(std::vector<std::string> errs) : errors(move(errs)) {}
    
    void generateFile(const std::string& baseName) {
        std::ofstream errFile(baseName + ".err");
        if (errFile) {
            for (const auto& err : errors) {
                errFile << err << "\n";
            }
        }
    }
};