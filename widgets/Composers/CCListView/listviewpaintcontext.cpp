#include "listviewpaintcontext.h"
#include <QListView>

namespace CCWidgetLibrary {

ListViewPaintContext::ListViewPaintContext(QListView* listView)
    : ContainerPaintContext(listView) {
}

QString ListViewPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}

}
