#include "containerpaintcontext.h"
#include "container_delegates_keys.h"
#include "containercommondelegate.h"
#include "paintcontextallocator.h"
#include <QAbstractItemView>
namespace CCWidgetLibrary {

ContainerPaintContext::ContainerPaintContext(QAbstractItemView* attached_widget)
    : PaintContext(attached_widget) {
}

bool ContainerPaintContext::initBaseStyleOptions() {
	auto itemView = as_item_view();
	// install delegates
	install_delegates();
	// common behaviors
	itemView->setMouseTracking(true);
	itemView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
	itemView->setSelectionMode(QAbstractItemView::SingleSelection);
	itemView->setDragEnabled(true);
	itemView->setAcceptDrops(true);
	itemView->setDropIndicatorShown(true);

	return true;
}

void ContainerPaintContext::install_delegates() {
	auto itemView = as_item_view();
	auto delegates = PaintContextAllocator::instance().allocate_delegate(
	    get_delegate_name(), itemView);
	if (!delegates) {
		delegates = PaintContextAllocator::instance().allocate_delegate(FALLBACK_DELEGATE_NAME, itemView);
	}
	itemView->setItemDelegate(delegates);
}

QAbstractItemView* ContainerPaintContext::as_item_view() const {
	return dynamic_cast<QAbstractItemView*>(attached_widget);
}
}
