#ifndef CCCARDACTIONS_H
#define CCCARDACTIONS_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QWidget>
class QHBoxLayout;

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCCardActions : public QWidget {
	Q_OBJECT
public:
	explicit CCCardActions(QWidget* parent = nullptr);
	~CCCardActions() override;
	void installActionWidget(const QString& name, QWidget* widget);
	void removeActionWidget(const QString& name);
	void removeActionWidget(QWidget* widget);

	QWidget* widget(const QString& name);
	void clear();
signals:
	void newWidget(QString name, QWidget* widget);
	void deleteWidget(QString name, QWidget* widget);

private:
	QWidget* container = nullptr;
	QMap<QString, QWidget*> mappings;
};

#endif // CCCARDACTIONS_H
