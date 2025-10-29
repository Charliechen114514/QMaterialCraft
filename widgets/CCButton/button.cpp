#include "button.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QEnterEvent>
#include <QPainter>

CCButton::CCButton(QWidget* parentWidget)
    : QPushButton(parentWidget) {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

CCButton::~CCButton() {
}

void CCButton::enterEvent(QEnterEvent* event) {
	paintContext->handleHoverEvent(
	    CCWidgetLibrary::HoverEventType::HOVER_IN, event);
}

void CCButton::leaveEvent(QEvent* event) {
	paintContext->handleHoverEvent(
	    CCWidgetLibrary::HoverEventType::HOVER_OUT, event);
}

void CCButton::mousePressEvent(QMouseEvent* event) {
	paintContext->handleMouseEvent(
	    CCWidgetLibrary::MouseEventType::MOUSE_PRESS, event);
}

void CCButton::mouseReleaseEvent(QMouseEvent* event) {
	paintContext->handleMouseEvent(
	    CCWidgetLibrary::MouseEventType::MOUSE_RELEASE, event);
}

void CCButton::mouseMoveEvent(QMouseEvent* event) {
	return QPushButton::mouseMoveEvent(event);
}

void CCButton::resizeEvent(QResizeEvent* event) {
	paintContext->handleResizeEvent(event);
}

void CCButton::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		return QPushButton::paintEvent(event);
	} else {
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);
		paintContext->paint(painter);
	}
}
