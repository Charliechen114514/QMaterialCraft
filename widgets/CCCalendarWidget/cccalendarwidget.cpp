#include "cccalendarwidget.h"
#include "CCCalendarWidget/calendarwidgetpaintcontext.h"
#include "paintcontextallocator.h"
#include <QPainter>

CONTEXT_PAINT_IMPL_WITH_OLD(CCCalendarWidget, QCalendarWidget);

CCCalendarWidget::CCCalendarWidget(QWidget* parent)
    : QCalendarWidget { parent } {
	ALLOCATE_PAINTCONTEXT();
}

void CCCalendarWidget::paintCell(QPainter* painter, const QRect& rect, QDate date) const {
	dynamic_cast<CCWidgetLibrary::CalendarWidgetPaintContext*>(paintContext)->paintCell(painter, rect, date);
}
