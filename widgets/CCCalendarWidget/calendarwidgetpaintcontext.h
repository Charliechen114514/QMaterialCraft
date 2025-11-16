#ifndef CALENDARWIDGETPAINTCONTEXT_H
#define CALENDARWIDGETPAINTCONTEXT_H

#include <paintcontext.h>
class QCalendarWidget;
namespace CCWidgetLibrary {
class CalendarWidgetPaintContext : public PaintContext {
public:
	CalendarWidgetPaintContext(QCalendarWidget* cal);
	virtual void paintCell(QPainter* painter,
	                       const QRect& rect, const QDate& date)
	    = 0;
};

}

#endif // CALENDARWIDGETPAINTCONTEXT_H
