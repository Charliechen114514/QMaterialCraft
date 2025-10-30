#include "labelgallery.h"
#include "ccbadgelabel.h"
#include "cclabel.h"
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>

QWidget* Gallery::createLabelGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCLabel* label = new CCLabel(root);
	label->setText("Hello world");
	v->addWidget(label);

	CCBadgeLabel* badge_label = new CCBadgeLabel(root);
	badge_label->setText("Hello World!");
	v->addWidget(badge_label);

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* cardGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(cardGallery);
	mainLayout->addWidget(sc);

	return cardGallery;
}
