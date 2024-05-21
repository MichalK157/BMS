#!/bin/bash

dir="$(dirname "$(readlink -f "$0")")"
repo_dir=$(readlink -f "$dir/..")

echo $repo_dir

rm -rf build
rm -rf proto

mkdir build
mkdir proto

cp $repo_dir/src/proto/protocol.h $repo_dir/API/proto/
cd build

cmake ..
make 

