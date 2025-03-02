cmake_minimum_required(VERSION 3.10)
project(MoonVM)

# Указываем стандарт C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем include-директорию
include_directories(Include)

# Список исходных файлов
set(SOURCES
    src/main.cpp
    src/vm.cpp
    src/arith/arith.cpp
    src/jump/jump.cpp
    src/memory/memory.cpp
    src/stack/stack.cpp
    src/opc_bool/cmp.cpp
    src/opc_bool/bool.cpp
)

# Создаем исполняемый файл
add_executable(vm ${SOURCES})

# Указываем директорию для сборки
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
