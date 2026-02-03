add_executable(QtnPropertyDemo
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    mydialog.cpp
    mydialog.h
    mydialog.ui
    AB/PropertyABColor.cpp
    AB/PropertyABColor.h
    AB/PropertyDelegateABColor.cpp
    AB/PropertyDelegateABColor.h
    Int/PropertyDelegateIntList.cpp
    Int/PropertyDelegateIntList.h
    Layer/PropertyLayer.cpp
    Layer/PropertyLayer.h
    Layer/PropertyDelegateLayer.cpp
    Layer/PropertyDelegateLayer.h
    PenWidth/PropertyPenWidth.cpp
    PenWidth/PropertyPenWidth.h
    PenWidth/PropertyDelegatePenWidth.cpp
    PenWidth/PropertyDelegatePenWidth.h
    Freq/PropertyFreq.cpp
    Freq/PropertyFreq.h
    Freq/PropertyDelegateFreq.cpp
    Freq/PropertyDelegateFreq.h
)

target_link_libraries(QtnPropertyDemo
    PRIVATE
        QtnProperty
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_include_directories(QtnPropertyDemo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qtn_add_pef(QtnPropertyDemo Demo.pef)

if(MSVC)
    target_compile_definitions(QtnPropertyDemo PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
