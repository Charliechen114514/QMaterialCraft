#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QProgressBar>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCProgressBar : public QProgressBar {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "progressbar";
	explicit CCProgressBar(QWidget* parent = nullptr);

	qreal thickness() const;
	void setThickness(qreal t);

	QColor indicatorColor() const;
	void setIndicatorColor(const QColor& c);

	QColor trackColor() const;
	void setTrackColor(const QColor& c);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // PROGRESSBAR_H
