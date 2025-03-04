#include <emscripten/bind.h>
#include "../ext_lib/add.h"
#include "../ext_lib/counter.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(es_ext_lib) {
    function("add", &ext_lib::add);
    class_<ext_lib::Counter>("Counter")
        .constructor<int>()
        .function("increment", &ext_lib::Counter::increment)
        .function("getCount", &ext_lib::Counter::getCount);
}
