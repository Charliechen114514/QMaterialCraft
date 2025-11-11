#include "materialtablewidgetpaintcontext.h"
#include "themes/material/commons/materialcontainerdefaultpaintcontext.h"
#include <QHeaderView>
namespace CCWidgetLibrary {

MaterialTableWidgetPaintContext::MaterialTableWidgetPaintContext(QTableWidget* tableWidget)
    : TableWidgetPaintContext(tableWidget) {
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	helpers = new MaterialContainerDefaultPaintHelpers(tableWidget);
}

bool MaterialTableWidgetPaintContext::paint(QPainter& p) {
	return helpers->paint(p);
}

void MaterialTableWidgetPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	helpers->handleMouseEvent(type, ev);
}

}
