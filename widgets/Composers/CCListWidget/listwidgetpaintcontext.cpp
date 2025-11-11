#include "listwidgetpaintcontext.h"
#include <QListWidget>

namespace CCWidgetLibrary {

ListWidgetPaintContext::ListWidgetPaintContext(QListWidget* listWidget)
    : ContainerPaintContext(listWidget) {
}

QString ListWidgetPaintContext::get_delegate_name() const {
	return WIDGET_NAME;
}

}
