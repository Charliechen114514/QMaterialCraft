#ifndef LABELPAINTCONTEXT_H
#define LABELPAINTCONTEXT_H

#include "TextIndiator.h"
#include <QColor>
#include <paintcontext.h>

namespace CCWidgetLibrary {
class LabelPaintContext : public PaintContext {
public:
	LabelPaintContext(QWidget* attached_widget);
	virtual void setTextStyle(TextStyle style) = 0;

	virtual void setBackgroundColor(const QColor& c);
	virtual void setTextColor(const QColor& c);
	virtual void setPadding(qreal h, qreal v);

	virtual QColor backGroundColor() const;
	virtual QColor textColor() const;
	virtual std::pair<qreal, qreal> padding() const;
};

}
#endif // LABELPAINTCONTEXT_H
