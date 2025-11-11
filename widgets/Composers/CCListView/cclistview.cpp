#include "cclistview.h"
#include "Composers/privates/containerpaintcontext.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QMouseEvent>
#include <QPainter>
CCListView::CCListView(QWidget* parent)
    : QListView(parent) {
	ALLOCATE_PAINTCONTEXT();
	dynamic_cast<CCWidgetLibrary::ContainerPaintContext*>(paintContext)->initBaseStyleOptions();
}

void CCListView::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		QListView::paintEvent(event);
	} else {
		QPainter painter(this->viewport());
		QListView::paintEvent(event);
		paintContext->paint(painter);
	}
}

CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(CCListView, QListView);
