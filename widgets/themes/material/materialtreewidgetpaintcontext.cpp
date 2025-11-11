#include "materialtreewidgetpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"
#include <QHeaderView>
namespace CCWidgetLibrary {

MaterialTreeWidgetPaintContext::MaterialTreeWidgetPaintContext(
    QTreeWidget* treeWidget)
    : TreeWidgetPaintContext(treeWidget) {
	treeWidget->setAnimated(true);
	treeWidget->header()->setStretchLastSection(true);
	helpers = new MaterialContainerDefaultPaintHelpers(treeWidget);
}

bool MaterialTreeWidgetPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialTreeWidgetPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}
}
