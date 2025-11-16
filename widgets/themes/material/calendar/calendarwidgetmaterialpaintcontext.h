#ifndef CALENDARWIDGETMATERIALPAINTCONTEXT_H
#define CALENDARWIDGETMATERIALPAINTCONTEXT_H
#include "CCCalendarWidget/calendarwidgetpaintcontext.h"
#include "helpers/animations/opacityanimation.h"
#include <QColor>

namespace CCWidgetLibrary {
class MaterialCalendarWidgetPaintContext : public CalendarWidgetPaintContext {
public:
	MaterialCalendarWidgetPaintContext(QCalendarWidget* w);
	bool paint(QPainter& p) override;
	// Accessors
	QColor accentColor() const;
	void setAccentColor(const QColor& c);

	int cornerRadius() const;
	void setCornerRadius(int r);
	void paintCell(QPainter* painter, const QRect& rect, const QDate& date) override;

private:
	QCalendarWidget* calendar;
	OpacityAnimation* holder;
	QColor accentColor_ { 0, 150, 136 };
	int cornerRadius_ { 8 };
};
}

#endif // CALENDARWIDGETMATERIALPAINTCONTEXT_H
