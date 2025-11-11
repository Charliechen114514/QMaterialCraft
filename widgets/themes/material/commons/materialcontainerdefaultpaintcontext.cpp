#include "materialcontainerdefaultpaintcontext.h"
#include <QAbstractItemView>
#include <QMouseEvent>
#include <QPainter>

namespace CCWidgetLibrary {
MaterialContainerDefaultPaintHelpers::
    MaterialContainerDefaultPaintHelpers(QAbstractItemView* binded_view) {
	this->binded_view = binded_view;
	ripple_animations = new RippleAnimation(binded_view);
}

bool MaterialContainerDefaultPaintHelpers::paint(QPainter& p) {
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	QColor rippleColor = binded_view->palette().highlight().color();
	ripple_animations->process_ripple_draw(p, rippleColor);
	p.restore();
	return true;
}

void MaterialContainerDefaultPaintHelpers::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	switch (type) {
	case MouseEventType::MOUSE_PRESS: {
		QModelIndex idx = binded_view->indexAt(ev->pos());
		if (idx.isValid()) {
			ripple_animations->activate_with_mouse_event(type, ev);
		}
	} break;
	case MouseEventType::MOUSE_MOVE:
		break;
	case MouseEventType::MOUSE_RELEASE:
		break;
	}
}
}
