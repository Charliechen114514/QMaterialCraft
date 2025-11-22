#include "ccmarkdownbrowserwidget.h"
#include "CCMarkdownWidget/cmarkdowncardwidget.h"
#include "button.h"
#include "ccbadgelabel.h"
#include "ccmarkdownbrowserwidget.h"
#include "helpers/commonwidgetsettingshelper.h"
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QStackedWidget>
#include <QTimer>
#include <QToolBar>

namespace {
QVector<QString> splitIntoPages(const QString& md) {
	// Simple parser: split by lines starting with # or ## (H1/H2). Keep the heading with its following content.
	QStringList lines = md.split('\n');
	QVector<QString> pages;
	QString cur;
	auto flush = [&] {
		if (!cur.isEmpty()) {
			pages.append(cur);
			cur.clear();
		} };

	for (int i = 0; i < lines.size(); ++i) {
		const QString& ln = lines.at(i);
		if (ln.startsWith("# ") || ln.startsWith("## ")) {
			// start new page
			flush();
		}
		cur += ln + '\n';
	}
	flush();
	if (pages.isEmpty() && !cur.isEmpty())
		pages.append(cur);
	return pages;
}

QWidget* createCardContainer(const QString& content) {
	QWidget* container = new QWidget();
	QVBoxLayout* lv = new QVBoxLayout(container);
	lv->setContentsMargins(48, 24, 48, 24);
	lv->setSpacing(12);

	CMarkdownCardWidget* card = new CMarkdownCardWidget(content, container);
	card->setObjectName("MarkdownCard");
	card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	lv->addWidget(card);
	container->setLayout(lv);
	return container;
}

void updateCardContainer(QWidget* container, const QString& content) {
	CMarkdownCardWidget* card = container->findChild<CMarkdownCardWidget*>("MarkdownCard");
	if (card) {
		card->setMarkdown(content);
	}
}

}

CCMarkdownBrowserWidget::CCMarkdownBrowserWidget(QWidget* parent)
    : QWidget { parent } {
	editor = new QPlainTextEdit(this);
	editor->setPlaceholderText("Enter Markdown here...");
	editor->setLineWrapMode(QPlainTextEdit::NoWrap);
	editor->setFont(QFont("Noto Sans Mono", 11));

	pagesStack = new QStackedWidget(this);
	pagesStack->setContentsMargins(0, 0, 0, 0);

	auto prevBtn = new CCButton("◀", this);
	auto nextBtn = new CCButton("▶", this);

	pageLabel = new CCBadgeLabel(this);
	pageLabel->setAlignment(Qt::AlignCenter);
	pageLabel->setMinimumWidth(120);

	QHBoxLayout* navLayout = new QHBoxLayout();
	navLayout->addWidget(prevBtn);
	navLayout->addWidget(pageLabel);
	navLayout->addWidget(nextBtn);
	navLayout->setContentsMargins(0, 0, 0, 0);

	QAction* actionSource = new QAction("Source", this);
	QAction* actionCards = new QAction("Cards", this);
	QAction* actionSplit = new QAction("Split", this);

	QToolBar* toolbar = new QToolBar(this);
	toolbar->addAction(actionSource);
	toolbar->addAction(actionCards);
	toolbar->addAction(actionSplit);

	QVBoxLayout* leftLayout = new QVBoxLayout();
	leftLayout->addWidget(editor);
	QWidget* leftPane = new QWidget(this);
	leftPane->setLayout(leftLayout);

	QWidget* rightPane = new QWidget(this);
	QVBoxLayout* rightLayout = new QVBoxLayout(rightPane);
	rightLayout->addWidget(pagesStack);
	rightLayout->addLayout(navLayout);
	rightPane->setLayout(rightLayout);

	splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(leftPane);
	splitter->addWidget(rightPane);
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 1);

	QVBoxLayout* main = new QVBoxLayout(this);
	main->addWidget(toolbar);
	main->addWidget(splitter);
	setLayout(main);

	// Connect actions
	connect(actionSource, &QAction::triggered, this, &CCMarkdownBrowserWidget::showSourceOnly);
	connect(actionCards, &QAction::triggered, this, &CCMarkdownBrowserWidget::showCardsOnly);
	connect(actionSplit, &QAction::triggered, this, &CCMarkdownBrowserWidget::showSplit);

	connect(prevBtn, &QPushButton::clicked, this, &CCMarkdownBrowserWidget::prevPage);
	connect(nextBtn, &QPushButton::clicked, this, &CCMarkdownBrowserWidget::nextPage);
	connect(editor, &QPlainTextEdit::textChanged, this, &CCMarkdownBrowserWidget::scheduleRender);

	renderTimer = new QTimer(this);
	renderTimer->setSingleShot(true);
	renderTimer->setInterval(220);
	connect(renderTimer, &QTimer::timeout, this, &CCMarkdownBrowserWidget::doRender);

	CCWidgetLibrary::WidgetHelpers::setWidgetBackgroundTransparent(pagesStack);
}

void CCMarkdownBrowserWidget::setMarkdown(const QString& markdown) {
	editor->setPlainText(markdown);
}

void CCMarkdownBrowserWidget::showSourceOnly() {
	splitter->widget(0)->show();
	splitter->widget(1)->hide();
}

void CCMarkdownBrowserWidget::showCardsOnly() {
	splitter->widget(0)->hide();
	splitter->widget(1)->show();
}

void CCMarkdownBrowserWidget::showSplit() {
	splitter->widget(0)->show();
	splitter->widget(1)->show();
}

void CCMarkdownBrowserWidget::goToPage(int index) {
	if (index < 0 || index >= pagesStack->count())
		return;
	pagesStack->setCurrentIndex(index);
	updatePageLabel();
}

void CCMarkdownBrowserWidget::prevPage() {
	goToPage(pagesStack->currentIndex() - 1);
}

void CCMarkdownBrowserWidget::nextPage() {
	goToPage(pagesStack->currentIndex() + 1);
}

void CCMarkdownBrowserWidget::scheduleRender() {
	renderTimer->start();
}

void CCMarkdownBrowserWidget::updatePageLabel() {
	if (pagesStack->count() == 0) {
		pageLabel->setText("0 / 0");
		return;
	}
	pageLabel->setText(QString("%1 / %2")
	                       .arg(pagesStack->currentIndex() + 1)
	                       .arg(pagesStack->count()));
}

void CCMarkdownBrowserWidget::doRender() {
	QString md = editor->toPlainText();
	QVector<QString> newPages = splitIntoPages(md);

	int oldCurrentIndex = pagesStack->currentIndex();
	int oldPageCount = pagesStack->count();

	pagesStack->blockSignals(true);

	for (int i = 0; i < newPages.size(); ++i) {
		if (i < oldPageCount) {
			QWidget* container = pagesStack->widget(i);
			updateCardContainer(container, newPages[i]);
		} else {
			QWidget* newContainer = createCardContainer(newPages[i]);
			pagesStack->addWidget(newContainer);
		}
	}

	while (pagesStack->count() > newPages.size()) {
		QWidget* w = pagesStack->widget(pagesStack->count() - 1);
		pagesStack->removeWidget(w);
		w->deleteLater();
	}

	pagesStack->blockSignals(false);

	goToPage(oldCurrentIndex);
	updatePageLabel();
}
