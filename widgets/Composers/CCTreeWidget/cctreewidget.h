#ifndef CCTREEWIDGET_H
#define CCTREEWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QTreeWidget>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCTreeWidget : public QTreeWidget {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "tree-widget";
	explicit CCTreeWidget(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTREEWIDGET_H
