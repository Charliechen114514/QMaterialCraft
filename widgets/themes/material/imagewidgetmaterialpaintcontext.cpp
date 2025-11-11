#include "imagewidgetmaterialpaintcontext.h"
#include "CCImageWidget/ccimagewidget.h"
#include "MaterialPropertyString.h"
#include "helpers/animations/opacityanimation.h"
#include "helpers/animations/rippleanimation.h"
#include <QPainter>
#include <QPainterPath>
namespace CCWidgetLibrary {

ImageWidgetMaterialPaintContext::ImageWidgetMaterialPaintContext(
    class CCImageWidget* attached_parent)
    : ImageWidgetPaintContext(attached_parent) {
	ripple_animation = new RippleAnimation(attached_parent);
	opacity_animation = new OpacityAnimation(attached_parent);

	opacity_animation->setMinOpacity(0);
	opacity_animation->setMaxOpacity(1);

	ripple_animation->setMaxOpacity(0.2);

	opacity_animation->applyConfigs([this](AnimationHelper::SettingsConfig& conf) {
		conf.curve = QEasingCurve::InOutCubic;
		conf.period_time = DURATION;
	});
	ripple_animation->applyConfigs([this](AnimationHelper::SettingsConfig& conf) {
		conf.curve = QEasingCurve::OutCubic;
		conf.period_time = DURATION * 6;
	});
}

bool ImageWidgetMaterialPaintContext::paint(QPainter& p) {
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	p.setRenderHint(QPainter::SmoothPixmapTransform);

	const int radius = 12;
	QRectF r = attached_widget->rect().adjusted(0, 0, -1, -1);

	QColor surface = attached_widget->palette().color(QPalette::Window);
	p.fillRect(r, surface);

	QPainterPath path;
	QLinearGradient gradient(attached_widget->rect().topLeft(),
	                         attached_widget->rect().bottomRight());
	gradient.setColorAt(0.0, colorA); // Material Blue 500
	gradient.setColorAt(1.0, colorB); // Material Indigo 400
	path.addRoundedRect(r, radius, radius);
	p.fillPath(path, gradient);

	if (!pixmap_.isNull()) {
		QRectF target = computePixmapTarget(pixmap_.size(), r.size());
		target.moveCenter(r.center());
		p.save();
		QPainterPath clipPath;
		clipPath.addRoundedRect(r, radius, radius);
		p.setClipPath(clipPath);

		p.setOpacity(opacity_animation->opacity());
		p.drawPixmap(target.toRect(), pixmap_);
		p.restore();
	}

	ripple_animation->process_ripple_draw(p, ripple_color);

	p.setPen(QPen(QColor(0, 0, 0, 18), 1));
	p.drawRoundedRect(r, radius, radius);

	p.restore();
	return true;
}

QRectF ImageWidgetMaterialPaintContext::computePixmapTarget(const QSizeF& srcSize, const QSizeF& boxSize) const {
	if (srcSize.isEmpty() || boxSize.isEmpty())
		return QRectF(QPointF(0, 0), boxSize);

	qreal sw = srcSize.width();
	qreal sh = srcSize.height();
	qreal bw = boxSize.width();
	qreal bh = boxSize.height();
	::CCImageWidget* widget = dynamic_cast<::CCImageWidget*>(attached_widget);
	auto mode = widget->scale_mode();
	if (mode == ::CCImageWidget::ScaleMode::Stretch)
		return QRectF(0, 0, bw, bh);

	const qreal sx = bw / sw;
	const qreal sy = bh / sh;
	const qreal scale = (mode == ::CCImageWidget::ScaleMode::Cover) ? qMax(sx, sy) : qMin(sx, sy);
	const qreal w = sw * scale;
	const qreal h = sh * scale;
	return QRectF(0, 0, w, h);
}

void ImageWidgetMaterialPaintContext::handleMouseEvent(
    const MouseEventType type, QMouseEvent* ev) {
	const qreal width = attached_widget->width();
	const qreal height = attached_widget->height();
	qreal maxRadius = sqrt(width * width + height * height) / 1.4;
	ripple_animation->activate(type, ev, maxRadius);
}

void ImageWidgetMaterialPaintContext::setPixmap(const QPixmap& newPixmap) {
	if (newPixmap.isNull())
		return;
	opacity_animation->activate_as_fadeIn();
	attached_widget->update();
	ImageWidgetPaintContext::setPixmap(newPixmap);
	pixmap_.setDevicePixelRatio(attached_widget->window()->devicePixelRatio());
}

bool ImageWidgetMaterialPaintContext::propertySettings(const QString property, const QVariant value) {
	using namespace CCWidgetLibrary::MaterialProperty::ImageWidget;
	if (property == StyleColor::COLORA) {
		QColor color = value.value<QColor>();
		if (!color.isValid()) {
			return false;
		}
		colorA = color;
		attached_widget->update();
		return true;
	} else if (property == StyleColor::COLORB) {
		QColor color = value.value<QColor>();
		if (!color.isValid()) {
			return false;
		}
		colorB = color;
		attached_widget->update();
		return true;
	}
	return false;
}

std::optional<QVariant>
ImageWidgetMaterialPaintContext::propertyGet(const QString property) {
	using namespace CCWidgetLibrary::MaterialProperty::ImageWidget;
	if (property == StyleColor::COLORA) {
		return { colorA };
	} else if (property == StyleColor::COLORB) {
		return { colorB };
	}
	return std::nullopt;
}
}
