#include "tableviewpaintcontext.h"
#include <QTableView>

namespace CCWidgetLibrary {

TableViewPaintContext::TableViewPaintContext(QTableView* tableView)
    : ContainerPaintContext(tableView) {
}

QString TableViewPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}

}
