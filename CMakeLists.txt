cmake_minimum_required(VERSION 3.22)

option(USE_UIKIT "Use the pigui UI kit library" ON)
configure_file(src/config.hpp.in src/config.hpp)

set(CMAKE_CXX_STANDARD_LIBRARIES -lSDL2)

if (USE_UIKIT)
    add_subdirectory(src/uikit)
    list(APPEND EXTRA_LIBS uikit)
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/uikit")
endif()

project (pigui)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)
add_subdirectory(src/components)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" "${EXTRA_INCLUDES}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})