#pragma once

#include <unordered_map>
#include <memory>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;
    std::string word;

    TrieNode() = default;
};