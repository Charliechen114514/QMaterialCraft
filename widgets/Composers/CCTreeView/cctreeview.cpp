#include "cctreeview.h"
#include "Composers/privates/containerpaintcontext.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QMouseEvent>
#include <QPainter>
CCTreeView::CCTreeView(QWidget* parent)
    : QTreeView(parent) {
	ALLOCATE_PAINTCONTEXT();
	dynamic_cast<CCWidgetLibrary::ContainerPaintContext*>(paintContext)->initBaseStyleOptions();
}

void CCTreeView::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		QTreeView::paintEvent(event);
	} else {
		QPainter painter(this->viewport());
		QTreeView::paintEvent(event);
		paintContext->paint(painter);
	}
}

CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(CCTreeView, QTreeView);
