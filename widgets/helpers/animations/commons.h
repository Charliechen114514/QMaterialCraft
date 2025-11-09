#ifndef COMMONS_H
#define COMMONS_H
#include "CCWidgets_BuildDefine.h"
#include <QEasingCurve>
#include <QVariant>

class QVariantAnimation;
namespace CCWidgetLibrary {
namespace animation {

	struct CCWIDGET_EXPORT AnimationConfig {
		QEasingCurve curve;
		int period_time;
	};

	struct CCWIDGET_EXPORT AnimationSession {
		QVariant begin;
		QVariant end;
	};

	void CCWIDGET_EXPORT apply_settings(QVariantAnimation* animation,
	                                    const AnimationConfig& config);

	void CCWIDGET_EXPORT apply_session(QVariantAnimation* animation,
	                                   const AnimationSession& session);
}
}

#endif // COMMONS_H
