#include "button.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include "property_string.h"
#include "themes/material/buttonmaterialpaintcontext.h"
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

CCButton::CCButton(const QString& text, QWidget* parentWidget)
    : QPushButton(text, parentWidget) {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

CCButton::CCButton(const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent) {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

CCButton::~CCButton() {
}

void CCButton::setTextColor(const QColor baseColor, bool autoContrast) {
	auto btn_context = dynamic_cast<CCWidgetLibrary::ButtonPaintContext*>(paintContext);
	if (!btn_context) {
		return; // Not valid
	}

	btn_context->setTextColor(baseColor, autoContrast);
}

void CCButton::setBackGroundColor(const QColor baseColor, bool autoContrast) {
	auto btn_context = dynamic_cast<CCWidgetLibrary::ButtonPaintContext*>(paintContext);
	if (!btn_context) {
		return; // Not valid
	}

	btn_context->setBackgroundColor(baseColor, autoContrast);
}

void CCButton::setBorderWidth(qreal width) {
	auto btn_context = dynamic_cast<CCWidgetLibrary::ButtonPaintContext*>(paintContext);
	if (!btn_context) {
		return; // Not valid
	}
	btn_context->setBorderWidth(width);
}

void CCButton::setBorderColor(const QColor& color) {
	auto btn_context = dynamic_cast<CCWidgetLibrary::ButtonPaintContext*>(paintContext);
	if (!btn_context) {
		return; // Not valid
	}
	btn_context->setBorderColor(color);
}

bool CCButton::setStyle(const char* style_type) {
	return paintContext->propertySettings(CCWidgetLibrary::Commons::STYLE,
	                                      style_type);
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
	QPushButton::mousePressEvent(event);
}

void CCButton::mouseReleaseEvent(QMouseEvent* event) {
	paintContext->handleMouseEvent(
	    CCWidgetLibrary::MouseEventType::MOUSE_RELEASE, event);
	QPushButton::mouseReleaseEvent(event);
}

void CCButton::mouseMoveEvent(QMouseEvent* event) {
	return QPushButton::mouseMoveEvent(event);
}

void CCButton::resizeEvent(QResizeEvent* event) {
	paintContext->handleResizeEvent(event);
	QPushButton::resizeEvent(event);
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
