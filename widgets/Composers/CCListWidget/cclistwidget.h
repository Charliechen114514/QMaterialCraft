#ifndef CCLISTWIDGET_H
#define CCLISTWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QListWidget>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCListWidget : public QListWidget {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "list-widget";
	explicit CCListWidget(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCLISTWIDGET_H
