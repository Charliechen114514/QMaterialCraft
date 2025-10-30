#include "animation_helpers.h"
#include <QPropertyAnimation>
#include <QVariantAnimation>
namespace CCWidgetLibrary {

AnimationHelper::AnimationHelper(QVariantAnimation* binding_animations) {
	holding_src = binding_animations;
}

AnimationHelper::~AnimationHelper() {
}

AnimationHelper& AnimationHelper::applySettings(ApplySettingsHandler conf) {
	SettingsConfig config;
	config.curve = holding_src->easingCurve();
	config.period_time = holding_src->duration();

	// run the applies
	conf(config);

	holding_src->setDuration(config.period_time);
	holding_src->setEasingCurve(config.curve);

	return *this;
}

AnimationHelper& AnimationHelper::applySession(ApplyConfigHandler conf) {
	if (!holding_src) {
	}

	RuntimeConfig runtime_config;
	runtime_config.start = holding_src->startValue();
	runtime_config.end = holding_src->endValue();

	conf(runtime_config);

	holding_src->stop();
	holding_src->setStartValue(runtime_config.start);
	holding_src->setEndValue(runtime_config.end);
	holding_src->start();

	return *this;
}

AnimationHolder::AnimationHolder(QObject* attached_object) {
	animations = new QVariantAnimation(attached_object);
	helpers = std::make_unique<AnimationHelper>(animations);
}

AnimationHolder::AnimationHolder(QObject* attached_object, QByteArray property) {
	animations = new QPropertyAnimation(attached_object, property);
	helpers = std::make_unique<AnimationHelper>(animations);
}

AnimationHolder::~AnimationHolder() {
}
}
