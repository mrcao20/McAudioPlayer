#pragma once

#include <QtCore/qglobal.h>

#if defined(SERVICE_LIBRARY)
#  define SERVICE_EXPORT Q_DECL_EXPORT
#else
#  define SERVICE_EXPORT Q_DECL_IMPORT
#endif
