/*******************************************************************************
Copyright (c) 2012-2016 Alex Zhondin <lexxmark.dev@gmail.com>
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

#include "PropertyQRectF.h"
#include <QRegularExpression>

#include "PropertyQRect.h"
#include "PropertyQSize.h"

QtnProperty *QtnPropertyQRectFBase::createLeftProperty(bool move)
{
	return createFieldProperty(&QRectF::left,
		move ? &QRectF::moveLeft : &QRectF::setLeft,
		QtnPropertyQRect::leftKey(), QtnPropertyQRect::leftString(),
		QtnPropertyQRect::leftDescriptionFmt());
}

QtnProperty *QtnPropertyQRectFBase::createTopProperty(bool move)
{
	return createFieldProperty(&QRectF::top,
		move ? &QRectF::moveTop : &QRectF::setTop, QtnPropertyQRect::topKey(),
		QtnPropertyQRect::topString(), QtnPropertyQRect::topDescriptionFmt());
}

QtnProperty *QtnPropertyQRectFBase::createRightProperty(bool move)
{
	return createFieldProperty(&QRectF::right,
		move ? &QRectF::moveRight : &QRectF::setRight,
		QtnPropertyQRect::rightKey(), QtnPropertyQRect::rightString(),
		QtnPropertyQRect::rightDescriptionFmt());
}

QtnProperty *QtnPropertyQRectFBase::createBottomProperty(bool move)
{
	return createFieldProperty(&QRectF::bottom,
		move ? &QRectF::moveBottom : &QRectF::setBottom,
		QtnPropertyQRect::bottomKey(), QtnPropertyQRect::bottomString(),
		QtnPropertyQRect::bottomDescriptionFmt());
}

QtnProperty *QtnPropertyQRectFBase::createWidthProperty()
{
	return createFieldProperty(&QRectF::width, &QRectF::setWidth,
		QtnPropertyQSize::widthKey(), QtnPropertyQSize::widthDisplayName(),
		QtnPropertyQSize::widthDescriptionFmt());
}

QtnProperty *QtnPropertyQRectFBase::createHeightProperty()
{
	return createFieldProperty(&QRectF::height, &QRectF::setHeight,
		QtnPropertyQSize::heightKey(), QtnPropertyQSize::heightDisplayName(),
		QtnPropertyQSize::heightDescriptionFmt());
}

QtnPropertyQRectFBase::QtnPropertyQRectFBase(QObject *parent)
	: ParentClass(parent)
{
}

bool QtnPropertyQRectFBase::fromStrImpl(
	const QString &str, QtnPropertyChangeReason reason)
{
	static QRegularExpression parserRect(
		QStringLiteral("^\\s*QRectF\\s*\\(([^\\)]+)\\)\\s*$"),
		QRegularExpression::CaseInsensitiveOption);
	static QRegularExpression parserParams(
		QStringLiteral("^\\s*(-?\\d+(\\.\\d*)?)\\s*,\\s*(-?\\d+(\\.\\d*)?)\\s*,"
					   "\\s*(\\d+(\\.\\d*)?)\\s*,\\s*(\\d+(\\.\\d*)?)\\s*$"),
		QRegularExpression::CaseInsensitiveOption);

	auto matchRect = parserRect.match(str);
	if (!matchRect.hasMatch())
		return false;

	QString paramStr = matchRect.captured(1);
	auto matchParams = parserParams.match(paramStr);
	if (!matchParams.hasMatch())
		return false;

	bool ok = false;
	double left = matchParams.captured(1).toDouble(&ok);
	if (!ok)
		return false;

	double top = matchParams.captured(3).toDouble(&ok);
	if (!ok)
		return false;

	double width = matchParams.captured(5).toDouble(&ok);
	if (!ok)
		return false;

	double height = matchParams.captured(7).toDouble(&ok);
	if (!ok)
		return false;

	return setValue(QRectF(left, top, width, height), reason);
}

bool QtnPropertyQRectFBase::toStrImpl(QString &str) const
{
	auto v = value();

	str = QStringLiteral("QRectF(%1, %2, %3, %4)")
			  .arg(v.left())
			  .arg(v.top())
			  .arg(v.width())
			  .arg(v.height());

	return true;
}

QtnPropertyQRectF::QtnPropertyQRectF(QObject *parent)
	: QtnSinglePropertyValue<QtnPropertyQRectFBase>(parent)
{
}

QtnPropertyQRectFCallback::QtnPropertyQRectFCallback(QObject *parent)
	: QtnSinglePropertyCallback<QtnPropertyQRectFBase>(parent)
{
}
