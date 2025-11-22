#ifndef CMARKDOWNCARDWIDGET_H
#define CMARKDOWNCARDWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include <QWidget>
class QTextBrowser;

class CCWIDGET_EXPORT CMarkdownCardWidget : public QWidget {
	Q_OBJECT
public:
	explicit CMarkdownCardWidget(QWidget* parent = nullptr);
	explicit CMarkdownCardWidget(const QString& markdown, QWidget* parent = nullptr);
	void setMarkdown(const QString& md);
	QString markdown() const;
	QString toHtml() const;

private:
	QTextBrowser* browser;
};

#endif // CMARKDOWNCARDWIDGET_H
