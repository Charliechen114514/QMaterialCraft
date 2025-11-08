#ifndef IMAGEWIDGETPAINTCONTEXT_H
#define IMAGEWIDGETPAINTCONTEXT_H
#include "paintcontext.h"
#include <QPixmap>

class CCImageWidget;

namespace CCWidgetLibrary {
class ImageWidgetPaintContext : public PaintContext {
public:
	explicit ImageWidgetPaintContext(CCImageWidget* attached_parent);

	QPixmap pixmap() const;
	virtual void setPixmap(const QPixmap& newPixmap);

protected:
	QPixmap pixmap_;
};
}

#endif // IMAGEWIDGETPAINTCONTEXT_H
