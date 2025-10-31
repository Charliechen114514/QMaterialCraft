#include "cardgallery.h"
#include "CCProgressBar/progressbar.h"
#include "button.h"
#include "ccbadgelabel.h"
#include "cccard.h"
#include "cclabel.h"
#include "privates/cccardactions.h"
#include "privates/cccardcontent.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

namespace {

void setHeader(QWidget* header) {
	if (!header) {
		qWarning() << "Card header NULL";
		return;
	}

	CCLabel* native_label = qobject_cast<CCLabel*>(header);
	if (!native_label) {
		qWarning() << "Not target native header!";
		return;
	}

	native_label->setText("Handle QMaterial Craft Project");
}

void setSubTitle(QWidget* header) {
	if (!header) {
		qWarning() << "Card header NULL";
		return;
	}

	CCBadgeLabel* native_label = qobject_cast<CCBadgeLabel*>(header);
	if (!native_label) {
		qWarning() << "Not target native header!";
		return;
	}

	native_label->setText("Card Widgets Priority");
}

void configAction(CCCard* card) {
	CCCardActions* action = card->actions();

	CCBadgeLabel* indicator = new CCBadgeLabel(action);
	indicator->setText("Progress: ");
	action->installActionWidget("progress_label", indicator);
	CCProgressBar* bar = new CCProgressBar(action);
	bar->setIndicatorColor(Qt::cyan);
	bar->setValue(70);
	action->installActionWidget("progress", bar);

	CCButton* button = new CCButton(action);
	button->setText("Cancle");
	button->setMinimumHeight(48);
	button->setBackGroundColor(Qt::darkRed);
	action->installActionWidget("cancle", button);

	CCButton* button2 = new CCButton(action);
	button2->setText("Finish");
	button2->setMinimumHeight(48);
	button2->setBackGroundColor(Qt::darkGreen);
	action->installActionWidget("Finish", button2);
}

void configContent(CCCard* card) {
	CCCardContent* content = card->content();
	QWidget* listWidget = new QWidget(content);
	auto v = new QVBoxLayout(listWidget);
	listWidget->setLayout(v);
	QStringList tasks;
	tasks << "* KNEEL Daddy!" << "* Consider Abstractions of CCCards";
	for (const auto& each : std::as_const(tasks)) {
		CCLabel* tmp = new CCLabel(listWidget);
		tmp->setText(each);
		v->addWidget(tmp);
	}

	content->setContentWidget(listWidget);
	content->setContentTitle("Expected Todo Today!!!");
	return;
}

}

QWidget* Gallery::createCardGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCCard* card = new CCCard(root);
	v->addWidget(card);

	card->applyHeaders(setHeader);
	card->applySubHeaders(setSubTitle);
	configContent(card);
	configAction(card);

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* cardGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(cardGallery);
	mainLayout->addWidget(sc);

	return cardGallery;
}
