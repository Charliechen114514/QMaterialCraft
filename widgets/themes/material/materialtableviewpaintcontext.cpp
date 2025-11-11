#include "materialtableviewpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"
#include <QHeaderView>

namespace CCWidgetLibrary {

MaterialTableViewPaintContext::MaterialTableViewPaintContext(
    QTableView* tableView)
    : TableViewPaintContext(tableView) {
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	helpers = new MaterialContainerDefaultPaintHelpers(tableView);
}

bool MaterialTableViewPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialTableViewPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}

}
