#include "calendarwidgetgallery.h"
#include "CCCalendarWidget/cccalendarwidget.h"
#include <QVBoxLayout>
#include <QWidget>

QWidget* Gallery::createCalendarGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCCalendarWidget* w = new CCCalendarWidget(root);
	v->addWidget(w);

	return root;
}
