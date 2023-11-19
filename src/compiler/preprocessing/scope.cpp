#include "scope.h"

namespace comp {
    bool Scope::operator==(const Scope& another) const {
        return (beginChar == another.beginChar) && (endChar == another.endChar);
    }
}
