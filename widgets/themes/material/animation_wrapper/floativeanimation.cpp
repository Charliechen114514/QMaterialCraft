#include "floativeanimation.h"
#include <QWidget>
namespace CCWidgetLibrary {
FloativeAnimation::FloativeAnimation(QWidget* parent)
    : QObject { parent } {
	attached_parent = parent;
	floating_animation = std::make_unique<AnimationHolder>(this, "floative_y");

	applyConfig([](AnimationHelper::SettingsConfig& conf) {
		conf.period_time = FLOATIVE_ANIMATION;
		conf.curve = QEasingCurve::InOutQuad;
	});
}

void FloativeAnimation::applyConfig(
    AnimationHelper::ApplySettingsHandler handler) {
	floating_animation->get_helpers()->applySettings(handler);
}

qreal FloativeAnimation::floative_y() const {
	return floative_y_;
}

void FloativeAnimation::setFloative_y(const qreal floative_y) {
	if (floative_y_ == floative_y) {
		return;
	}
	floative_y_ = floative_y;
	emit floativeYChanged(floative_y_);
	attached_parent->update();
	// attached_parent->update(attached_parent->rect().adjusted(0, -floative_y_max, 0, 0));
}

qreal FloativeAnimation::getFloative_y_max() const {
	return floative_y_max;
}

void FloativeAnimation::setFloative_y_max(qreal newFloative_y_max) {
	floative_y_max = newFloative_y_max;
}

void FloativeAnimation::activate_floatup() {
	floating_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& conf) {
		    conf.start = floative_y_;
		    conf.end = floative_y_max;
	    });
}

void FloativeAnimation::activate_sinkdown() {
	floating_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& conf) {
		    conf.start = floative_y_;
		    conf.end = 0;
	    });
}

void FloativeAnimation::activete_with_hover(const HoverEventType ev) {
	switch (ev) {
	case HoverEventType::HOVER_IN:
		activate_floatup();
		break;
	case HoverEventType::HOVER_OUT:
		activate_sinkdown();
		break;
	}
}

}
