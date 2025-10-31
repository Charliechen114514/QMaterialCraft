#include "progressbargallery.h"
#include "button.h"
#include "progressbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

QWidget* Gallery::createProgressBarGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCProgressBar* progress_bar = new CCProgressBar(root);
	progress_bar->setMinimum(0);
	progress_bar->setMaximum(100);
	progress_bar->setValue(50);
	progress_bar->setMinimumHeight(60);

	v->addWidget(progress_bar);

	QWidget* buttons_container = new QWidget(root);
	auto* button_control = new QHBoxLayout(buttons_container);
	v->addWidget(buttons_container);

	CCButton* minus_progress = new CCButton(buttons_container);
	minus_progress->setMinimumHeight(60);
	minus_progress->setText("-");
	button_control->addWidget(minus_progress);
	QObject::connect(minus_progress, &QPushButton::clicked,
	                 progress_bar, [=]() {
		                 progress_bar->setValue(progress_bar->value() - 5);
	                 });

	CCButton* add_progress = new CCButton(buttons_container);
	add_progress->setMinimumHeight(60);
	add_progress->setText("+");
	button_control->addWidget(add_progress);
	QObject::connect(add_progress, &QPushButton::clicked,
	                 progress_bar, [=]() {
		                 progress_bar->setValue(progress_bar->value() + 5);
	                 });

	return root;
}
