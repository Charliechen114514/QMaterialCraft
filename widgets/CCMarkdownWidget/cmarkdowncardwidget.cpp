#include "cmarkdowncardwidget.h"
#include "helpers/widgetlayouthelper.h"
#include "privates/markdownhighlighter.h"
#include <QTextBrowser>
#include <QVBoxLayout>

CMarkdownCardWidget::CMarkdownCardWidget(QWidget* parent)
    : QWidget { parent } {
	QVBoxLayout* l = new QVBoxLayout(this);
	l->setContentsMargins(18, 18, 18, 18);
	l->setSpacing(12);

	browser = new QTextBrowser(this);
	browser->setOpenExternalLinks(true);
	browser->setReadOnly(true);
	browser->setFrameShape(QFrame::NoFrame);
	browser->setContextMenuPolicy(Qt::DefaultContextMenu);
	browser->document()->setDefaultFont(QFont("Noto Sans", 11));

	auto highlighter = new CCWidgetLibrary::MarkdownHighLighter(browser->document());

	l->addWidget(browser);
	setLayout(l);

	// card look
	setAttribute(Qt::WA_StyledBackground);
	setStyleSheet(R"(
QWidget { background: transparent; }
QTextBrowser { background: transparent; }
)");
}

CMarkdownCardWidget::CMarkdownCardWidget(
    const QString& markdown, QWidget* parent)
    : CMarkdownCardWidget { parent } {
	setMarkdown(markdown);
}

void CMarkdownCardWidget::setMarkdown(const QString& md) {
	// QTextBrowser has setMarkdown in Qt6
	browser->setMarkdown(md);
}

QString CMarkdownCardWidget::markdown() const {
	return browser->toMarkdown();
}

QString CMarkdownCardWidget::toHtml() const {
	return browser->toHtml();
}
