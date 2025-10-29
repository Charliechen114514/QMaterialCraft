#include "sliderpaintcontext.h"
#include <QMouseEvent>
#include <QWidget>

namespace CCWidgetLibrary {
SliderPaintContext::SliderPaintContext(QWidget* attached_widget)
    : PaintContext(attached_widget) {
}

void SliderPaintContext::setPercentage(const float percentage) noexcept {
	if (percentage == process_percentage) {
		return;
	}
	process_percentage = std::clamp(percentage, 0.0f, 1.0f);
	attached_widget->update();
	emit percentage_changed(process_percentage);
}

float SliderPaintContext::mappings_from_mousepoint(const QMouseEvent* ev) {
	return static_cast<float>((ev->pos().x() - start_postion.x())) / (expected_visible_width());
}

float SliderPaintContext::expected_visible_width() const noexcept {
	return WIDTH_PERCENTAGE * attached_widget->width();
}

float SliderPaintContext::expected_visible_height() const noexcept {
	return HEIGHT_PERCENTAGE * attached_widget->height();
}

float SliderPaintContext::percentage() const noexcept {
	return process_percentage;
}

QPoint SliderPaintContext::lefttop_positions() const noexcept {
	return attached_widget->mapFromGlobal(start_postion);
}

void SliderPaintContext::set_lefttop_positions(const QPoint& p) noexcept {
	start_postion = p;
}
}
