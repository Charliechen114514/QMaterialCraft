#include "materialtoolboxpaintcontext.h"
#include "CCToolButton/cctoolbutton.h"
#include "materialheaderbar.h"
#include <QLayout>
#include <QPainter>
#include <QTimer>
#include <QToolBox>
namespace CCWidgetLibrary {

MaterialToolBoxPaintContext::
    MaterialToolBoxPaintContext(QToolBox* toolbox)
    : ToolBoxPaintContext(toolbox) {
	header_bar = new MaterialHeaderBar(toolbox);
	// some settings
	static constexpr int headerHeight = 48;

	toolbox->setStyleSheet(
	    QString("QToolBox { padding-top: %1px; } "
	            "QToolBox::tab { "
	            "background: transparent; "
	            "border: none; padding: 0px; "
	            "margin: 0px; height: 0px; "
	            "} "
	            "QToolBox::tab:selected { "
	            "height: 0px; "
	            "}")
	        .arg(headerHeight));

	header_bar->setFixedHeight(headerHeight);
	header_bar->raise();

	connect(toolbox, &QToolBox::currentChanged,
	        this, &MaterialToolBoxPaintContext::onCurrentChanged);
}

bool MaterialToolBoxPaintContext::paint(QPainter& p) {
	p.save();
	p.restore();
	return true;
}

bool MaterialToolBoxPaintContext::propertySettings(const QString property, const QVariant value) {
	if (property == "primary-color") {
		auto c = value.value<QColor>();
		if (c.isValid()) {
			setPrimaryColor(c);
			return true;
		}
	}
	return false;
}

std::optional<QVariant>
MaterialToolBoxPaintContext::propertyGet(const QString property) {
	if (property == "primary-color") {
		return { primaryColor() };
	}
	return std::nullopt;
}

void MaterialToolBoxPaintContext::handleResizeEvent(const QResizeEvent* /*ev*/) {
	QWidget* boxWidget = attached_widget;
	header_bar->setFixedWidth(boxWidget->width());
	header_bar->setGeometry(0, 0, boxWidget->width(), header_bar->height());
	header_bar->raise();
}

int MaterialToolBoxPaintContext::addItemAction(
    QWidget* widget, const QString& text) {
	QToolBox* toolbox = dynamic_cast<QToolBox*>(attached_widget);
	int idx = toolbox->QToolBox::addItem(widget, text);
	addHeaderButton(idx, text, QIcon());
	if (toolbox->count() == 1) {
		header_bar->buttonAt(0)->setChecked(true);
		QTimer::singleShot(0, this, [this]() { header_bar->moveIndicatorUnder(header_bar->buttonAt(0), false); });
	}
	return idx;
}

int MaterialToolBoxPaintContext::addItemAction(QWidget* widget, const QIcon& icon, const QString& text) {
	QToolBox* toolbox = dynamic_cast<QToolBox*>(attached_widget);
	int idx = toolbox->QToolBox::addItem(widget, icon, text);
	addHeaderButton(idx, text, icon);
	if (toolbox->count() == 1) {
		header_bar->buttonAt(0)->setChecked(true);
		QTimer::singleShot(0, this, [this]() { header_bar->moveIndicatorUnder(header_bar->buttonAt(0), false); });
	}
	return idx;
}

int MaterialToolBoxPaintContext::insertItemAction(int index, QWidget* widget, const QString& text) {
	QToolBox* toolbox = dynamic_cast<QToolBox*>(attached_widget);
	int idx = toolbox->QToolBox::insertItem(index, widget, text);
	addHeaderButton(idx, text, QIcon());
	return idx;
}

int MaterialToolBoxPaintContext::insertItemAction(
    int index, QWidget* widget,
    const QIcon& icon, const QString& text) {
	QToolBox* toolbox = dynamic_cast<QToolBox*>(attached_widget);
	int idx = toolbox->QToolBox::insertItem(index, widget, icon, text);
	addHeaderButton(idx, text, icon);
	return idx;
}

void MaterialToolBoxPaintContext::removeItemAction(int index) {
	QToolBox* toolbox = dynamic_cast<QToolBox*>(attached_widget);
	toolbox->QToolBox::removeItem(index);
	if (index >= 0 && index < int(buttons.size())) {
		CCToolButton* b = buttons.at(index);
		b->setParent(nullptr);
		b->deleteLater();
		buttons.erase(buttons.begin() + index);
		syncButtons();
	}
}

void MaterialToolBoxPaintContext::setPrimaryColor(const QColor c) {
	IndicatorWidget* indicator = header_bar->indicator_widgets();
	indicator->setPrimaryColor(c);
}

QColor MaterialToolBoxPaintContext::primaryColor() const {
	IndicatorWidget* indicator = header_bar->indicator_widgets();
	return indicator->primaryColor();
}

void MaterialToolBoxPaintContext::onCurrentChanged(int idx) {
	for (int i = 0; i < int(buttons.size()); ++i) {
		buttons.at(i)->setChecked(i == idx);
	}
	if (idx >= 0 && idx < int(buttons.size()))
		header_bar->moveIndicatorUnder(buttons.at(idx), true);
}

void MaterialToolBoxPaintContext::addHeaderButton(int idx, const QString& text, const QIcon& icon) {
	CCToolButton* btn = new CCToolButton(header_bar);
	btn->setText(text);
	btn->setIcon(icon);
	btn->setSizePolicy(
	    QSizePolicy::Expanding,
	    QSizePolicy::Expanding);
	connect(btn, &QToolButton::clicked, this, [this, idx]() { dynamic_cast<QToolBox*>(attached_widget)->setCurrentIndex(idx); });
	header_bar->addButton(btn);
	buttons.insert(buttons.begin() + idx, btn);
	syncButtons();
}

void MaterialToolBoxPaintContext::syncButtons() {
	auto box = dynamic_cast<QToolBox*>(attached_widget);
	for (auto& c : connections)
		disconnect(c);
	connections.clear();

	for (int i = 0; i < buttons.size(); ++i) {
		CCToolButton* b = buttons.at(i);
		if (!b)
			continue;
		auto c = connect(b, &QToolButton::clicked, this,
		                 [this, i, box]() { box->setCurrentIndex(i); });
		connections.push_back(c);

		b->setChecked(i == box->currentIndex());
	}
}
}
