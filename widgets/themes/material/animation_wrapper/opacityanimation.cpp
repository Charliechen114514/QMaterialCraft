#include "opacityanimation.h"
#include <QWidget>

namespace CCWidgetLibrary {
OpacityAnimation::OpacityAnimation(QWidget* parent)
    : QObject { parent } {
	opacity_animation = std::make_unique<AnimationHolder>(this, "opacity");
	attached_parent = parent;
}

void OpacityAnimation::setOpacity(qreal opacity) {
	if (qFuzzyCompare(opacity, opacity_))
		return;
	opacity_ = opacity;
	emit opacityChanged();
	attached_parent->update();
}

qreal OpacityAnimation::opacity() const {
	return opacity_;
}

void OpacityAnimation::applyConfigs(AnimationHelper::ApplySettingsHandler handler) {
	opacity_animation->get_helpers()->applySettings(handler);
}

void OpacityAnimation::activate_as_fadeIn() {
	opacity_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& config) {
		    config.start = min_opacity_;
		    config.end = max_opacity_;
	    });
}

void OpacityAnimation::activate_as_fadeOut() {
	opacity_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& config) {
		    config.start = max_opacity_;
		    config.end = min_opacity_;
	    });
}

void OpacityAnimation::setMaxOpacity(qreal maxOpacity) {
	max_opacity_ = maxOpacity;
}

qreal OpacityAnimation::maxOpacity() const {
	return max_opacity_;
}

void OpacityAnimation::setMinOpacity(qreal minOpacity) {
	min_opacity_ = minOpacity;
}

qreal OpacityAnimation::minOpacity() const {
	return min_opacity_;
}
}
