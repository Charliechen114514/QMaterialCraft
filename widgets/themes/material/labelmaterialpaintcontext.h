#ifndef LABELMATERIALPAINTCONTEXT_H
#define LABELMATERIALPAINTCONTEXT_H
#include "CCLabel/cclabel.h"
#include "MaterialThemeMarker.h"
#include "TextIndiator.h"
#include "labelpaintcontext.h"
#include <QColor>
namespace CCWidgetLibrary {
class OpacityAnimation;

class LabelMaterialPaintContext : public LabelPaintContext,
                                  public MaterialThemeMarker {
public:
	static constexpr const char* LABEL_NAME = CCLabel::WIDGET_NAME;
	LabelMaterialPaintContext(QWidget* attached_widget);
	bool paint(QPainter& p) override;
	void handleHoverEvent(const HoverEventType type, QEvent* ev) override;

	void setTextStyle(TextStyle style) override;

	void setTextColor(const QColor& color) override;
	QColor textColor() const override { return color_; }

private:
	TextStyle style_ = TextStyle::BodyMedium;
	QColor color_;
	OpacityAnimation* opacity_animation;
};
}

#endif // LABELMATERIALPAINTCONTEXT_H
