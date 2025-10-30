#ifndef CCBADGELABEL_H
#define CCBADGELABEL_H
#include "cclabel.h"

class CCWIDGET_EXPORT CCBadgeLabel : public CCLabel {
public:
	static constexpr const char* WIDGET_NAME = "badge-label";
	explicit CCBadgeLabel(QWidget* parent = nullptr);
	QSize sizeHint() const override;

	void setBackgroundColor(const QColor& c);
	void setPadding(qreal h, qreal v);

	QColor backGroundColor() const;
	std::pair<qreal, qreal> padding() const;

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCBADGELABEL_H
