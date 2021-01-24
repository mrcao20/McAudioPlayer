#pragma once

#include <McIoc/McGlobal.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

class IMcAcquireModel {
    MC_TYPELIST()
public:
    virtual ~IMcAcquireModel() noexcept = default;
    
    virtual QAbstractItemModel *getModel() const noexcept = 0;
};

MC_DECL_METATYPE(IMcAcquireModel)
