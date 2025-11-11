#ifndef LISTWIDGETPAINTCONTEXT_H
#define LISTWIDGETPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QListWidget;

namespace CCWidgetLibrary {
class ListWidgetPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "list-widget";
	explicit ListWidgetPaintContext(QListWidget* listWidget = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // LISTWIDGETPAINTCONTEXT_H
