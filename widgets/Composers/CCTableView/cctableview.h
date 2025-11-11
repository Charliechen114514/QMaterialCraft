#ifndef CCTABLEVIEW_H
#define CCTABLEVIEW_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QTableView>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCTableView : public QTableView {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "table-view";
	explicit CCTableView(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTABLEVIEW_H
