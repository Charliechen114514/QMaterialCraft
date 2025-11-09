#include "appearanimationgallery.h"
#include "button.h"
#include "helpers/animations/appearanimation.h"
#include <QHBoxLayout>
#include <QWidget>

QWidget* Gallery::createAppearAnimationGalleryWidgets(QWidget* parent) {
	using namespace CCWidgetLibrary::animation;
	QWidget* root = new QWidget(parent);

	auto* h = new QHBoxLayout(root);
	h->setSpacing(16);
	h->setContentsMargins(16, 16, 16, 16);

	QWidget* canvas = new QWidget(root);
	canvas->setMinimumSize(500, 500);
	h->addWidget(canvas);

	CCButton* animate_widget = new CCButton(canvas);
	animate_widget->setFixedSize(50, 50);
	animate_widget->move(50, 50);

	AppearAnimation* appear_animation = new AppearAnimation(animate_widget);
	appear_animation->apply_config({ QEasingCurve::OutCubic, 600 });

	appear_animation->setStartPos(QPoint(50, 50));
	appear_animation->setEndPos(QPoint(200, 450));

	QVBoxLayout* v = new QVBoxLayout;

	CCButton* appear_button = new CCButton(root);
	appear_button->setText("Appear");
	v->addWidget(appear_button);
	QObject::connect(appear_button, &QPushButton::clicked,
	                 appear_animation, &AppearAnimation::appear);

	CCButton* disappear_button = new CCButton(root);
	disappear_button->setText("Disappear");
	v->addWidget(disappear_button);
	QObject::connect(disappear_button, &QPushButton::clicked,
	                 appear_animation, &AppearAnimation::disappear);

	h->addLayout(v);

	return root;
}
