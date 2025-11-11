#include "treewidgetpaintcontext.h"
#include <QTreeWidget>

namespace CCWidgetLibrary {

TreeWidgetPaintContext::TreeWidgetPaintContext(QTreeWidget* treeWidget)
    : ContainerPaintContext(treeWidget) {
}

QString TreeWidgetPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}
}
