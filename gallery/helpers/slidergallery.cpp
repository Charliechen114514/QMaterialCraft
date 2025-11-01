#include "slidergallery.h"
#include "slider.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
QWidget* Gallery::createSliderGalleryWidgets(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCSlider* card = new CCSlider(root);
	v->addWidget(card);
	card->setMinimumHeight(40);
	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* cardGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(cardGallery);
	mainLayout->addWidget(sc);

	return cardGallery;
}
