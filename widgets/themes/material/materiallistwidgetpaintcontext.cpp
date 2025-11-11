#include "materiallistwidgetpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"

namespace CCWidgetLibrary {

MaterialListWidgetPaintContext::MaterialListWidgetPaintContext(
    QListWidget* listWidget)
    : ListWidgetPaintContext(listWidget) {
	helpers = new MaterialContainerDefaultPaintHelpers(listWidget);
}

bool MaterialListWidgetPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialListWidgetPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}

}
