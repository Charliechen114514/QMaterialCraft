#ifndef CCLISTVIEW_H
#define CCLISTVIEW_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QListView>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCListView : public QListView {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "list-view";
	explicit CCListView(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCLISTVIEW_H
