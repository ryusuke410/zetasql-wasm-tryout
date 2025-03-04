#!/usr/bin/env bash

cd ../..

mkdir -p ./es-ext-lib/dist

emcc -lembind -o ./es-ext-lib/dist/index.js ./es-ext-lib/binding.cc ./ext_lib/add.cc ./ext_lib/counter.cc \
  -s ENVIRONMENT=web,node \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s EXPORT_ES6=1 \
  -s MODULARIZE=1 \
  -s NO_FILESYSTEM=1 \
  -s ASSERTIONS=0 \
  -flto \
  --closure 1 \
  -O3 \
  --emit-tsd index.d.ts
