#ifndef IMAGEWIDGETMATERIALPAINTCONTEXT_H
#define IMAGEWIDGETMATERIALPAINTCONTEXT_H

#include "CCImageWidget/imagewidgetpaintcontext.h"

namespace CCWidgetLibrary {
class RippleAnimation;
class OpacityAnimation;

class ImageWidgetMaterialPaintContext : public ImageWidgetPaintContext {
	static constexpr const short DURATION = 400;

public:
	explicit ImageWidgetMaterialPaintContext(CCImageWidget* attached_parent);

	bool paint(QPainter& p);
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev);
	void setPixmap(const QPixmap& newPixmap);
	bool propertySettings(const QString property, const QVariant value);
	std::optional<QVariant> propertyGet(const QString property);

private:
	QRectF computePixmapTarget(const QSizeF& srcSize, const QSizeF& boxSize) const;

private:
	RippleAnimation* ripple_animation;
	OpacityAnimation* opacity_animation;
	QColor ripple_color { Qt::white };
	QColor colorA { 63, 81, 181 };
	QColor colorB { 92, 107, 192 };
};
}

#endif // IMAGEWIDGETMATERIALPAINTCONTEXT_H
