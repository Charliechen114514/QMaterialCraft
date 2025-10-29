#include "rippleanimation.h"
#include <QMouseEvent>
#include <QPainter>
#include <QVariantAnimation>
#include <QWidget>
namespace CCWidgetLibrary {

RippleAnimation::RippleAnimation(QWidget* parent)
    : QObject { parent } {
	attached_widget = parent;
	ripple_animation = std::make_unique<AnimationHolder>(this);
	apply_duration(RIPPLE_TIME);

	auto ripple_animation_raw = ripple_animation->get_animations();
	connect(ripple_animation_raw, &QVariantAnimation::valueChanged,
	        this, [this](const QVariant& v) {
		        QPointF vals = v.toPointF();
		        rippleRadius_ = vals.x();
		        rippleOpacity_ = vals.y();
		        attached_widget->update();
	        });
}

void RippleAnimation::apply_duration(int duration_new) {
	ripple_animation->get_helpers()->applySettings(
	    [duration_new](AnimationHelper::SettingsConfig& conf) {
		    conf.period_time = duration_new;
	    });
}

int RippleAnimation::duration() const {
	return ripple_animation->get_animations()->duration();
}

void RippleAnimation::process_ripple_draw(QPainter& p, const QColor& baseColor) {
	if (!rippleAvaiable()) {
		return;
	}
	QColor rippleColor = baseColor;
	rippleColor.setAlphaF(rippleOpacity_);
	p.setBrush(rippleColor);
	p.setPen(Qt::NoPen);
	p.drawEllipse(pressPosition, rippleRadius_, rippleRadius_);
}

void RippleAnimation::process_ripple_draw(QPainter& p, const QPointF center, const QColor& baseColor) {
	if (!rippleAvaiable()) {
		return;
	}

	QColor rippleColor(baseColor);
	rippleColor.setAlphaF(rippleOpacity_);
	p.setBrush(rippleColor);

	p.drawEllipse(center,
	              rippleRadius_, rippleRadius_);
}

void RippleAnimation::activate_with_mouse_event(const MouseEventType e, QMouseEvent* ev) {
	switch (e) {
	case MouseEventType::MOUSE_PRESS:
		pressPosition = ev->pos();
		ripple_animation->get_helpers()->applySession(
		    [this](AnimationHelper::RuntimeConfig& config) {
			    config.start = QPointF { 0.0, 0.4 };
			    config.end = QPointF { attached_widget->width() * 1.2, 0.0 };
		    });
		break;
	case MouseEventType::MOUSE_MOVE:
		break;
	case MouseEventType::MOUSE_RELEASE:
		break;
	}
}

void RippleAnimation::activate(const MouseEventType e, const qreal size) {
	switch (e) {
	case MouseEventType::MOUSE_PRESS:
		ripple_animation->get_helpers()->applySession(
		    [size, this](AnimationHelper::RuntimeConfig& config) {
			    config.start = QPointF { 0.0, 0.4 };
			    config.end = QPointF { size, 0.0 };
		    });
		break;
	case MouseEventType::MOUSE_MOVE:
		break;
	case MouseEventType::MOUSE_RELEASE:
		break;
	}
}

bool RippleAnimation::rippleAvaiable() const {
	return rippleOpacity_ > 0.0;
}

void RippleAnimation::setRippleRadius(qreal v) {
	rippleRadius_ = v;
	emit rippleRadiusChanged(v);
	attached_widget->update();
}

void RippleAnimation::setRippleOpacity(qreal v) {
	rippleOpacity_ = v;
	emit rippleOpacityChanged(v);
	attached_widget->update();
}

qreal RippleAnimation::rippleRadius() const {
	return rippleRadius_;
}

qreal RippleAnimation::rippleOpacity() const {
	return rippleOpacity_;
}

}
