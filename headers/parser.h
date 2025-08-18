#pragma once

#include <string>
#include <unordered_map>
#include <vector>


std::vector<std::string> tokenizer(const std::string& line);
std::unordered_map<std::string, int> preprocess(
    const std::vector<std::string>& program);