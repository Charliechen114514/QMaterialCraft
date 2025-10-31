#include "cardmaterialpaintcontext.h"
#include <QPainter>
#include <QWidget>
namespace CCWidgetLibrary {

CardMaterialPaintContext::
    CardMaterialPaintContext(QWidget* attached_parent)
    : PaintContext(attached_parent) {
	floats = new FloativeAnimation(attached_parent);
	shadows = new ShadowOffsetsAnimation(attached_parent);
}

bool CardMaterialPaintContext::paint(QPainter& p) {
	p.save();
	p.setRenderHint(QPainter::Antialiasing, true);
	QRectF rect = attached_widget->rect();
	if (borderWidth_ > 0.0) {
		qreal halfPen = borderWidth_ / 2.0;
		rect = rect.adjusted(halfPen, halfPen, -halfPen, -halfPen);
	}
	floats->translate_for_none_clip(p, rect);
	shadows->translate_for_none_clip(p, rect);
	QPen pen;
	if (borderWidth_ > 0.0) {
		pen = QPen(borderColor_, borderWidth_);
		pen.setJoinStyle(Qt::RoundJoin);
		pen.setCapStyle(Qt::RoundCap);
	} else {
		pen = Qt::NoPen;
	}
	p.setBrush(backgroundColor_);
	qreal radius = 0.3f * std::min(rect.width(), rect.height());

	p.setPen(pen);
	p.drawRoundedRect(rect, radius, radius);

	p.restore();
	return true;
}

void CardMaterialPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	shadows->process_shadowoffset_action(type);
}

void CardMaterialPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	floats->activete_with_hover(type);
}

QColor CardMaterialPaintContext::backgroundColor() const {
	return backgroundColor_;
}

void CardMaterialPaintContext::setBackgroundColor(const QColor& newBackgroundColor) {
	backgroundColor_ = newBackgroundColor;
}

QColor CardMaterialPaintContext::borderColor() const {
	return borderColor_;
}

void CardMaterialPaintContext::setBorderColor(const QColor& newBorderColor) {
	borderColor_ = newBorderColor;
}

qreal CardMaterialPaintContext::borderWidth() const {
	return borderWidth_;
}

void CardMaterialPaintContext::setBorderWidth(qreal newBorderWidth) {
	borderWidth_ = newBorderWidth;
}
}
