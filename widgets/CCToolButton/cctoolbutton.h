#ifndef CCTOOLBUTTON_H
#define CCTOOLBUTTON_H

#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QToolButton>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCToolButton : public QToolButton {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "tool-button";
	explicit CCToolButton(QWidget* parent = nullptr);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTOOLBUTTON_H
