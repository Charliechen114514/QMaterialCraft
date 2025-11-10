#ifndef CCLABEL_H
#define CCLABEL_H
#include "CCWidgets_BuildDefine.h"
#include "TextIndiator.h"
#include "context_request_macros.h"
#include <QLabel>
CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCLabel : public QLabel {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "label";
	explicit CCLabel(QWidget* parent = nullptr);
	explicit CCLabel(const QString& text, QWidget* parent = nullptr);
	void setTextStyle(CCWidgetLibrary::TextStyle style);

	virtual void setTextColor(const QColor& c);
	virtual QColor textColor() const;

protected:
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCLABEL_H
