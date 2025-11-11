#include "cclistwidget.h"
#include "Composers/privates/containerpaintcontext.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QMouseEvent>
#include <QPainter>
CCListWidget::CCListWidget(QWidget* parent)
    : QListWidget(parent) {
	ALLOCATE_PAINTCONTEXT();
	dynamic_cast<CCWidgetLibrary::ContainerPaintContext*>(paintContext)->initBaseStyleOptions();
}

void CCListWidget::paintEvent(QPaintEvent* event) {
	if (!paintContext) {
		qWarning() << "paintContext NULL, use the default paint";
		QListWidget::paintEvent(event);
	} else {
		QPainter painter(this->viewport());
		QListWidget::paintEvent(event);
		paintContext->paint(painter);
	}
}

CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(CCListWidget, QListWidget);
