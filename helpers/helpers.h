#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace helpers {

std::vector<std::string> splitString(const std::string& string, const std::vector<std::string>& delimiters);
int64_t stoi64(std::string string);

} // helpers