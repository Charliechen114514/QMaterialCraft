#ifndef CCTREEVIEW_H
#define CCTREEVIEW_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QTreeView>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCTreeView : public QTreeView {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "tree-view";
	explicit CCTreeView(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTREEVIEW_H
