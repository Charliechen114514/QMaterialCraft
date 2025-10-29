#ifndef BUTTON_H
#define BUTTON_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QPushButton>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCButton : public QPushButton {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "button";
	explicit CCButton(QWidget* parentWidget = nullptr);
	~CCButton();

protected:
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // BUTTON_H
