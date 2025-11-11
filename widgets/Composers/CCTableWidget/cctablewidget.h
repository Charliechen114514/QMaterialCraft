#ifndef CCTABLEWIDGET_H
#define CCTABLEWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QTableWidget>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCTableWidget : public QTableWidget {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "table-widget";
	explicit CCTableWidget(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTABLEWIDGET_H
