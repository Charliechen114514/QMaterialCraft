#include "appearanimation.h"
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QPointer>
#include <QPropertyAnimation>
#include <QWidget>

namespace {
QGraphicsOpacityEffect* ensureOpacityEffect(QWidget* w, bool setInitial) {
	if (!w)
		return nullptr;
	auto* effect = qobject_cast<QGraphicsOpacityEffect*>(w->graphicsEffect());
	if (!effect) {
		effect = new QGraphicsOpacityEffect(w);
		w->setGraphicsEffect(effect);
	}
	return effect;
}
}

namespace CCWidgetLibrary::animation {

AppearAnimation::AppearAnimation(QWidget* parent)
    : QObject { parent } {
	widget = parent;
	if (!widget) {
		throw std::invalid_argument("Widget can not be null!");
	}
	QWidget* parentWidget = widget->parentWidget();
	if (!parentWidget) {
		parentWidget = widget->window();
		if (!parentWidget) {
			qWarning() << "AppearAnimation: cannot find parent or window to attach container.";
			return;
		}
	}
	container = new QWidget(parentWidget);
	container->setAttribute(Qt::WA_TranslucentBackground);
	container->setWindowFlags(Qt::FramelessWindowHint);
	QGraphicsOpacityEffect* eff = ensureOpacityEffect(container, true);

	animation_group = new QParallelAnimationGroup(this);
	position_animation = new QPropertyAnimation(container, "pos");
	opacity_animation = new QPropertyAnimation(eff, "opacity");
	animation_group->addAnimation(position_animation);
	animation_group->addAnimation(opacity_animation);

	connect(animation_group, &QParallelAnimationGroup::finished,
	        this, &AppearAnimation::finished);
}

void AppearAnimation::apply_config(const AnimationConfig& config) {
	apply_settings(position_animation, config);
	apply_settings(opacity_animation, config);
}

QPoint AppearAnimation::getStartPos() const {
	return startPos;
}

void AppearAnimation::setStartPos(QPoint newStartPos) {
	startPos = newStartPos;
}

QPoint AppearAnimation::getEndPos() const {
	return endPos;
}

void AppearAnimation::setEndPos(QPoint newEndPos) {
	endPos = newEndPos;
}

qreal AppearAnimation::getAppear_opacity() const {
	return appear_opacity;
}

void AppearAnimation::setAppear_opacity(qreal newAppear_opacity) {
	appear_opacity = newAppear_opacity;
}

qreal AppearAnimation::getDisappear_opacity() const {
	return disappear_opacity;
}

void AppearAnimation::setDisappear_opacity(qreal newDisappear_opacity) {
	disappear_opacity = newDisappear_opacity;
}

void AppearAnimation::appear() {
	if (!widget)
		return;

	if (animation_group->state() == QAbstractAnimation::Running) {
		animation_group->stop();
	}

	QWidget* oldParent = widget->parentWidget();
	QSize widgetSize = widget->size();
	container->resize(widgetSize);

	QPoint containerStartPos = startPos;
	container->move(containerStartPos);
	container->show();
	container->raise();

	widget->setParent(container);
	widget->move(0, 0);
	widget->show();

	position_animation->setStartValue(startPos);
	position_animation->setEndValue(endPos);
	opacity_animation->setStartValue(disappear_opacity);
	opacity_animation->setEndValue(appear_opacity);

	connect(animation_group, &QParallelAnimationGroup::finished, this, [=]() {
		QPointer<QWidget> wptr(widget); // safety
		QWidget* restoreParent = (container ? container->parentWidget() : oldParent);
		if (restoreParent) {
			wptr->setParent(restoreParent);
			QPoint finalPos = endPos;
			wptr->move(finalPos);
			wptr->show();
			wptr->raise();
		} else {
			wptr->setParent(oldParent);
			wptr->move(endPos);
			wptr->show();
			wptr->raise();
		}
		
		emit finished(); }, Qt::SingleShotConnection);

	animation_group->start();
}

void AppearAnimation::disappear(bool hide) {
	if (!widget)
		return;

	if (animation_group->state() == QAbstractAnimation::Running) {
		animation_group->stop();
	}

	QWidget* oldParent = widget->parentWidget();
	QSize widgetSize = widget->size();
	container->resize(widgetSize);

	QPoint containerStartPos = startPos;
	container->move(containerStartPos);
	container->show();
	container->raise();

	widget->setParent(container);
	widget->move(0, 0);
	widget->show();

	position_animation->setStartValue(endPos);
	position_animation->setEndValue(startPos);
	opacity_animation->setStartValue(appear_opacity);
	opacity_animation->setEndValue(disappear_opacity);

	connect(animation_group, &QParallelAnimationGroup::finished, this, [=]() {
		QPointer<QWidget> wptr(widget); // safety
		QWidget* restoreParent = (container ? container->parentWidget() : oldParent);
		if (restoreParent) {
			wptr->setParent(restoreParent);
			QPoint finalPos = startPos;
			wptr->move(finalPos);
			if (hide)
				wptr->hide();
		} else {
			wptr->setParent(oldParent);
			wptr->move(startPos);
			if (hide)
				wptr->hide();
		}
		
		emit finished(); }, Qt::SingleShotConnection);

	animation_group->start();
}
}
