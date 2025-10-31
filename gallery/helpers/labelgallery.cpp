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
	label->setText("CCLabel");
	v->addWidget(label);

	CCBadgeLabel* badge_label = new CCBadgeLabel(root);
	badge_label->setText("CCBadgeLabel AlignedLeft");
	badge_label->setPadding(100, 64);
	v->addWidget(badge_label);

	CCBadgeLabel* badge_label2 = new CCBadgeLabel(root);
	badge_label2->setText("CCBadgeLabel! AlignedCenter");
	badge_label2->setPadding(100, 64);
	badge_label2->setAlignment(Qt::AlignCenter);
	v->addWidget(badge_label2);

	CCBadgeLabel* badge_label3 = new CCBadgeLabel(root);
	badge_label3->setText("CCBadgeLabel! AlignedRight");
	badge_label3->setPadding(100, 64);
	badge_label3->setAlignment(Qt::AlignRight);
	v->addWidget(badge_label3);

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* labelGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(labelGallery);
	mainLayout->addWidget(sc);

	return labelGallery;
}
