#include "McJsonUtils.h"

#include <qmetaobject.h>

QString McJsonUtils::objToJson(QObject *obj) noexcept {
	return QJsonDocument(objToJsonObj(obj)).toJson();
}

QJsonObject McJsonUtils::objToJsonObj(QObject *obj) noexcept {
	if (!obj)
		return QJsonObject();
	QJsonObject jsonObj;
	const QMetaObject *mobj = obj->metaObject();
	int offsetOver = mobj->propertyOffset() + mobj->propertyCount();
	for (int i = mobj->propertyOffset(); i < offsetOver; ++i) {
		QMetaProperty pro = mobj->property(i);
		if (pro.type() == QMetaType::UnknownType)
			continue;
		QVariant variant = pro.read(obj);
		if (pro.type() >= QMetaType::User) {
			if(isPointer(pro.typeName()))
				variant = objToJsonObj(variant.value<QObject *>());
			else if (isListPointer(pro.typeName())) {
				QJsonArray jsonArr;
				QList<QObject *> listObj = variant.value<QList<QObject *>>();
				for (auto o : listObj)
					jsonArr.append(objToJsonObj(o));
				variant = jsonArr;
			}
		}
		QJsonValue jsonValue = QJsonValue::fromVariant(variant);
		jsonObj.insert(pro.name(), jsonValue);
	}
	return jsonObj;
}

QJsonObject McJsonUtils::gadgetToJsonObj(void *gadget, const QMetaObject *mobj) noexcept {
	QJsonObject jsonObj;
	int offsetOver = mobj->propertyOffset() + mobj->propertyCount();
	for (int i = mobj->propertyOffset(); i < offsetOver; ++i) {
		QMetaProperty pro = mobj->property(i);
		if (pro.type() == QMetaType::UnknownType)
			continue;
		QVariant variant = pro.readOnGadget(gadget);
		QJsonValue jsonValue = QJsonValue::fromVariant(variant);
		jsonObj.insert(pro.name(), jsonValue);
	}
	return jsonObj;
}

bool McJsonUtils::isPointer(const QString &typeName) noexcept {
	return typeName.endsWith('*');
}

bool McJsonUtils::isListPointer(const QString &typeName) noexcept {
	return typeName.startsWith("QList<") && typeName.contains('*');
}
