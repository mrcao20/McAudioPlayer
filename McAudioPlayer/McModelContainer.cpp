#include "McModelContainer.h"

#include <qmap.h>
#include <qabstractitemmodel.h>
#include <qdebug.h>

#include "McIocContainer.h"
#include "IMcApplicationContext.h"
#include "McGlobal.h"

struct McModelContainerData {
	QMap<QString, QAbstractItemModel *> models;	// 键为beanName，值为model对象
};

McModelContainer::McModelContainer(QObject *parent)
	: QObject(parent)
	, d(new McModelContainerData)
{
	IMcApplicationContext *appCtx = McIocContainer::getInstance()->getApplicationContext();
	auto beanNames = McIocContainer::getInstance()->getComponent(MC_MODEL_STR);
	for (const auto &beanName : beanNames) {
		QAbstractItemModel *model = qobject_cast<QAbstractItemModel *>(appCtx->getBean(beanName));
		if (!model) {
			qDebug() << QString("model '%1' must be inherited from QAbstractItemModel").arg(beanName);
			continue;
		}
		model->setParent(this);	// 所有权归属容器本身
		d->models.insert(beanName, model);
	}
}

McModelContainer::~McModelContainer(){
}

QAbstractItemModel *McModelContainer::get(const QString &beanName) noexcept {
	return d->models[beanName];
}
