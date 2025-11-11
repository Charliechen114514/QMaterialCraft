#ifndef MATERIALLISTWIDGETPAINTCONTEXT_H
#define MATERIALLISTWIDGETPAINTCONTEXT_H
#include "Composers/CCListWidget/cclistwidget.h"
#include "Composers/CCListWidget/listwidgetpaintcontext.h"

namespace CCWidgetLibrary {

class MaterialContainerDefaultPaintHelpers;

class MaterialListWidgetPaintContext : public ListWidgetPaintContext {
public:
	static constexpr const char* WIDGET_NAME = CCListWidget::WIDGET_NAME;
	MaterialListWidgetPaintContext(QListWidget* listWidget = nullptr);
	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);

private:
	MaterialContainerDefaultPaintHelpers* helpers;
};
}

#endif // MATERIALLISTWIDGETPAINTCONTEXT_H
