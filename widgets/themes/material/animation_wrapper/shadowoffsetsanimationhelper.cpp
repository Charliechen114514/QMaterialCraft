#include "shadowoffsetsanimationhelper.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QVariantAnimation>
#include <QWidget>
namespace CCWidgetLibrary {
ShadowOffsetsAnimation::ShadowOffsetsAnimation(QWidget* parent)
    : QObject { parent } {
	attached_widget = parent;

	offsetY_animation = std::make_unique<AnimationHolder>(this, "offsetY");

	shadow_offset_holder = std::make_unique<AnimationHolder>(this);
	auto shadow_margin_holder_raw = shadow_offset_holder->get_animations();
	connect(shadow_margin_holder_raw, &QVariantAnimation::valueChanged,
	        this, [this](const QVariant& v) {
		        QPoint pair = v.toPoint();
		        auto drop = dynamic_cast<QGraphicsDropShadowEffect*>(attached_widget->graphicsEffect());
		        drop->setOffset(pair.x(), pair.y());
	        });

	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(attached_widget);
	shadow->setBlurRadius(shadow_margin);
	shadow->setColor(shadows_color);
	shadow->setOffset(shadow_margin, shadow_height);
	attached_widget->setGraphicsEffect(shadow);

	apply_duration(DURATION_TIME);
}

void ShadowOffsetsAnimation::apply_duration(const int duration_new) {
	offsetY_animation->get_helpers()->applySettings(
	    [duration_new](AnimationHelper::SettingsConfig& config) {
		    config.period_time = duration_new;
	    });
	shadow_offset_holder->get_helpers()->applySettings(
	    [duration_new](AnimationHelper::SettingsConfig& config) {
		    config.period_time = duration_new;
	    });
}

int ShadowOffsetsAnimation::duration() const {
	return offsetY_animation->get_animations()->duration();
}

void ShadowOffsetsAnimation::setoffsetY(qreal v) {
	offsetY_ = v;
	emit offsetYChanged(v);
	attached_widget->update();
}

qreal ShadowOffsetsAnimation::offsetY() const {
	return offsetY_;
}

void ShadowOffsetsAnimation::translate_for_none_clip(QPainter& p, QRectF& sourceRect) {
	p.translate(0, offsetY_ / 2);
	sourceRect.adjust(0, 0, 0, -maxOffsetY_ / 2);
}

void ShadowOffsetsAnimation::translate_rect_for_none_clip(QRectF& sourceRect) {
	sourceRect.adjust(0, 0, 0, -maxOffsetY_ / 2);
}

int ShadowOffsetsAnimation::shadowMargin() const {
	return shadow_margin;
}

int ShadowOffsetsAnimation::shadowHeight() const {
	return shadow_height;
}

void ShadowOffsetsAnimation::setShadowMargin(int margin) {
	if (shadow_margin == margin)
		return;
	shadow_margin = margin;
	emit shadowMarginChanged(shadow_margin);
	attached_widget->update();
}

void ShadowOffsetsAnimation::setShadowHeight(int height) {
	if (shadow_height == height)
		return;
	shadow_height = height;
	emit shadowHeightChanged(shadow_height);
	attached_widget->update();
}

void ShadowOffsetsAnimation::
    process_shadowoffset_action(const MouseEventType e) {
	switch (e) {
	case MouseEventType::MOUSE_PRESS:
		offsetY_animation->get_helpers()->applySession(
		    [this](AnimationHelper::RuntimeConfig& config) {
			    config.start = offsetY_;
			    config.end = maxOffsetY_;
		    });
		shadow_offset_holder->get_helpers()->applySession(
		    [this](AnimationHelper::RuntimeConfig& config) {
			    config.start = QPoint { shadow_margin, shadow_height };
			    config.end = QPoint { shadow_margin / 2, shadow_height / 2 };
		    });
		break;
	case MouseEventType::MOUSE_MOVE:
		break; // do noting there lol
	case MouseEventType::MOUSE_RELEASE:
		offsetY_animation->get_helpers()->applySession(
		    [this](AnimationHelper::RuntimeConfig& config) {
			    config.start = offsetY_;
			    config.end = 0.0;
		    });
		shadow_offset_holder->get_helpers()->applySession(
		    [this](AnimationHelper::RuntimeConfig& config) {
			    config.start = QPoint { shadow_margin / 2, shadow_height / 2 };
			    config.end = QPoint { shadow_margin, shadow_height };
		    });
		break;
	}
}

qreal ShadowOffsetsAnimation::getMaxOffsetY() const {
	return maxOffsetY_;
}

void ShadowOffsetsAnimation::setMaxOffsetY(qreal maxOffsetY) {
	if (maxOffsetY_ == maxOffsetY) {
		return;
	}
	maxOffsetY_ = maxOffsetY;
	emit offsetYMaxChanged(maxOffsetY_);
}
}
