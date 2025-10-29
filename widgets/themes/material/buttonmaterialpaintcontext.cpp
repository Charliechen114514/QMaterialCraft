#include "buttonmaterialpaintcontext.h"
#include "themes/material/material_color_helper.h"
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QVariantAnimation>

namespace CCWidgetLibrary {
ButtonMaterialPaintContext::ButtonMaterialPaintContext(QPushButton* button)
    : PaintContext(button) {
	attached_widget->setMouseTracking(true);
	attached_widget->setAttribute(Qt::WA_Hover, true);
	ripple_animation_helper = new RippleAnimation(attached_widget);
	hover_animation_helper = new HoverColorAnimation(attached_widget);
	shadow_animation_helper = new ShadowOffsetsAnimation(attached_widget);
}

ButtonMaterialPaintContext::~ButtonMaterialPaintContext() {
}

bool ButtonMaterialPaintContext::paint(QPainter& p) {
	p.save();
	auto adjustments = radius / 2;
	qreal current_offset_y = shadow_animation_helper->offsetY();
	QRectF rect = attached_widget->rect().adjusted(
	    adjustments, adjustments + current_offset_y, -adjustments, -adjustments + current_offset_y);

	// body apply
	p.setBrush(hover_animation_helper->get_current_bgColor(backgroundColor_));
	p.drawRoundedRect(rect, radius, radius);

	// ripple apply
	ripple_animation_helper->process_ripple_draw(p, textColor_);

	// test apply
	QPushButton* btn = qobject_cast<QPushButton*>(attached_widget);
	p.setPen(textColor_);
	QFont f = btn->font();
	p.setFont(f);
	p.drawText(rect, Qt::AlignCenter, btn->text());
	p.restore();
	return true;
}

void ButtonMaterialPaintContext::handleMouseEvent(
    const MouseEventType type, QMouseEvent* ev) {
	shadow_animation_helper->process_shadowoffset_action(type);
	ripple_animation_helper->activate_with_mouse_event(type, ev);
}

void ButtonMaterialPaintContext::handleResizeEvent(const QResizeEvent* ev) {
	radius = RADIUS_PERCENTAGE * std::min(attached_widget->width(), attached_widget->height());
}

void ButtonMaterialPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	hover_animation_helper->activate_hover_animation(type);
}

void ButtonMaterialPaintContext::setBackgroundColor(const QColor& c, bool autoContrast) {
	backgroundColor_ = c;
	if (autoContrast) {
		textColor_ = MaterialColorHelper().contrastColorDuplicate(c, 0.7);
	}
	attached_widget->update();
}

void ButtonMaterialPaintContext::setTextColor(const QColor& c, bool autoContrast) {
	textColor_ = c;
	if (autoContrast) {
		backgroundColor_ = MaterialColorHelper().contrastColorDuplicate(c, 0.7);
	}
	attached_widget->update();
}
}
