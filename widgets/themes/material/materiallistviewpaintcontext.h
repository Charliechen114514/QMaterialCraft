#ifndef MATERIALLISTVIEWPAINTCONTEXT_H
#define MATERIALLISTVIEWPAINTCONTEXT_H
#include "Composers/CCListView/cclistview.h"
#include "Composers/CCListView/listviewpaintcontext.h"

namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialListViewPaintContext : public ListViewPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCListView::WIDGET_NAME;
	MaterialListViewPaintContext(QListView* listView = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALLISTVIEWPAINTCONTEXT_H
