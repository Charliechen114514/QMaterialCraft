#include "slidermaterialpaintcontext.h"
#include "material_color_helper.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QWidget>

namespace CCWidgetLibrary {

SliderMaterialPaintContext::SliderMaterialPaintContext(QSlider* widget)
    : SliderPaintContext(widget) {
	_context_name = SLIDER_NAME;
	attached_widget->setMouseTracking(true);

	pressedColor = MaterialSliderHelpers::pressedColor(knobColor);
	ani_radius = new QPropertyAnimation(this, "radius");

	connect(widget, &QSlider::valueChanged, this, [this](int value) {
		QSlider* slider = dynamic_cast<QSlider*>(attached_widget);
		setPercentage(static_cast<float>(value) / slider->maximum());
	});
	connect(ani_radius, &QPropertyAnimation::valueChanged, this, [this]() {
		attached_widget->update();
	});

	ani_radius_helpers = std::make_unique<AnimationHelper>(ani_radius);
	ani_radius_helpers->applySettings([this](AnimationHelper::SettingsConfig& config) {
		config.period_time = ANI_RADIUS_DURATION;
	});

	rippleAnimation = new RippleAnimation(attached_widget);
}

qreal SliderMaterialPaintContext::computeRippleTargetRadius() const {
	static constexpr qreal RIPPLE_SAFETY_MARGIN = 2.0;
	const int start_pos_x = start_postion.x();
	const int start_pos_y = start_postion.y();
	const int trackRectHeight = expected_visible_height();
	const int trackRectWidth = expected_visible_width();

	qreal knobX = start_pos_x + (trackRectWidth)*process_percentage;
	qreal knobY = start_pos_y + trackRectHeight / 2.0;

	qreal leftDistTrack = knobX - start_pos_x;
	qreal rightDistTrack = (start_pos_x + trackRectWidth) - knobX;

	qreal leftDistWidget = knobX;
	qreal rightDistWidget = attached_widget->width() - knobX;
	qreal topDistWidget = knobY;
	qreal bottomDistWidget = attached_widget->height() - knobY;

	qreal minHorizontal = std::min({ leftDistTrack, rightDistTrack, leftDistWidget, rightDistWidget });
	qreal minVertical = std::min(topDistWidget, bottomDistWidget);

	qreal maxAllowed = std::min(minHorizontal, minVertical);
	qreal safetySubtract = current_knob_radius + 2.0 /*shadow*/ + RIPPLE_SAFETY_MARGIN;
	qreal target = maxAllowed - safetySubtract;
	return std::max<qreal>(0.0, target);
}

SliderMaterialPaintContext::~SliderMaterialPaintContext() {
}

bool SliderMaterialPaintContext::paint(QPainter& painter) {
	set_lefttop_positions({ static_cast<int>(attached_widget->width() * 0.05),
	                        attached_widget->height() / 2 });

	const int start_pos_x = start_postion.x();
	const int start_pos_y = start_postion.y();
	const int trackRectHeight = expected_visible_height();
	const int trackRectWidth = expected_visible_width();
	painter.setRenderHint(QPainter::Antialiasing);
	QRectF trackRect(start_pos_x, start_pos_y, trackRectWidth, trackRectHeight);
	painter.setPen(Qt::NoPen);

	painter.setBrush(trackColor);

	painter.drawRoundedRect(trackRect, trackRectHeight / 2, trackRectHeight / 2);

	QRectF progressRect(start_pos_x, start_pos_y, (trackRectWidth)*process_percentage, trackRectHeight);
	painter.setBrush(knobColor);

	painter.drawRoundedRect(progressRect,
	                        trackRectHeight / 2, trackRectHeight / 2);

	qreal knobX = start_pos_x + (trackRectWidth)*process_percentage;
	const QPointF knob_draw_center(knobX, start_pos_y + trackRectHeight / 2);

	painter.setBrush(QColor(0, 0, 0, 40));
	painter.drawEllipse(knob_draw_center,
	                    current_knob_radius + 2, current_knob_radius + 2);

	rippleAnimation->process_ripple_draw(painter, knob_draw_center, pressedColor);

	painter.setBrush(knobColor);
	painter.drawEllipse(knob_draw_center, current_knob_radius, current_knob_radius);
	return true;
}

void SliderMaterialPaintContext::handleMouseEvent(
    const MouseEventType type, QMouseEvent* ev) {
	rippleAnimation->activate(type, computeRippleTargetRadius());
	switch (type) {
	case MouseEventType::MOUSE_PRESS:
		handle_mouseclicked_session(ev);
		break;
	case MouseEventType::MOUSE_MOVE:
		setPercentage(mappings_from_mousepoint(ev));
		return; // do nothing
	case MouseEventType::MOUSE_RELEASE:
		handle_mouserelease_session(ev);
		break;
	}
}

void SliderMaterialPaintContext::handleResizeEvent(const QResizeEvent* ev) {
	current_knob_radius = validify_knob_radius(expected_visible_height() * UNPRESSED_STREEED);
}

void SliderMaterialPaintContext::setColor(
    const QColor& color, const Roles which) {
	switch (which) {
	case Roles::Track:
		trackColor = color;
		break;
	case Roles::Knob:
		knobColor = color;
		pressedColor = MaterialSliderHelpers::pressedColor(knobColor);
		break;
	}
}

QColor SliderMaterialPaintContext::color(const Roles which)
    const noexcept {
	switch (which) {
	case Roles::Track:
		return trackColor;
	case Roles::Knob:
		return knobColor;
		break;
	}

	return {};
}

float SliderMaterialPaintContext::_radius() const noexcept {
	return current_knob_radius;
}

void SliderMaterialPaintContext::setRadius(float radius) {
	if (radius == current_knob_radius) {
		return;
	}

	current_knob_radius = radius;
	attached_widget->update();
	emit knobRadiusChanged(current_knob_radius);
}

void SliderMaterialPaintContext::handle_mouseclicked_session(QMouseEvent* event) {
	setPercentage(mappings_from_mousepoint(event));
	ani_radius_helpers->applySession(
	    [this](AnimationHelper::RuntimeConfig& config) {
		    config.start = current_knob_radius;
		    config.end = validify_knob_radius(PRESSED_STREEED * expected_visible_height());
	    });
}

void SliderMaterialPaintContext::handle_mouserelease_session(QMouseEvent* event) {
	ani_radius->stop();
	ani_radius->setStartValue(current_knob_radius);
	ani_radius->setEndValue(validify_knob_radius(UNPRESSED_STREEED * expected_visible_height()));
	ani_radius->start();
}

int SliderMaterialPaintContext::validify_knob_radius(int val) {
	return std::clamp<float>(val, 0, attached_widget->height() / 2 / UNPRESSED_STREEED);
}

QColor MaterialSliderHelpers::autoTrackColor(const QColor& thumbColor) noexcept {
	return MaterialColorHelper().harmonizeColor(thumbColor, 0.7, 0.9);
}

QColor MaterialSliderHelpers::autoThumbColor(const QColor& trackColor) noexcept {
	auto helpers = MaterialColorHelper();
	double lum = helpers.luminance(trackColor);
	if (lum > 0.5)
		return helpers.harmonizeColor(trackColor, 0.6, 1.0);
	else
		return helpers.harmonizeColor(trackColor, 1.4, 1.0);
}

QColor MaterialSliderHelpers::pressedColor(const QColor& base) noexcept {
	QColor hsl = base.toHsl();
	double l = std::clamp(hsl.lightnessF() * 0.85, 0.0, 1.0);
	double s = std::clamp(hsl.saturationF() * 1.15, 0.0, 1.0);
	return QColor::fromHslF(hsl.hueF(), s, l, base.alphaF());
}

}
