#ifndef TABLEVIEWPAINTCONTEXT_H
#define TABLEVIEWPAINTCONTEXT_H

#include "Composers/privates/containerpaintcontext.h"

class QTableView;

namespace CCWidgetLibrary {
class TableViewPaintContext : public ContainerPaintContext {
public:
	static constexpr const char* WIDGET_NAME = "table-view";
	explicit TableViewPaintContext(QTableView* tableView = nullptr);
	virtual QString get_delegate_name() const override;
};
}

#endif // TABLEVIEWPAINTCONTEXT_H
