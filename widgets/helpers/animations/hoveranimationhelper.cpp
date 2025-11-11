#include "hoveranimationhelper.h"
#include <QColor>
#include <QWidget>
#include <qvariantanimation.h>

namespace CCWidgetLibrary {

HoverAnimationHelper::HoverAnimationHelper(QWidget* parent)
    : QObject { parent } {
	hover_animation = std::make_unique<AnimationHolder>(this, "hoverProcess");
	attached_parent = parent;
	apply_duration(HOVER_TIME);
}

qreal HoverAnimationHelper::hoverProcess() const {
	return hoverProcess_;
}

void HoverAnimationHelper::apply_duration(int duration_new) {
	hover_animation->get_helpers()->applySettings(
	    [duration_new](AnimationHelper::SettingsConfig& conf) {
		    conf.period_time = duration_new;
	    });
}

int HoverAnimationHelper::duration() const {
	return hover_animation->get_animations()->duration();
}

void HoverAnimationHelper::setHoverProcess(qreal hoverProcess) {
	if (hoverProcess == hoverProcess_) {
		return;
	}
	emit hoverProcessChanged(hoverProcess);
	hoverProcess_ = hoverProcess;
	attached_parent->update();
}

void HoverAnimationHelper::activate_hover_animation(const HoverEventType type) {
	switch (type) {
	case HoverEventType::HOVER_IN:
		activate_hover_in();
		break;
	case HoverEventType::HOVER_OUT:
		activate_hover_out();
		break;
	}
}

bool HoverAnimationHelper::isHovering() const {
	return isHovering_;
}

void HoverAnimationHelper::activate_hover_in() {
	isHovering_ = true;

	hover_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& config) {
		    config.start = hoverProcess_;
		    config.end = 1.0;
	    });
}

void HoverAnimationHelper::activate_hover_out() {
	isHovering_ = false;
	hover_animation->get_helpers()->applySession(
	    [this](AnimationHelper::RuntimeConfig& config) {
		    config.start = hoverProcess_;
		    config.end = 0.0;
	    });
}

HoverColorAnimation::HoverColorAnimation(QWidget* parent)
    : HoverAnimationHelper(parent) {
}

QColor HoverColorAnimation::get_current_bgColor(const QColor& base) const {
	if (hoverProcess_ <= 0.0 || hoverProcess_ > 1.0) {
		return base;
	}
	QColor bg = base;
	QColor hoverTint = bg.lighter(light_level_);
	bg = QColor::fromRgbF(
	    bg.redF() + (hoverTint.redF() - bg.redF()) * hoverProcess_,
	    bg.greenF() + (hoverTint.greenF() - bg.greenF()) * hoverProcess_,
	    bg.blueF() + (hoverTint.blueF() - bg.blueF()) * hoverProcess_);
	return bg;
}

}
