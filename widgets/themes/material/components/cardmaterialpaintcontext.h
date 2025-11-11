#ifndef CARDMATERIALPAINTCONTEXT_H
#define CARDMATERIALPAINTCONTEXT_H
#include "../MaterialThemeMarker.h"
#include "helpers/animations/floativeanimation.h"
#include "helpers/animations/shadowoffsetsanimationhelper.h"
#include "paintcontext.h"
namespace CCWidgetLibrary {
class CardMaterialPaintContext : public PaintContext,
                                           public MaterialThemeMarker {
public:
	CardMaterialPaintContext(QWidget* attached_parent);

	bool paint(QPainter& p) override;
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev) override;
	void handleHoverEvent(const HoverEventType type, QEvent* ev) override;

	QColor backgroundColor() const;
	void setBackgroundColor(const QColor& newBackgroundColor);

	QColor borderColor() const;
	void setBorderColor(const QColor& newBorderColor);
	qreal borderWidth() const;
	void setBorderWidth(qreal newBorderWidth);

private:
	void act_each_child(QWidget* w);

private:
	FloativeAnimation* floats;
	ShadowOffsetsAnimation* shadows;
	QColor backgroundColor_ = QColor { Qt::gray };
	QColor borderColor_ = QColor { 0, 0, 0, 40 };
	qreal borderWidth_ = 2.0;
};
}

#endif // CARDMATERIALPAINTCONTEXT_H
