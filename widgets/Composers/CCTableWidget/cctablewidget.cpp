#include "cctablewidget.h"
#include "Composers/privates/containerpaintcontext.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QMouseEvent>
#include <QPainter>
CCTableWidget::CCTableWidget(QWidget* parent)
    : QTableWidget(parent) {
	ALLOCATE_PAINTCONTEXT();
	dynamic_cast<CCWidgetLibrary::ContainerPaintContext*>(paintContext)->initBaseStyleOptions();
}

void CCTableWidget::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		QTableWidget::paintEvent(event);
	} else {
		QPainter painter(this->viewport());
		QTableWidget::paintEvent(event);
		paintContext->paint(painter);
	}
}

CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(CCTableWidget, QTableWidget);
