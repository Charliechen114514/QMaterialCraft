#include "materiallistviewpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"

namespace CCWidgetLibrary {

MaterialListViewPaintContext::
    MaterialListViewPaintContext(QListView* listView)
    : ListViewPaintContext(listView) {
	helpers = new MaterialContainerDefaultPaintHelpers(listView);
}

bool MaterialListViewPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialListViewPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}

}
