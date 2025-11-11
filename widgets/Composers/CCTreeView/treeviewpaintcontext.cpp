#include "treeviewpaintcontext.h"
#include <QTreeView>

namespace CCWidgetLibrary {

TreeViewPaintContext::TreeViewPaintContext(QTreeView* treeView)
    : ContainerPaintContext(treeView) {
}

QString TreeViewPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}

}
