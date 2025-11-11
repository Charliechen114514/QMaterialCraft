#ifndef TREEWIDGETPAINTCONTEXT_H
#define TREEWIDGETPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QTreeWidget;

namespace CCWidgetLibrary {
class TreeWidgetPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "tree-widget";
	explicit TreeWidgetPaintContext(QTreeWidget* treeWidget = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // TREEWIDGETPAINTCONTEXT_H
