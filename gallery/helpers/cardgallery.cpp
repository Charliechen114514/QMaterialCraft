#include "cardgallery.h"
#include "cccard.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

QWidget* Gallery::createCardGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* cardGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(cardGallery);
	mainLayout->addWidget(sc);

	return cardGallery;
}
