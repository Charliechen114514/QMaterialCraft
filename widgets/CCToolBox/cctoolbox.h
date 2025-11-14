#ifndef CCTOOLBOX_H
#define CCTOOLBOX_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QToolBox>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCToolBox : public QToolBox {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "tool-box";
	explicit CCToolBox(QWidget* parent = nullptr);
	int addItem(QWidget* widget, const QString& text);
	int addItem(QWidget* widget, const QIcon& icon, const QString& text);

	int insertItem(
	    int index, QWidget* widget, const QString& text);
	int insertItem(
	    int index, QWidget* widget,
	    const QIcon& icon, const QString& text);

	void removeItem(int index);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCTOOLBOX_H
