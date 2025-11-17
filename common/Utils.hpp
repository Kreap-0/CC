#pragma once

#include <string>
#include <fstream>
#include <iostream>

static std::string read_file_to_string(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return "";
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string content(size, '\0');
    file.read(content.data(), size);

    if (file.gcount() != size) {
        std::cerr << "Warning: Could not read the entire file." << std::endl;
    }

    file.close();
    return content;
}