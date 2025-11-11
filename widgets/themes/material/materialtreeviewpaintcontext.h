#ifndef MATERIALTREEVIEWPAINTCONTEXT_H
#define MATERIALTREEVIEWPAINTCONTEXT_H
#include "Composers/CCTreeView/cctreeview.h"
#include "Composers/CCTreeView/treeviewpaintcontext.h"

namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialTreeViewPaintContext : public TreeViewPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCTreeView::WIDGET_NAME;
	MaterialTreeViewPaintContext(QTreeView* treeView = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALTREEVIEWPAINTCONTEXT_H
