#ifndef MATERIALTREEWIDGETPAINTCONTEXT_H
#define MATERIALTREEWIDGETPAINTCONTEXT_H
#include "Composers/CCTreeWidget/cctreewidget.h"
#include "Composers/CCTreeWidget/treewidgetpaintcontext.h"
namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialTreeWidgetPaintContext : public TreeWidgetPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCTreeWidget::WIDGET_NAME;
	MaterialTreeWidgetPaintContext(QTreeWidget* treeWidget = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALTREEWIDGETPAINTCONTEXT_H
