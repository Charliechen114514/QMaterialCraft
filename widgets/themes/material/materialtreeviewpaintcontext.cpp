#include "materialtreeviewpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"
#include <QHeaderView>
namespace CCWidgetLibrary {

MaterialTreeViewPaintContext::MaterialTreeViewPaintContext(
    QTreeView* treeView)
    : TreeViewPaintContext(treeView) {
	treeView->setAnimated(true);
	treeView->header()->setStretchLastSection(true);
	helpers = new MaterialContainerDefaultPaintHelpers(treeView);
}

bool MaterialTreeViewPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialTreeViewPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}

}
