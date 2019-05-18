#include "McControllerContainer.h"

#include <qdebug.h>
#include <qmetaobject.h>

#include "McIocContainer.h"
#include "IMcApplicationContext.h"
#include "McGlobal.h"
#include "McRestResponse.h"
#include "McJsonUtils.h"

struct McControllerContainerData {
	QMap<QString, QObject *> controllers;	// 键为beanName，值为controller对象
};

McControllerContainer::McControllerContainer(QObject *parent)
	: QObject(parent)
	, d(new McControllerContainerData)
{
	IMcApplicationContext *appCtx = McIocContainer::getInstance()->getApplicationContext();
	auto beanNames = McIocContainer::getInstance()->getComponent(MC_CONTROLLER_STR);
	for (const auto &beanName : beanNames)
		d->controllers.insert(beanName, appCtx->getBean(beanName));
}

McControllerContainer::~McControllerContainer(){
}

QString McControllerContainer::invoke(const QString &uri) noexcept {
	auto list = uri.split('?', QString::SkipEmptyParts);
	if (list.isEmpty())
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));
	auto beanAndFunc = list.at(0).split('.', QString::SkipEmptyParts);
	if (beanAndFunc.size() != 2)
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));
	if(!d->controllers.contains(beanAndFunc.at(0)))
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("访问路径不存在"));
	QString param = list.size() == 2 ? list.at(1) : "";
	return invokeForUri(d->controllers[beanAndFunc.at(0)], beanAndFunc.at(1), param);
}

QString McControllerContainer::invoke(const QString &uri, const QString &data) noexcept {
	qDebug() << uri << data;
	return "";
}

QString McControllerContainer::invokeForUri(QObject *bean, const QString &func, const QString &param) noexcept {
	const QMetaObject *metaBean = bean->metaObject();
	// <参数名，参数值>
	QMap<QString, QVariant> args = splitParam(param);
	int methodOffsetEnd = metaBean->methodOffset() + metaBean->methodCount();
	for (int i = metaBean->methodOffset(); i < methodOffsetEnd; ++i) {
		QMetaMethod method = metaBean->method(i);
		if(method.name() != func)
			continue;
		if (!isMethodMatching(method, args.keys()))
			continue;
		return invokeForArgs(bean, method, args);
	}
	return McJsonUtils::responseToJson(McRestResponse<QString>::fail("请求参数错误"));
}

QMap<QString, QVariant> McControllerContainer::splitParam(const QString &param) noexcept {
	QMap<QString, QVariant> args;
	QStringList params = param.split('&', QString::SkipEmptyParts);
	for (const auto &p : params) {
		QStringList nameAndValue = p.split('=', QString::SkipEmptyParts);
		if(nameAndValue.size() != 2)
			continue;
		args.insert(nameAndValue.at(0), nameAndValue.at(1));
	}
	return args;
}

bool McControllerContainer::isMethodMatching(const QMetaMethod &m, const QList<QString> &names) noexcept {
	QList<QByteArray> methodParamNames = m.parameterNames();
	if (methodParamNames.size() > names.size())
		return false;
	QList<QString> argNames = names;
	if (methodParamNames.size() == argNames.size()) {
		removeDuplication(argNames, methodParamNames);
		if (methodParamNames.isEmpty())
			return true;
		else
			return false;
	}
	else {
		QList<QByteArray> methodParamTypes = m.parameterTypes();
		removeDuplication(argNames, methodParamNames, methodParamTypes);
		if (methodParamNames.isEmpty())
			return false;
		for (const QByteArray &type : methodParamTypes) {
			if (!type.endsWith('*'))
				return false;
			int typeId = QMetaType::type(type);
			if (typeId == QMetaType::UnknownType)
				return false;
			const QMetaObject *mobj = QMetaType::metaObjectForType(typeId);
			for (const QString &name : argNames) {
				if (mobj->indexOfProperty(name.toLocal8Bit()) == -1)
					continue;
				argNames.removeOne(name);
			}
		}
		if (argNames.isEmpty())
			return true;
		else
			return false;
	}
	return false;
}

void McControllerContainer::removeDuplication(QList<QString> &argNames, QList<QByteArray> &paramNames, QList<QByteArray> &paramTypes) noexcept {
	for (int i = 0; i < paramNames.size(); ++i) {
		if (!argNames.contains(paramNames.at(i)))
			continue;
		argNames.removeOne(paramNames.at(i));
		paramNames.removeAt(i);
		paramTypes.removeAt(i);
		--i;
	}
}

QString McControllerContainer::invokeForArgs(QObject *bean, const QMetaMethod &method, const QMap<QString, QVariant> &args) noexcept {
	QString returnValue;
	QGenericReturnArgument returnArg;
	if (method.returnType() == QMetaType::Void)
		returnValue = "调用成功";
	else
		returnArg = Q_RETURN_ARG(QString, returnValue);
	QVector<QGenericArgument> arguments;
	arguments.resize(10);
	QList<QByteArray> paramNames = method.parameterNames();
	QList<QByteArray> paramTypes = method.parameterTypes();
	for (int i = 0; i < paramTypes.size(); ++i) {
		QByteArray type = paramTypes.at(i);
		QVariant value;
		if (type.endsWith('*'))
			value = makeValue(type, args);
		else {
			value = args[paramNames.at(i)];
			value.convert(QMetaType::type(type));
		}
		// 由于Q_ARG宏所调用的函数是直接取value的地址，所以value不能是局部变量
		arguments.replace(i, Q_ARG(QVariant, value));
	}
	if (!method.invoke(bean, returnArg,
		arguments.at(0),
		arguments.at(1),
		arguments.at(2),
		arguments.at(3),
		arguments.at(4),
		arguments.at(5),
		arguments.at(6),
		arguments.at(7),
		arguments.at(8),
		arguments.at(9)))
		return McJsonUtils::responseToJson(McRestResponse<QString>::fail("函数调用失败"));
	return returnValue;
}

QVariant McControllerContainer::makeValue(const QByteArray &typeName, const QMap<QString, QVariant> &args) noexcept {
	int typeId = QMetaType::type(typeName);
	if (typeId == QMetaType::UnknownType) {
		qDebug() << QString("类型名为%1的类没有注册!").arg(typeName.data());
		return QVariant();
	}
	const QMetaObject *mobj = QMetaType::metaObjectForType(typeId);
	QObject *obj = mobj->newInstance();
	int proOffsetEnd = mobj->propertyOffset() + mobj->propertyCount();
	for (int i = mobj->propertyOffset(); i < proOffsetEnd; ++i) {
		QMetaProperty pro = mobj->property(i);
		if(!args.contains(pro.name()))
			continue;
		if (!pro.write(obj, args[pro.name()]))
			qDebug() << QString("类%1中的属性%2无法动态写入值").arg(typeName.data(), pro.name());
	}
	return QVariant::fromValue(obj);
}
