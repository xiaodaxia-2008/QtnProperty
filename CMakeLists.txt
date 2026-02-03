cmake_minimum_required(VERSION 3.16)

project(QtnProperty VERSION 2.0.3 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets LinguistTools Test)

add_subdirectory(QtnProperty)
find_package(BISON QUIET)
find_package(FLEX QUIET)
if (BISON_FOUND AND FLEX_FOUND)
    add_subdirectory(PEG)
else()
    message(WARNING "Bison/Flex not found, QtnPEG will not be built.")
endif()

function(qtn_add_pef target pef_file)
    get_filename_component(pef_abs ${pef_file} ABSOLUTE)
    get_filename_component(pef_name ${pef_file} NAME_WE)
    get_filename_component(pef_dir ${pef_file} DIRECTORY)

    if (TARGET QtnPEG)
        set(out_cpp "${CMAKE_CURRENT_BINARY_DIR}/${pef_name}.peg.cpp")
        set(out_h "${CMAKE_CURRENT_BINARY_DIR}/${pef_name}.peg.h")

        add_custom_command(
            OUTPUT "${out_cpp}" "${out_h}"
            COMMAND QtnPEG "${pef_abs}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS QtnPEG "${pef_abs}"
            COMMENT "Generating PEG files for ${pef_file}"
            VERBATIM
        )

        target_sources(${target} PRIVATE "${out_cpp}" "${out_h}")
        # Ensure AUTOMOC finds the generated header
        set_property(SOURCE "${out_h}" PROPERTY SKIP_AUTOMOC OFF)
    else()
        if (pef_dir)
            set(src_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${pef_dir}/${pef_name}.peg.cpp")
            set(src_h "${CMAKE_CURRENT_SOURCE_DIR}/${pef_dir}/${pef_name}.peg.h")
        else()
            set(src_cpp "${CMAKE_CURRENT_SOURCE_DIR}/${pef_name}.peg.cpp")
            set(src_h "${CMAKE_CURRENT_SOURCE_DIR}/${pef_name}.peg.h")
        endif()
        
        if (EXISTS "${src_cpp}")
            message(STATUS "Using pre-generated PEG files for ${pef_file}")
            target_sources(${target} PRIVATE "${src_cpp}" "${src_h}")
            set_property(SOURCE "${src_h}" PROPERTY SKIP_AUTOMOC OFF)
        else()
            message(WARNING "Pre-generated PEG files not found for ${pef_file}: ${src_cpp}")
        endif()
    endif()
endfunction()

add_subdirectory(Tests)
add_subdirectory(Demo)
