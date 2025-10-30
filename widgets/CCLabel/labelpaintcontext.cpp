#include "labelpaintcontext.h"

namespace CCWidgetLibrary {

LabelPaintContext::LabelPaintContext(QWidget* attached_widget)
    : PaintContext(attached_widget) {
}

void LabelPaintContext::setBackgroundColor(const QColor& c) { }

void LabelPaintContext::setTextColor(const QColor& c) { }

void LabelPaintContext::setPadding(qreal h, qreal v) { }

QColor LabelPaintContext::backGroundColor() const {
	return {};
}

QColor LabelPaintContext::textColor() const {
	return {};
}

std::pair<qreal, qreal> LabelPaintContext::padding() const {
	return {};
}
}
