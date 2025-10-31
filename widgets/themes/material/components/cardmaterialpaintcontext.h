#ifndef CARDMATERIALPAINTCONTEXT_H
#define CARDMATERIALPAINTCONTEXT_H
#include "../MaterialThemeMarker.h"
#include "../animation_wrapper/floativeanimation.h"
#include "../animation_wrapper/shadowoffsetsanimationhelper.h"
#include "paintcontext.h"
#include "privates/cccard_components_name.h"
namespace CCWidgetLibrary {
class CardMaterialPaintContext : public PaintContext,
                                           public MaterialThemeMarker {
public:
	static constexpr const char* WIDGET_NAME = Card::WIDGET_NAME;
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
	QColor backgroundColor_ = QColor { 255, 255, 255, 130 };
	QColor borderColor_ = QColor { 0, 0, 0, 40 };
	qreal borderWidth_ = 2.0;
};
}

#endif // CARDMATERIALPAINTCONTEXT_H
