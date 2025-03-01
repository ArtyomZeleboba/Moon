g++ -IInclude src/main.cpp src/vm.cpp src/arith/arith.cpp src/jump/jump.cpp src/memory/memory.cpp src/stack/stack.cpp src/opc_bool/cmp.cpp src/opc_bool/bool.cpp -o build/vm
./build/vm
