#include "imagewidgetpaintcontext.h"
#include "ccimagewidget.h"
namespace CCWidgetLibrary {

ImageWidgetPaintContext::ImageWidgetPaintContext(
    CCImageWidget* attached_parent)
    : PaintContext(attached_parent) {
}

QPixmap ImageWidgetPaintContext::pixmap() const {
	return pixmap_;
}

void ImageWidgetPaintContext::setPixmap(const QPixmap& newPixmap) {
	pixmap_ = newPixmap;
}
}
