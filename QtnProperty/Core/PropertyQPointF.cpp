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

#include "PropertyQPointF.h"
#include <QRegularExpression>

#include "PropertyQPoint.h"

QtnPropertyQPointFBase::QtnPropertyQPointFBase(QObject *parent)
	: ParentClass(parent)
{
}

QtnProperty *QtnPropertyQPointFBase::createXProperty()
{
	return createFieldProperty(&QPointF::x, &QPointF::setX,
		QtnPropertyQPoint::xKey(), getXLabel(), getXDescriptionFormat());
}

QtnProperty *QtnPropertyQPointFBase::createYProperty()
{
	return createFieldProperty(&QPointF::y, &QPointF::setY,
		QtnPropertyQPoint::yKey(), getYLabel(), getYDescriptionFormat());
}

QString QtnPropertyQPointFBase::getXLabel() const
{
	return QtnPropertyQPoint::xDisplayName();
}

QString QtnPropertyQPointFBase::getXDescriptionFormat() const
{
	return QtnPropertyQPoint::xDescriptionFmt();
}

QString QtnPropertyQPointFBase::getYLabel() const
{
	return QtnPropertyQPoint::yDisplayName();
}

QString QtnPropertyQPointFBase::getYDescriptionFormat() const
{
	return QtnPropertyQPoint::yDescriptionFmt();
}

bool QtnPropertyQPointFBase::fromStrImpl(
	const QString &str, QtnPropertyChangeReason reason)
{
	static QRegularExpression parserPoint(
		QStringLiteral("^\\s*QPointF\\s*\\(([^\\)]+)\\)\\s*$"),
		QRegularExpression::CaseInsensitiveOption);
	auto matchPoint = parserPoint.match(str);

	if (!matchPoint.hasMatch())
		return false;

	QString paramStr = matchPoint.captured(1);

	static QRegularExpression parserParams(
		QStringLiteral(
			"^\\s*(-?\\d+(\\.\\d*)?)\\s*,\\s*(-?\\d+(\\.\\d*)?)\\s*$"),
		QRegularExpression::CaseInsensitiveOption);
	auto matchParams = parserParams.match(paramStr);

	if (!matchParams.hasMatch())
		return false;

	bool ok = false;
	double x = matchParams.captured(1).toDouble(&ok);

	if (!ok)
		return false;

	double y = matchParams.captured(3).toDouble(&ok);

	if (!ok)
		return false;

	return setValue(QPointF(x, y), reason);
}

bool QtnPropertyQPointFBase::toStrImpl(QString &str) const
{
	QPointF v = value();
	str = QStringLiteral("QPointF(%1, %2)").arg(v.x()).arg(v.y());
	return true;
}

QtnPropertyQPointF::QtnPropertyQPointF(QObject *parent)
	: QtnSinglePropertyValue<QtnPropertyQPointFBase>(parent)
{
}

QtnPropertyQPointFCallback::QtnPropertyQPointFCallback(QObject *parent)
	: QtnSinglePropertyCallback<QtnPropertyQPointFBase>(parent)
{
}
