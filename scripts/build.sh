if [ "$(basename "$(pwd)")" = "scripts" ]; then
    # if we are in scripts folder
    cd ..
fi


# creating the build folder
if [ ! -d "build" ]; then
    mkdir -p build
fi
cd build &&

# run the script
cmake cmake -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Debug .. &&

# build the project
ninja &&

cd ..