
file(GLOB PARSER_SOURCES "src/*.cpp")

add_executable(parser ${PARSER_SOURCES})

target_include_directories(parser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)