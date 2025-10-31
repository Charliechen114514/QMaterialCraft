#include "slider.h"
#include "paintcontextallocator.h"
#include <QPainter>
#include <QPropertyAnimation>
CCSlider::CCSlider(QWidget* parent)
    : QSlider { parent } {
	setOrientation(Qt::Horizontal);
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

CCSlider::~CCSlider() {
}

void CCSlider::resizeEvent(QResizeEvent* event) {
	paintContext->handleResizeEvent(event);
}

void CCSlider::mousePressEvent(QMouseEvent* event) {
	using MouseEventType = CCWidgetLibrary::MouseEventType;
	isPressed = true;
	paintContext->handleMouseEvent(MouseEventType::MOUSE_PRESS, event);
}

void CCSlider::mouseReleaseEvent(QMouseEvent* event) {
	using MouseEventType = CCWidgetLibrary::MouseEventType;
	isPressed = false;
	paintContext->handleMouseEvent(MouseEventType::MOUSE_RELEASE, event);
}

void CCSlider::mouseMoveEvent(QMouseEvent* event) {
	using MouseEventType = CCWidgetLibrary::MouseEventType;
	if (!isPressed)
		return;
	paintContext->handleMouseEvent(MouseEventType::MOUSE_MOVE, event);
}

void CCSlider::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		return QSlider::paintEvent(event);
	} else {
		QPainter painter(this);
		paintContext->paint(painter);
	}
}
