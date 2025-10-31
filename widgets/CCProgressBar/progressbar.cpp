#include "progressbar.h"
#include "paintcontextallocator.h"
#include "progressbarpaintcontext.h"
#include <QEnterEvent>
#include <QPainter>

CCProgressBar::CCProgressBar(QWidget* parent)
    : QProgressBar { parent } {
	paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	    WIDGET_NAME, this);
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}
}

qreal CCProgressBar::thickness() const {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	return pbpc->thickness();
}

void CCProgressBar::setThickness(qreal t) {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	pbpc->setThickness(t);
}

QColor CCProgressBar::indicatorColor() const {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	return pbpc->indicatorColor();
}

void CCProgressBar::setIndicatorColor(const QColor& c) {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	pbpc->setIndicatorColor(c);
}

QColor CCProgressBar::trackColor() const {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	return pbpc->trackColor();
}

void CCProgressBar::setTrackColor(const QColor& c) {
	CCWidgetLibrary::ProgressBarPaintContext* pbpc = dynamic_cast<
	    CCWidgetLibrary::ProgressBarPaintContext*>(paintContext);

	pbpc->setTrackColor(c);
}

CONTEXT_HOVER_IMPL(CCProgressBar);
CONTEXT_MOUSE_IMPL(CCProgressBar);
CONTEXT_PAINT_IMPL(CCProgressBar, QProgressBar)
CONTEXT_RESIZE_IMPL(CCProgressBar)
