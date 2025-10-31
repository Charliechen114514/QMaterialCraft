#include "cclabel.h"
#include "labelpaintcontext.h"
#include "paintcontextallocator.h"
#include <QEnterEvent>
#include <QPainter>

CCLabel::CCLabel(QWidget* parent)
    : QLabel { parent } {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

void CCLabel::setTextStyle(CCWidgetLibrary::TextStyle style) {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	label_context->setTextStyle(style);
}

void CCLabel::setTextColor(const QColor& c) {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	label_context->setTextColor(c);
}

QColor CCLabel::textColor() const {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	return label_context->textColor();
}

void CCLabel::enterEvent(QEnterEvent* event) {
	paintContext->handleHoverEvent(CCWidgetLibrary::HoverEventType::HOVER_IN, event);
	QLabel::enterEvent(event);
}

void CCLabel::leaveEvent(QEvent* event) {
	paintContext->handleHoverEvent(CCWidgetLibrary::HoverEventType::HOVER_OUT, event);
	QLabel::leaveEvent(event);
}

void CCLabel::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		return QLabel::paintEvent(event);
	} else {
		QPainter painter(this);
		paintContext->paint(painter);
	}
}
