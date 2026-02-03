add_library(QtnProperty SHARED)

target_include_directories(QtnProperty
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(QtnProperty
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_compile_definitions(QtnProperty
    PRIVATE
        QTN_DYNAMIC_LIBRARY
    INTERFACE
        QTN_DYNAMIC_IMPORT
)

file(GLOB_RECURSE QTN_PROPERTY_SOURCES "*.cpp")
file(GLOB_RECURSE QTN_PROPERTY_HEADERS "*.h")
file(GLOB_RECURSE QTN_PROPERTY_FORMS "*.ui")

target_sources(QtnProperty PRIVATE
    ${QTN_PROPERTY_SOURCES}
    ${QTN_PROPERTY_HEADERS}
    ${QTN_PROPERTY_FORMS}
)

qt_standard_project_setup(I18N_TRANSLATED_LANGUAGES en zh)
qt_add_translations(QtnProperty)


install(TARGETS QtnProperty EXPORT QtnPropertyConfig)
install(EXPORT QtnPropertyConfig DESTINATION cmake)