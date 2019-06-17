#ifndef _MC_MODEL_CONTAINER_H_
#define _MC_MODEL_CONTAINER_H_

#include <QObject>

struct McModelContainerData;

QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

class McModelContainer : public QObject {
	Q_OBJECT

public:
	explicit McModelContainer(QObject *parent = 0);
	~McModelContainer();

	Q_INVOKABLE QAbstractItemModel *get(const QString &beanName) noexcept;

private:
	QScopedPointer<McModelContainerData> d;
};

#endif // !_MC_MODEL_CONTAINER_H_