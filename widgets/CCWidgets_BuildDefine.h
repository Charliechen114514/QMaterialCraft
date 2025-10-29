#ifndef CCSILDER_GLOBAL_H
#define CCSILDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CCWIDGET_LIBRARY_BUILD)
#define CCWIDGET_EXPORT Q_DECL_EXPORT
#else
#define CCWIDGET_EXPORT Q_DECL_IMPORT
#endif

#endif // CCSILDER_GLOBAL_H
