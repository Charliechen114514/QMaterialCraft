#ifndef CCCARDCONTENT_H
#define CCCARDCONTENT_H
#include "CCWidgets_BuildDefine.h"
#include "TextIndiator.h"
#include "helpers/widgetlayouthelper.h"
#include <QWidget>

class QLabel;

class CCWIDGET_EXPORT CCCardContent : public QWidget {
	Q_OBJECT
public:
	explicit CCCardContent(QWidget* parent = nullptr);
	void setContentTitle(const QString& title,
	                     CCWidgetLibrary::TextStyle style = CCWidgetLibrary::TextStyle::TitleMedium);
	void setContentTitleVisible(bool visible);
	bool contentTitleVisible() const;

	QWidget* getContentWidget() const;
	void setContentWidget(QWidget* newContentWidget);

signals:
	void contentWidgetChanged(QWidget* w);

private:
	WidgetLayoutHelper* helpers;
	QWidget* contentWidget;
	QLabel* contextLabel;
};

#endif // CCCARDCONTENT_H
