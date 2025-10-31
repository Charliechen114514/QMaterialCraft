#include "cccardactions.h"
#include <QEnterEvent>
#include <QHBoxLayout>
#include <QPainter>
#include <QScrollArea>

CCCardActions::CCCardActions(QWidget* parent)
    : QWidget { parent } {
	container = new QWidget(this);
	QScrollArea* scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(container);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setStyleSheet("background: transparent");
	QHBoxLayout* hLayout = new QHBoxLayout(container);
	hLayout->setContentsMargins(16, 8, 16, 8);
	container->setLayout(hLayout);
	hLayout->setAlignment(Qt::AlignCenter);
	auto suml = new QHBoxLayout(this);
	suml->setContentsMargins(0, 0, 0, 0);
	suml->addWidget(scrollArea);
	setLayout(suml);
}

CCCardActions::~CCCardActions() {
	clear();
}

void CCCardActions::installActionWidget(const QString& name, QWidget* widget) {
	if (!widget)
		return;

	QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(container->layout());

	if (mappings.contains(name)) {
		QWidget* old = mappings.value(name);
		if (old) {
			hLayout->removeWidget(old);
		}
		mappings.remove(name);
	}

	widget->setParent(container);
	int count = hLayout->count();
	if (count == 0) {
		hLayout->addStretch();
		hLayout->addWidget(widget);
		hLayout->addStretch();
	} else {
		hLayout->insertWidget(count - 1, widget);
	}

	mappings.insert(name, widget);
	emit newWidget(name, widget);
}

void CCCardActions::removeActionWidget(const QString& name) {
	if (!mappings.contains(name))
		return;
	QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(container->layout());

	QWidget* w = mappings.take(name);
	if (!w)
		return;

	hLayout->removeWidget(w);
	w->hide();
	emit deleteWidget(name, w);
}

void CCCardActions::removeActionWidget(QWidget* widget) {
	if (!widget)
		return;
	QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(container->layout());

	QString keyToRemove;
	for (auto it = mappings.cbegin(); it != mappings.cend(); ++it) {
		if (it.value() == widget) {
			keyToRemove = it.key();
			break;
		}
	}

	if (!keyToRemove.isEmpty()) {
		mappings.remove(keyToRemove);
	}

	hLayout->removeWidget(widget);
	widget->hide();
	emit deleteWidget(keyToRemove, widget);
}

QWidget* CCCardActions::widget(const QString& name) {
	return mappings.value(name, nullptr);
}

void CCCardActions::clear() {
	QHBoxLayout* hLayout = qobject_cast<QHBoxLayout*>(container->layout());

	for (auto w : std::as_const(mappings)) {
		if (w) {
			hLayout->removeWidget(w);
			w->hide();
		}
	}
	mappings.clear();
}
