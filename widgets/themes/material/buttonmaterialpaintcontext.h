#ifndef BUTTONMATERIALPAINTCONTEXT_H
#define BUTTONMATERIALPAINTCONTEXT_H

#include "animation_wrapper/hoveranimationhelper.h"
#include "animation_wrapper/shadowoffsetsanimationhelper.h"
#include "button.h"
#include "buttonpaintcontext.h"
#include "paintcontext.h"
#include "themes/material/MaterialThemeMarker.h"
#include "themes/material/animation_wrapper/rippleanimation.h"
#include <QColor>
#include <QPoint>

class QPushButton;

namespace CCWidgetLibrary {
class ButtonMaterialPaintContext : public ButtonPaintContext,
                                   public MaterialThemeMarker {
	Q_OBJECT

	static constexpr const unsigned int BKCOLOR = 0x6200EE;
	static constexpr const float RADIUS_PERCENTAGE = 0.1;

public:
	static constexpr const char* BUTTON_NAME = CCButton::WIDGET_NAME;
	ButtonMaterialPaintContext(QPushButton* attached_widget = nullptr);
	~ButtonMaterialPaintContext();

	bool paint(QPainter& p) override;
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev) override;
	void handleResizeEvent(const QResizeEvent* ev) override;
	void handleHoverEvent(const HoverEventType type, QEvent* ev) override;

	void setBackgroundColor(const QColor& c, bool autoContrast = false) override;
	void setTextColor(const QColor& c, bool autoContrast = false) override;

	bool propertySettings(const QString property, const QVariant value) override;
	std::optional<QVariant> propertyGet(const QString property) override;

	void setBorderColor(const QColor& c) override;
	void setBorderWidth(qreal w) override;

private:
	void applyTickedSession(QPainter& p);
	void drawIconAndText(QPainter& p);

private:
	HoverColorAnimation* hover_animation_helper;
	ShadowOffsetsAnimation* shadow_animation_helper;
	RippleAnimation* ripple_animation_helper;

	qreal radius = 0.0;

	QPointF pressPosition;

	QColor backgroundColor_ { BKCOLOR };
	QColor textColor_ { Qt::white };

	QColor borderColor_ = Qt::transparent;
	qreal borderWidth_ = 0.0;
};
}

#endif // BUTTONMATERIALPAINTCONTEXT_H
