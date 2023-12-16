#pragma once

#include <unordered_map>

#include "../common/types.h"

namespace comp {
    using namespace std;

    struct Scope {
        byte beginChar;
        byte endChar;

        bool operator==(const Scope& another) const;
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