#include "ccimagewidget.h"
#include "imagewidgetpaintcontext.h"
#include "paintcontextallocator.h"
#include <QPainter>
CCImageWidget::ScaleMode CCImageWidget::scale_mode() const {
	return scale_mode_;
}

CONTEXT_MOUSE_IMPL(CCImageWidget);
CONTEXT_PAINT_IMPL(CCImageWidget, QWidget);

CCImageWidget::CCImageWidget(QWidget* parent) {
	ALLOCATE_PAINTCONTEXT();
}

void CCImageWidget::setScale_mode(const ScaleMode& newScale_mode) {
	scale_mode_ = newScale_mode;
}

void CCImageWidget::setPixmap(const QPixmap& pixmap) {
	CCWidgetLibrary::ImageWidgetPaintContext* image_paint_context
	    = dynamic_cast<CCWidgetLibrary::ImageWidgetPaintContext*>(paintContext);

	image_paint_context->setPixmap(pixmap);
}

QPixmap CCImageWidget::pixmap() const {
	CCWidgetLibrary::ImageWidgetPaintContext* image_paint_context
	    = dynamic_cast<CCWidgetLibrary::ImageWidgetPaintContext*>(paintContext);

	return image_paint_context->pixmap();
}
