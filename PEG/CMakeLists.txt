find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(BISON_PropertyEnum_OUTPUT_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/PropertyEnum.parser.cpp")
set(BISON_PropertyEnum_OUTPUT_HEADER "${CMAKE_CURRENT_BINARY_DIR}/PropertyEnum.parser.hpp")
BISON_TARGET(PropertyEnumParser PropertyEnum.y ${BISON_PropertyEnum_OUTPUT_SOURCE}
    DEFINES_FILE ${BISON_PropertyEnum_OUTPUT_HEADER}
)

set(FLEX_PropertyEnum_OUTPUT_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/PropertyEnum.lexer.cpp")
FLEX_TARGET(PropertyEnumLexer PropertyEnum.l ${FLEX_PropertyEnum_OUTPUT_SOURCE})
ADD_FLEX_BISON_DEPENDENCY(PropertyEnumLexer PropertyEnumParser)

add_executable(QtnPEG
    main.cpp
    PropertyEnumGenerator.cpp
    ${BISON_PropertyEnumParser_OUTPUTS}
    ${FLEX_PropertyEnumLexer_OUTPUTS}
)

target_include_directories(QtnPEG PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(QtnPEG PRIVATE Qt6::Core)

if(MSVC)
    target_compile_definitions(QtnPEG PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(QtnPEG PRIVATE /wd4065 /wd4267 /wd4005)
endif()
