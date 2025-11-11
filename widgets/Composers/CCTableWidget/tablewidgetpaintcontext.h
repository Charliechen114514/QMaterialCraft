#ifndef TABLEWIDGETPAINTCONTEXT_H
#define TABLEWIDGETPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QTableWidget;

namespace CCWidgetLibrary {
class TableWidgetPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "table-widget";
	explicit TableWidgetPaintContext(QTableWidget* tableWidget = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // TABLEWIDGETPAINTCONTEXT_H
