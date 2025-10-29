#include "paintcontext.h"
#include <QWidget>
namespace CCWidgetLibrary {

PaintContext::PaintContext(QWidget* attached_widget)
    : QObject(attached_widget)
    , attached_widget(attached_widget) { }

void PaintContext::handleMouseEvent(
    const MouseEventType, QMouseEvent*) {
}

void PaintContext::handleResizeEvent(const QResizeEvent* ev) { }

void PaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) { }

bool PaintContext::checkContextAvalible() {
	return attached_widget != nullptr; // Not Null
}
}
