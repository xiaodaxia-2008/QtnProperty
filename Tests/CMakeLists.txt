add_executable(QtnPropertyTests
    main.cpp
    TestProperty.cpp
    TestGeneratedProperty.cpp
    TestEnum.cpp
    TestProperty.h
    TestGeneratedProperty.h
    TestEnum.h
)

target_link_libraries(QtnPropertyTests
    PRIVATE
        QtnProperty
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Test
)

target_include_directories(QtnPropertyTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qtn_add_pef(QtnPropertyTests PEG/test.pef)
qtn_add_pef(QtnPropertyTests PEG/test2.pef)
