#ifndef MATERIALTABLEVIEWPAINTCONTEXT_H
#define MATERIALTABLEVIEWPAINTCONTEXT_H
#include "Composers/CCTableView/cctableview.h"
#include "Composers/CCTableView/tableviewpaintcontext.h"

namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialTableViewPaintContext : public TableViewPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCTableView::WIDGET_NAME;
	MaterialTableViewPaintContext(QTableView* tableView = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALTABLEVIEWPAINTCONTEXT_H
