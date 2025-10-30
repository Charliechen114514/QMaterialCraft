#include "ccbadgelabel.h"
#include "labelpaintcontext.h"
#include "paintcontextallocator.h"
#include <QPainter>

CCBadgeLabel::CCBadgeLabel(QWidget* parent)
    : CCLabel(parent) {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

QSize CCBadgeLabel::sizeHint() const {
	return paintContext->sizeHint();
}

void CCBadgeLabel::setBackgroundColor(const QColor& c) {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	label_context->setBackgroundColor(c);
}

void CCBadgeLabel::setPadding(qreal h, qreal v) {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	label_context->setPadding(h, v);
}

QColor CCBadgeLabel::backGroundColor() const {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	return label_context->backGroundColor();
}

std::pair<qreal, qreal> CCBadgeLabel::padding() const {
	auto label_context = dynamic_cast<CCWidgetLibrary::LabelPaintContext*>(paintContext);
	return label_context->padding();
}

void CCBadgeLabel::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		return CCLabel::paintEvent(event); // call QLabel event as requests
	} else {
		QPainter painter(this);
		paintContext->paint(painter);
	}
}
