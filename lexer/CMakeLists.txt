file(GLOB_RECURSE LEXER_SOURCES "src/*.cpp")

add_executable(lexer ${LEXER_SOURCES})

target_include_directories(lexer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/common
)