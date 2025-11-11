#include "cctreewidget.h"
#include "Composers/privates/containerpaintcontext.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QMouseEvent>
#include <QPainter>
CCTreeWidget::CCTreeWidget(QWidget* parent)
    : QTreeWidget(parent) {
	ALLOCATE_PAINTCONTEXT();
	dynamic_cast<CCWidgetLibrary::ContainerPaintContext*>(paintContext)->initBaseStyleOptions();
}

void CCTreeWidget::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		QTreeWidget::paintEvent(event);
	} else {
		QPainter painter(this->viewport());
		QTreeWidget::paintEvent(event);
		paintContext->paint(painter);
	}
}

CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(CCTreeWidget, QTreeWidget);
