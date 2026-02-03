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

set(QTN_PROPERTY_SOURCES
    PropertyBase.cpp
    Property.cpp
    PropertySet.cpp
    Enum.cpp
    QObjectPropertySet.cpp
    Core/PropertyBool.cpp
    Core/PropertyInt.cpp
    Core/PropertyUInt.cpp
    Core/PropertyDouble.cpp
    Core/PropertyFloat.cpp
    Core/PropertyQString.cpp
    Core/PropertyQRect.cpp
    Core/PropertyEnum.cpp
    Core/PropertyEnumFlags.cpp
    Core/PropertyQSize.cpp
    Core/PropertyQPoint.cpp
    GUI/PropertyQColor.cpp
    GUI/PropertyQFont.cpp
    GUI/PropertyQBrush.cpp
    GUI/PropertyQPen.cpp
    GUI/PropertyButton.cpp
    PropertyWidget.cpp
    PropertyView.cpp
    Utils/InplaceEditing.cpp
    Delegates/PropertyDelegate.cpp
    Delegates/PropertyDelegateAux.cpp
    Delegates/PropertyDelegateFactory.cpp
    Delegates/Core/PropertyDelegateBool.cpp
    Delegates/Core/PropertyDelegateInt.cpp
    Delegates/Core/PropertyDelegateUInt.cpp
    Delegates/Core/PropertyDelegateQString.cpp
    Delegates/Core/PropertyDelegateDouble.cpp
    Delegates/Core/PropertyDelegateFloat.cpp
    Delegates/Core/PropertyDelegateEnum.cpp
    Delegates/Core/PropertyDelegateQRect.cpp
    Delegates/Core/PropertyDelegateQRectF.cpp
    Delegates/Core/PropertyDelegateEnumFlags.cpp
    Delegates/Core/PropertyDelegateQSize.cpp
    Delegates/Core/PropertyDelegateQSizeF.cpp
    Delegates/Core/PropertyDelegateQPoint.cpp
    Delegates/Core/PropertyDelegateQPointF.cpp
    Delegates/GUI/PropertyDelegateQColor.cpp
    Delegates/GUI/PropertyDelegateQBrush.cpp
    Delegates/GUI/PropertyDelegateQPen.cpp
    Delegates/GUI/PropertyDelegateQFont.cpp
    Delegates/GUI/PropertyDelegateButton.cpp
    Delegates/Utils/PropertyEditorHandler.cpp
    Delegates/Utils/PropertyEditorAux.cpp
    Delegates/Utils/PropertyDelegateMisc.cpp
    Delegates/Utils/PropertyDelegatePropertySet.cpp
    Delegates/Utils/PropertyDelegateSliderBox.cpp
    Delegates/Utils/PropertyDelegateGeoCoord.cpp
    Delegates/Utils/PropertyDelegateGeoPoint.cpp
    Utils/AccessibilityProxy.cpp
    Utils/DoubleSpinBox.cpp
    Utils/MultilineTextDialog.cpp
    PropertyInt64.cpp
    PropertyUInt64.cpp
    Core/PropertyQRectF.cpp
    Core/PropertyQPointF.cpp
    Core/PropertyQSizeF.cpp
    PropertyWidgetEx.cpp
    CustomPropertyEditorDialog.cpp
    CustomPropertyOptionsDialog.cpp
    VarProperty.cpp
    PropertyQVariant.cpp
    CustomPropertyWidget.cpp
    QObjectPropertyWidget.cpp
    MultiProperty.cpp
    PropertyConnector.cpp
    Utils/QtnConnections.cpp
    Utils/QtnInt64SpinBox.cpp
    Auxiliary/PropertyDelegateInfo.cpp
    PropertyQKeySequence.cpp
    PropertyDelegateMetaEnum.cpp
    Install.cpp
    Utils/QtnCompleterLineEdit.cpp
    Utils/QtnCompleterItemDelegate.cpp
    GUI/PropertyQVector3D.cpp
    Delegates/GUI/PropertyDelegateQVector3D.cpp
)

set(QTN_PROPERTY_HEADERS
    PropertyBase.h
    Property.h
    PropertySet.h
    Enum.h
    QObjectPropertySet.h
    PropertyCore.h
    PropertyGUI.h
    Auxiliary/PropertyTemplates.h
    Auxiliary/PropertyMacro.h
    Auxiliary/PropertyAux.h
    Auxiliary/PropertyDelegateInfo.h
    Core/PropertyBool.h
    Core/PropertyInt.h
    Core/PropertyUInt.h
    Core/PropertyDouble.h
    Core/PropertyFloat.h
    Core/PropertyQString.h
    Core/PropertyQRect.h
    Core/PropertyEnum.h
    Core/PropertyEnumFlags.h
    Core/PropertyQSize.h
    Core/PropertyQPoint.h
    GUI/PropertyQColor.h
    GUI/PropertyQFont.h
    GUI/PropertyQBrush.h
    GUI/PropertyQPen.h
    GUI/PropertyButton.h
    PropertyWidget.h
    PropertyView.h
    Utils/InplaceEditing.h
    Delegates/PropertyDelegate.h
    Delegates/PropertyDelegateAux.h
    Delegates/PropertyDelegateFactory.h
    Delegates/Core/PropertyDelegateBool.h
    Delegates/Core/PropertyDelegateInt.h
    Delegates/Core/PropertyDelegateUInt.h
    Delegates/Core/PropertyDelegateQString.h
    Delegates/Core/PropertyDelegateDouble.h
    Delegates/Core/PropertyDelegateFloat.h
    Delegates/Core/PropertyDelegateEnum.h
    Delegates/Core/PropertyDelegateQRect.h
    Delegates/Core/PropertyDelegateQRectF.h
    Delegates/Core/PropertyDelegateEnumFlags.h
    Delegates/Core/PropertyDelegateQSize.h
    Delegates/Core/PropertyDelegateQSizeF.h
    Delegates/Core/PropertyDelegateQPoint.h
    Delegates/Core/PropertyDelegateQPointF.h
    Delegates/GUI/PropertyDelegateQColor.h
    Delegates/GUI/PropertyDelegateQFont.h
    Delegates/GUI/PropertyDelegateQBrush.h
    Delegates/GUI/PropertyDelegateQPen.h
    Delegates/GUI/PropertyDelegateButton.h
    Delegates/Utils/PropertyEditorHandler.h
    Delegates/Utils/PropertyEditorAux.h
    Delegates/Utils/PropertyDelegateMisc.h
    Delegates/Utils/PropertyDelegatePropertySet.h
    Delegates/Utils/PropertyDelegateSliderBox.h
    Delegates/Utils/PropertyDelegateGeoCoord.h
    Delegates/Utils/PropertyDelegateGeoPoint.h
    Utils/AccessibilityProxy.h
    Utils/DoubleSpinBox.h
    Utils/MultilineTextDialog.h
    PropertyInt64.h
    PropertyUInt64.h
    Core/PropertyQRectF.h
    Core/PropertyQPointF.h
    Core/PropertyQSizeF.h
    PropertyWidgetEx.h
    CustomPropertyEditorDialog.h
    CustomPropertyOptionsDialog.h
    VarProperty.h
    PropertyQVariant.h
    CustomPropertyWidget.h
    QObjectPropertyWidget.h
    IQtnPropertyStateProvider.h
    MultiProperty.h
    StructPropertyBase.h
    PropertyConnector.h
    Utils/QtnConnections.h
    Utils/QtnInt64SpinBox.h
    PropertyDelegateAttrs.h
    PropertyQKeySequence.h
    PropertyDelegateMetaEnum.h
    Install.h
    Config.h
    FunctionalHelpers.h
    Utils/QtnCompleterLineEdit.h
    Utils/QtnCompleterItemDelegate.h
    GUI/PropertyQVector3D.h
    Delegates/GUI/PropertyDelegateQVector3D.h
)

set(QTN_PROPERTY_FORMS
    CustomPropertyEditorDialog.ui
    CustomPropertyOptionsDialog.ui
    Utils/MultilineTextDialog.ui
)

target_sources(QtnProperty PRIVATE
    ${QTN_PROPERTY_SOURCES}
    ${QTN_PROPERTY_HEADERS}
    ${QTN_PROPERTY_FORMS}
    QtnProperty.qrc
)

# Compile translations
set(QM_FILES)
foreach(lang en ru)
    set(ts_file "${CMAKE_CURRENT_SOURCE_DIR}/Translations/${lang}.ts")
    set(qm_file "${CMAKE_CURRENT_SOURCE_DIR}/Translations/${lang}.qm")
    # set(qm_file "${CMAKE_CURRENT_BINARY_DIR}/Translations/${lang}.qm")
    
    # file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Translations")
    
    add_custom_command(
        OUTPUT "${qm_file}"
        COMMAND Qt6::lrelease "${ts_file}" -qm "${qm_file}"
        DEPENDS "${ts_file}"
        VERBATIM
    )
    list(APPEND QM_FILES "${qm_file}")
endforeach()

# Target for translations
add_custom_target(QtnProperty_translations DEPENDS ${QM_FILES})
add_dependencies(QtnProperty QtnProperty_translations)

if(MSVC)
    target_compile_definitions(QtnProperty PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
