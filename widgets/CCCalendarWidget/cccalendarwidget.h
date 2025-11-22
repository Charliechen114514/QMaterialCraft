#ifndef CCCALENDARWIDGET_H
#define CCCALENDARWIDGET_H

#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QCalendarWidget>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCCalendarWidget : public QCalendarWidget {
public:
	static constexpr const char* WIDGET_NAME = "calendar-widget";
	explicit CCCalendarWidget(QWidget* parent = nullptr);

protected:
	void paintCell(QPainter* painter, const QRect& rect, QDate date) const override;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCCALENDARWIDGET_H
