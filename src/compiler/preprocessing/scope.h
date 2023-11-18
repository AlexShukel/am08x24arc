#pragma once

#include <unordered_map>

#include "../types.h"

using namespace std;

namespace comp {
    struct Scope {
        byte beginChar;
        byte endChar;

        bool operator==(const Scope& another) const {
            return (beginChar == another.beginChar) && (endChar == another.endChar);
        }
    };

    struct ScopeCheckResult {
        bool result;
        Scope scope;
    };
}

namespace std {
    template<>
    struct hash<comp::Scope> {
        size_t operator()(const comp::Scope &key) const {
            return std::hash<char>()(key.beginChar) ^ std::hash<char>()(key.endChar);
        }
    };
}