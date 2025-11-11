#ifndef TREEVIEWPAINTCONTEXT_H
#define TREEVIEWPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QTreeView;

namespace CCWidgetLibrary {
class TreeViewPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "tree-view";
	explicit TreeViewPaintContext(QTreeView* treeView = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // TREEVIEWPAINTCONTEXT_H
