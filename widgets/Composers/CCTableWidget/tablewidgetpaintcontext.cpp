#include "tablewidgetpaintcontext.h"
#include <QTableWidget>

namespace CCWidgetLibrary {

TableWidgetPaintContext::TableWidgetPaintContext(QTableWidget* tableWidget)
    : ContainerPaintContext(tableWidget) {
}

QString TableWidgetPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}

}
