#ifndef CCCARDHEADER_H
#define CCCARDHEADER_H
#include "CCWidgets_BuildDefine.h"
#include <QWidget>

class CCLabel;

class CCWIDGET_EXPORT CCCardHeader : public QWidget {
	Q_OBJECT
public:
	explicit CCCardHeader(QWidget* parent = nullptr);

	enum class HeaderRole {
		TITLE,
		SUBTITLE
	};

	void setHeaderRoleWidget(const HeaderRole role, QWidget* widget);
	QWidget* roleWidget(const HeaderRole role) const;

	void resumeNativeWidgets();

signals:
	void roleWidgetChanged(HeaderRole r, QWidget* newWidget);

protected:
	virtual void initNativeWidget();

private:
	CCLabel* nativeTitleWidget;
	CCLabel* nativeSubTitleWidget;
	QMap<HeaderRole, QWidget*> widgets;
};

#endif // CCCARDHEADER_H
