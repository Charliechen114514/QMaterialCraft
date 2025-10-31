#include "widgetlayouthelper.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
WidgetLayoutHelper::WidgetLayoutHelper(QWidget* parent)
    : QObject { parent } {
	attachedWidget = parent;
	connect(this, &WidgetLayoutHelper::directionChanged,
	        this, &WidgetLayoutHelper::adjustLayouts);
	adjustLayouts();
}

WidgetLayoutHelper::LayoutDirection WidgetLayoutHelper::getDirection() const {
	return direction;
}

void WidgetLayoutHelper::setDirection(LayoutDirection newDirection) {
	if (direction == newDirection)
		return;
	direction = newDirection;
	emit directionChanged(direction);
}

QLayout* WidgetLayoutHelper::layout() const {
	return holdingLayout;
}

void WidgetLayoutHelper::adjustLayouts() {
	QWidgetList tempWidgets_;
	if (attachedWidget->layout()) {
		QLayout* old = attachedWidget->layout();
		while (QLayoutItem* item = old->takeAt(0)) {
			if (item->widget()) {
				item->widget()->setParent(nullptr);
				tempWidgets_.push_back(item->widget());
			}
			delete item;
		}
		delete old;
	}

	QBoxLayout* newLayout = nullptr;
	if (direction == LayoutDirection::Vertical)
		newLayout = new QVBoxLayout(attachedWidget);
	else
		newLayout = new QHBoxLayout(attachedWidget);

	newLayout->setContentsMargins(16, 8, 16, 8);
	newLayout->setSpacing(2);

	for (auto* w : tempWidgets_)
		newLayout->addWidget(w);

	attachedWidget->setLayout(newLayout);
	holdingLayout = newLayout;
}
