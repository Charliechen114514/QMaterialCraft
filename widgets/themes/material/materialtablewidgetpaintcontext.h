#ifndef MATERIALTABLEWIDGETPAINTCONTEXT_H
#define MATERIALTABLEWIDGETPAINTCONTEXT_H
#include "Composers/CCTableWidget/cctablewidget.h"
#include "Composers/CCTableWidget/tablewidgetpaintcontext.h"

namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialTableWidgetPaintContext : public TableWidgetPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCTableWidget::WIDGET_NAME;
	MaterialTableWidgetPaintContext(QTableWidget* tableWidget = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALTABLEWIDGETPAINTCONTEXT_H
