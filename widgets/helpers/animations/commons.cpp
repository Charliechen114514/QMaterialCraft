#include "helpers/animations/commons.h"
#include <QVariantAnimation>

namespace CCWidgetLibrary::animation {
void apply_settings(QVariantAnimation* animation,
                    const AnimationConfig& config) {
	animation->setDuration(config.period_time);
	animation->setEasingCurve(config.curve);
}

void apply_session(QVariantAnimation* animation,
                   const AnimationSession& session) {
	animation->stop();
	animation->setStartValue(session.begin);
	animation->setEndValue(session.end);
	animation->start();
}
}
