#include "counter.h"

namespace ext_lib {

Counter::Counter(int initial) : count(initial) {}

void Counter::increment() {
    ++count;
}

int Counter::getCount() const {
    return count;
}

} // namespace ext_lib
