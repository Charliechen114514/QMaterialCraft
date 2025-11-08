#ifndef IMAGEWIDGETMATERIALPAINTCONTEXT_H
#define IMAGEWIDGETMATERIALPAINTCONTEXT_H

#include "CCImageWidget/ccimagewidget.h"
#include "CCImageWidget/imagewidgetpaintcontext.h"

namespace CCWidgetLibrary {
class RippleAnimation;
class OpacityAnimation;

class ImageWidgetMaterialPaintContext : public ImageWidgetPaintContext {
	static constexpr const short DURATION = 400;

public:
	static constexpr const char* WIDGET_NAME = CCImageWidget::WIDGET_NAME;
	explicit ImageWidgetMaterialPaintContext(CCImageWidget* attached_parent);

	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);
	void setPixmap(const QPixmap& newPixmap);

private:
	QRectF computePixmapTarget(const QSizeF& srcSize, const QSizeF& boxSize) const;

private:
	RippleAnimation* ripple_animation;
	OpacityAnimation* opacity_animation;
	QColor ripple_color { Qt::white };
};
}

#endif // IMAGEWIDGETMATERIALPAINTCONTEXT_H
