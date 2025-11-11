#ifndef LISTVIEWPAINTCONTEXT_H
#define LISTVIEWPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QListView;

namespace CCWidgetLibrary {
class ListViewPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "list-view";
	explicit ListViewPaintContext(QListView* listView = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // LISTVIEWPAINTCONTEXT_H
