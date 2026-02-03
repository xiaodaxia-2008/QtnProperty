/*******************************************************************************
Copyright (c) 2015-2019 Alexandra Cherdantseva <neluhus.vagus@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include "PropertyQVariant.h"

#include "QObjectPropertySet.h"
#include "Delegates/PropertyDelegateFactory.h"
#include "Delegates/Utils/PropertyEditorAux.h"
#include "Delegates/Utils/PropertyEditorHandler.h"
#include "MultiProperty.h"
#include "Core/PropertyQString.h"

#include "CustomPropertyEditorDialog.h"

#include <QEvent>
#include <QKeyEvent>

bool qtnCompareQVariants(const QVariant &left, const QVariant &right)
{
	if (left.userType() != right.userType())
	{
		return false;
	}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	switch (left.type())
#else
	switch (left.typeId())
#endif
	{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::Hash:
#else
		case QMetaType::QVariantHash:
#endif
		{
			const auto leftMap = left.toHash();
			const auto rightMap = right.toHash();
			if (leftMap.size() != rightMap.size())
			{
				return false;
			}
			auto leftIt = leftMap.cbegin();
			for (; leftIt != leftMap.cend(); ++leftIt)
			{
				auto rightIt = rightMap.find(leftIt.key());
				if (rightIt == rightMap.end())
				{
					return false;
				}

				if (!qtnCompareQVariants(leftIt.value(), rightIt.value()))
				{
					return false;
				}
			}
			return true;
		}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::Map:
#else
		case QMetaType::QVariantMap:
#endif
		{
			const auto leftMap = left.toMap();
			const auto rightMap = right.toMap();
			if (leftMap.size() != rightMap.size())
			{
				return false;
			}
			auto leftIt = leftMap.cbegin();
			auto rightIt = rightMap.cbegin();
			for (; leftIt != leftMap.cend(); ++leftIt, ++rightIt)
			{
				if (leftIt.key() != rightIt.key())
				{
					return false;
				}

				if (!qtnCompareQVariants(leftIt.value(), rightIt.value()))
				{
					return false;
				}
			}
			return true;
		}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::List:
#else
		case QMetaType::QVariantList:
#endif
		{
			const auto leftList = left.toList();
			const auto rightList = left.toList();
			int count = leftList.size();
			if (count != rightList.size())
			{
				return false;
			}
			for (int i = 0; i < count; i++)
			{
				if (!qtnCompareQVariants(leftList.at(i), rightList.at(i)))
				{
					return false;
				}
			}
			return true;
		}

		default:
			break;
	}
	return left == right;
}

class QtnPropertyQVariantEditBttnHandler
	: public QtnPropertyEditorBttnHandler<QtnPropertyQVariantBase,
		  QtnLineEditBttn>
{
public:
	QtnPropertyQVariantEditBttnHandler(
		QtnPropertyDelegate *delegate, QtnLineEditBttn &editor);

protected:
	virtual void revertInput() override;
	virtual void onToolButtonClick() override;
	virtual void updateEditor() override;

private:
	void onEditingFinished();
	void onToolButtonClicked(bool);
	void onApplyData(const QVariant &data);

	CustomPropertyEditorDialog *dialog;
	DialogContainerPtr dialogContainer;
	bool is_object;
};

QtnPropertyQVariantBase::QtnPropertyQVariantBase(QObject *parent)
	: QtnSinglePropertyBase(parent)
{
}

bool QtnPropertyQVariantBase::fromStrImpl(
	const QString &str, QtnPropertyChangeReason reason)
{
	return setValue(str, reason);
}

bool QtnPropertyQVariantBase::toStrImpl(QString &str) const
{
	str = value().toString();
	return true;
}

bool QtnPropertyQVariantBase::fromVariantImpl(
	const QVariant &var, QtnPropertyChangeReason reason)
{
	return setValue(var, reason);
}

bool QtnPropertyQVariantBase::toVariantImpl(QVariant &var) const
{
	var = value();
	return var.isValid();
}

QtnPropertyQVariantCallback::QtnPropertyQVariantCallback(
	QObject *object, const QMetaProperty &metaProperty, QObject *parent)
	: QtnSinglePropertyCallback(parent)
{
	setCallbackValueGet([object, metaProperty]() -> QVariant {
		return metaProperty.read(object);
	});

	setCallbackValueSet([object, metaProperty](QVariant value,
							QtnPropertyChangeReason /*reason*/) {
		metaProperty.write(object, value);
	});

	setCallbackValueEqual([object, metaProperty](QVariant value) -> bool {
		auto thisValue = metaProperty.read(object);

		return qtnCompareQVariants(thisValue, value);
	});
}

QtnPropertyQVariantCallback::QtnPropertyQVariantCallback(QObject *parent)
	: QtnSinglePropertyCallback<QtnPropertyQVariantBase>(parent)
{
}

QtnPropertyQVariant::QtnPropertyQVariant(QObject *parent)
	: QtnSinglePropertyValue<QtnPropertyQVariantBase>(parent)
{
}

QString QtnPropertyQVariant::valueToString(const QVariant &value)
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	return !variantIsObject(value.type()) ? value.toString() : QString();
#else
	return !variantIsObject(static_cast<QMetaType::Type>(value.typeId()))
		? value.toString()
		: QString();
#endif
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
bool QtnPropertyQVariant::variantIsObject(QVariant::Type type)
#else
bool QtnPropertyQVariant::variantIsObject(QMetaType::Type type)
#endif
{
	switch (type)
	{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::Hash:
		case QVariant::Map:
		case QVariant::StringList:
		case QVariant::List:
#else
		case QMetaType::QVariantHash:
		case QMetaType::QVariantMap:
		case QMetaType::QStringList:
		case QMetaType::QVariantList:
#endif
			return true;

		default:
			break;
	}

	return false;
}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
QString QtnPropertyQVariant::getPlaceholderStr(QVariant::Type type)
#else
QString QtnPropertyQVariant::getPlaceholderStr(QMetaType::Type type)
#endif
{
	switch (type)
	{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::Hash:
		case QVariant::Map:
#else
		case QMetaType::QVariantHash:
		case QMetaType::QVariantMap:
#endif
			return tr("(Dictionary)");

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		case QVariant::StringList:
		case QVariant::List:
#else
		case QMetaType::QStringList:
		case QMetaType::QVariantList:
#endif
			return tr("(List)");

		default:
			break;
	}

	return QtnPropertyQString::getEmptyPlaceholderStr();
}

QtnPropertyDelegateQVariant::QtnPropertyDelegateQVariant(
	QtnPropertyQVariantBase &owner)
	: QtnPropertyDelegateTyped<QtnPropertyQVariantBase>(owner)
{
}

void QtnPropertyDelegateQVariant::Register(QtnPropertyDelegateFactory &factory)
{
	factory.registerDelegateDefault(&QtnPropertyQVariantBase::staticMetaObject,
		&qtnCreateDelegate<QtnPropertyDelegateQVariant,
			QtnPropertyQVariantBase>,
		"QVariant");
}

bool QtnPropertyDelegateQVariant::acceptKeyPressedForInplaceEditImpl(
	QKeyEvent *keyEvent) const
{
	if (QtnPropertyDelegateTyped<QtnPropertyQVariantBase>::
			acceptKeyPressedForInplaceEditImpl(keyEvent))
		return true;

	// accept any printable key
	return qtnAcceptForLineEdit(keyEvent);
}

QWidget *QtnPropertyDelegateQVariant::createValueEditorImpl(
	QWidget *parent, const QRect &rect, QtnInplaceInfo *inplaceInfo)
{
	auto editor = new QtnLineEditBttn(parent);
	editor->setGeometry(rect);

	new QtnPropertyQVariantEditBttnHandler(this, *editor);

	qtnInitLineEdit(editor->lineEdit, inplaceInfo);
	return editor;
}

bool QtnPropertyDelegateQVariant::propertyValueToStrImpl(
	QString &strValue) const
{
	auto value = owner().value();
	strValue = QtnPropertyQVariant::valueToString(value);

	if (strValue.isEmpty())
	{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		strValue = QtnPropertyQVariant::getPlaceholderStr(value.type());
#else
		strValue = QtnPropertyQVariant::getPlaceholderStr(
			static_cast<QMetaType::Type>(value.typeId()));
#endif
	}

	return true;
}

bool QtnPropertyDelegateQVariant::isPlaceholderColor() const
{
	return QtnPropertyQVariant::valueToString(owner().value()).isEmpty();
}

QtnPropertyQVariantEditBttnHandler::QtnPropertyQVariantEditBttnHandler(
	QtnPropertyDelegate *delegate, QtnLineEditBttn &editor)
	: QtnPropertyEditorHandlerType(delegate, editor)
	, dialog(new CustomPropertyEditorDialog(&editor))
	, is_object(false)
{
	dialogContainer = connectDialog(dialog);
	updateEditor();

	editor.lineEdit->installEventFilter(this);

	QObject::connect(editor.toolButton, &QToolButton::clicked, this,
		&QtnPropertyQVariantEditBttnHandler::onToolButtonClicked);

	QObject::connect(editor.lineEdit, &QLineEdit::editingFinished, this,
		&QtnPropertyQVariantEditBttnHandler::onEditingFinished);

	QObject::connect(dialog, &CustomPropertyEditorDialog::apply, this,
		&QtnPropertyQVariantEditBttnHandler::onApplyData);
}

void QtnPropertyQVariantEditBttnHandler::revertInput()
{
	reverted = true;
}

void QtnPropertyQVariantEditBttnHandler::onToolButtonClick()
{
	onToolButtonClicked(false);
}

void QtnPropertyQVariantEditBttnHandler::updateEditor()
{
	auto edit = editor().lineEdit;
	edit->setReadOnly(!stateProperty()->isEditableByUser());

	if (stateProperty()->isMultiValue())
	{
		edit->clear();
		edit->setPlaceholderText(QtnMultiProperty::getMultiValuePlaceholder());
	} else
	{
		QVariant value;
		value = property().value();

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		if (QtnPropertyQVariant::variantIsObject(value.type()))
#else
		if (QtnPropertyQVariant::variantIsObject(
				static_cast<QMetaType::Type>(value.typeId())))
#endif
		{
			is_object = true;
			edit->setText(QString());
		} else
		{
			is_object = false;
			edit->setText(value.toString());
		}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
		edit->setPlaceholderText(
			QtnPropertyQVariant::getPlaceholderStr(value.type()));
#else
		edit->setPlaceholderText(QtnPropertyQVariant::getPlaceholderStr(
			static_cast<QMetaType::Type>(value.typeId())));
#endif
		edit->selectAll();
	}
}

void QtnPropertyQVariantEditBttnHandler::onEditingFinished()
{
	if (canApply())
	{
		auto text = editor().lineEdit->text();

		if (!is_object || !text.isEmpty())
		{
			if (is_object || text != property().value().toString())
				property().setValue(text, delegate()->editReason());

			updateEditor();
		}
	}

	applyReset();
}

void QtnPropertyQVariantEditBttnHandler::onToolButtonClicked(bool)
{
	QVariant data;
	auto text = editor().lineEdit->text();

	auto property = &this->property();
	auto value = property->value();

	if (!is_object && text != value.toString())
	{
		data = text;
	} else
		data = value;

	auto dialogContainer = this->dialogContainer;
	reverted = true;
	dialog->setReadOnly(!stateProperty()->isEditableByUser());

	volatile bool destroyed = false;
	auto connection = QObject::connect(this, &QObject::destroyed,
		[&destroyed]() mutable { destroyed = true; });

	if (dialog->execute(property->name(), data) && !destroyed)
		property->setValue(data, delegate()->editReason());

	if (!destroyed)
	{
		QObject::disconnect(connection);
		updateEditor();
	}

	Q_UNUSED(dialogContainer);
}

void QtnPropertyQVariantEditBttnHandler::onApplyData(const QVariant &data)
{
	property().setValue(data, delegate()->editReason());
	updateEditor();
}
