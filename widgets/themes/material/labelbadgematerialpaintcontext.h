#ifndef LABELBADGEMATERIALPAINTCONTEXT_H
#define LABELBADGEMATERIALPAINTCONTEXT_H

#include "ccbadgelabel.h"
#include <QColor>
#include <labelpaintcontext.h>
namespace CCWidgetLibrary {
class LabelBadgeMaterialPaintContext : public LabelPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCBadgeLabel::WIDGET_NAME;
	LabelBadgeMaterialPaintContext(QWidget* attached_parent);
	bool paint(QPainter& p) override;
	void setTextStyle(TextStyle style) override;

	QSize sizeHint() const override;

	void setBackgroundColor(const QColor& c) override;
	void setTextColor(const QColor& c) override;
	void setPadding(qreal h, qreal v) override;

	QColor backGroundColor() const override;
	QColor textColor() const override;
	std::pair<qreal, qreal> padding() const override;

private:
	QColor bg_color_ { 0xE91E63 };
	QColor text_color_ { Qt::white };
	qreal padding_h_;
	qreal padding_v_;
	TextStyle style_ = TextStyle::BodyMedium;
};
}

#endif // LABELBADGEMATERIALPAINTCONTEXT_H
