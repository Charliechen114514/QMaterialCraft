#include "ccimagewidget.h"
#include "imagewidgetpaintcontext.h"
#include "paintcontextallocator.h"
#include "property_string.h"
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
	update();
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

void CCImageWidget::setEmptyImage(const BlankColor& color) {
	paintContext->propertySettings(CCWidgetLibrary::CCImageWidget::COLORA, color.colorA);
	paintContext->propertySettings(CCWidgetLibrary::CCImageWidget::COLORB, color.colorB);
}

CCImageWidget::BlankColor CCImageWidget::emptyWhenColor() const {
	BlankColor c;
	c.colorA = paintContext->propertyGet(
	                           CCWidgetLibrary::CCImageWidget::COLORA)
	               .value()
	               .value<QColor>();
	c.colorB = paintContext->propertyGet(
	                           CCWidgetLibrary::CCImageWidget::COLORB)
	               .value()
	               .value<QColor>();
	return c;
}
