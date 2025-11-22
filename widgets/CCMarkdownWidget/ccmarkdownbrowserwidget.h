#ifndef CCMARKDOWNBROWSERWIDGET_H
#define CCMARKDOWNBROWSERWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include <QWidget>
class QStackedWidget;
class QSplitter;
class CCBadgeLabel;
class QPlainTextEdit;

class CCWIDGET_EXPORT CCMarkdownBrowserWidget : public QWidget {
	Q_OBJECT
public:
	explicit CCMarkdownBrowserWidget(QWidget* parent = nullptr);
	void setMarkdown(const QString& markdown);

public slots:
	void showSourceOnly();
	void showCardsOnly();
	void showSplit();

	void goToPage(int index);

	void prevPage();
	void nextPage();

private slots:
	void updatePageLabel();
	void scheduleRender();
	void doRender();

private:
	QPlainTextEdit* editor;
	QStackedWidget* pagesStack;
	QSplitter* splitter;
	CCBadgeLabel* pageLabel;
	QTimer* renderTimer;
};

#endif // CCMARKDOWNBROWSERWIDGET_H
