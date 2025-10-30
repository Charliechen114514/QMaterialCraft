#include "buttonmaterialpaintcontext.h"
#include "themes/material/material_color_helper.h"
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QVariantAnimation>

namespace CCWidgetLibrary {
ButtonMaterialPaintContext::ButtonMaterialPaintContext(QPushButton* button)
    : ButtonPaintContext(button) {
	attached_widget->setMouseTracking(true);
	attached_widget->setAttribute(Qt::WA_Hover, true);
	ripple_animation_helper = new RippleAnimation(attached_widget);
	hover_animation_helper = new HoverColorAnimation(attached_widget);
	shadow_animation_helper = new ShadowOffsetsAnimation(attached_widget);

	QPushButton* btn = qobject_cast<QPushButton*>(attached_widget);
	if (btn) {
		connect(btn, &QAbstractButton::toggled, attached_widget, [this](bool) {
			attached_widget->update();
		});
	}
}

ButtonMaterialPaintContext::~ButtonMaterialPaintContext() {
}

bool ButtonMaterialPaintContext::paint(QPainter& p) {
	p.save();
	auto adjustments = radius / 2;
	qreal current_offset_y = shadow_animation_helper->offsetY();
	QRectF rect = attached_widget->rect().adjusted(
	    adjustments, adjustments + current_offset_y, -adjustments, -adjustments + current_offset_y);

	if (borderWidth_ > 0.0) {
		qreal halfPen = borderWidth_ / 2.0;
		rect = rect.adjusted(halfPen, halfPen, -halfPen, -halfPen);
	}

	QPen pen;
	if (borderWidth_ > 0.0) {
		pen = QPen(borderColor_, borderWidth_);
		pen.setJoinStyle(Qt::RoundJoin);
		pen.setCapStyle(Qt::RoundCap);
	} else {
		pen = Qt::NoPen;
	}

	// body apply
	p.setPen(pen);

	QColor current_shell_hover_color = attached_widget->isEnabled() ? hover_animation_helper->get_current_bgColor(backgroundColor_) : backgroundColor_;
	p.setBrush(current_shell_hover_color);
	p.drawRoundedRect(rect, radius, radius);

	// ripple apply
	ripple_animation_helper->process_ripple_draw(p, textColor_);

	// test apply
	QPushButton* btn = qobject_cast<QPushButton*>(attached_widget);

	if (btn->isCheckable() && btn->isChecked()) {
		applyTickedSession(p);
	}

	drawIconAndText(p);

	p.restore();
	return true;
}

void ButtonMaterialPaintContext::handleMouseEvent(
    const MouseEventType type, QMouseEvent* ev) {
	shadow_animation_helper->process_shadowoffset_action(type);
	ripple_animation_helper->activate_with_mouse_event(type, ev);
}

void ButtonMaterialPaintContext::handleResizeEvent(const QResizeEvent* ev) {
	radius = RADIUS_PERCENTAGE * std::min(attached_widget->width(), attached_widget->height());
}

void ButtonMaterialPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	hover_animation_helper->activate_hover_animation(type);
}

void ButtonMaterialPaintContext::setBackgroundColor(const QColor& c, bool autoContrast) {
	backgroundColor_ = c;
	if (autoContrast) {
		textColor_ = MaterialColorHelper().contrastColorDuplicate(c, 0.7);
	}
	attached_widget->update();
}

void ButtonMaterialPaintContext::setTextColor(const QColor& c, bool autoContrast) {
	textColor_ = c;
	if (autoContrast) {
		backgroundColor_ = MaterialColorHelper().contrastColorDuplicate(c, 0.7);
	}
	attached_widget->update();
}

void ButtonMaterialPaintContext::setBorderColor(const QColor& c) {
	borderColor_ = c;
	attached_widget->update();
}

void ButtonMaterialPaintContext::setBorderWidth(qreal w) {
	borderWidth_ = std::max<qreal>(0.0, w);
	attached_widget->update();
}

void ButtonMaterialPaintContext::applyTickedSession(QPainter& p) {
	const auto adjustments = radius / 2;
	const qreal current_offset_y = shadow_animation_helper->offsetY();
	const QRectF rect = attached_widget->rect().adjusted(
	    adjustments, adjustments + current_offset_y, -adjustments, -adjustments + current_offset_y);

	const qreal dotSize = std::min<qreal>(rect.height() * 0.52, 20.0);
	const qreal leftMargin = std::max<qreal>(8.0, rect.height() * 0.12);
	QRectF dotRect(rect.left() + leftMargin,
	               rect.center().y() - dotSize * 0.5,
	               dotSize, dotSize);

	// find the circle color and tick color
	QColor dotFill = textColor_;
	if (dotFill.lightness() > 200) {
		dotFill = dotFill.darker(180);
	}
	QColor checkColor = (dotFill.lightness() > 128) ? QColor(0, 0, 0) : QColor(255, 255, 255);

	// draw dot
	p.setBrush(dotFill);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.drawEllipse(dotRect);

	// draw ticks
	QPainterPath checkPath;
	QPointF p1(dotRect.left() + dotRect.width() * 0.22, dotRect.top() + dotRect.height() * 0.52);
	QPointF p2(dotRect.left() + dotRect.width() * 0.45, dotRect.bottom() - dotRect.height() * 0.20);
	QPointF p3(dotRect.right() - dotRect.width() * 0.20, dotRect.top() + dotRect.height() * 0.28);
	checkPath.moveTo(p1);
	checkPath.lineTo(p2);
	checkPath.lineTo(p3);

	QPen checkPen(checkColor, std::max<qreal>(2.0, dotRect.width() * 0.12), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	p.setPen(checkPen);
	p.setBrush(MaterialColorHelper().contrastColorDuplicate(backgroundColor_, 0.7));
	p.drawPath(checkPath);
}

void ButtonMaterialPaintContext::drawIconAndText(QPainter& p) {
	QPushButton* btn = qobject_cast<QPushButton*>(attached_widget);
	const auto adjustments = radius / 2;
	const qreal current_offset_y = shadow_animation_helper->offsetY();
	const QRectF rect = attached_widget->rect().adjusted(
	    adjustments, adjustments + current_offset_y, -adjustments, -adjustments + current_offset_y);

	constexpr qreal iconTextSpacing = 8.0;
	const QString txt = btn->text();
	const bool hasText = !txt.isEmpty();
	const bool hasIcon = !btn->icon().isNull();

	QSizeF iconSizeF(0, 0);
	QRectF iconRect;

	QFont f = btn->font();
	p.setFont(f);
	QFontMetricsF fm(f);

	qreal spacing = hasIcon && hasText ? 6.0 : 0.0;
	QRectF textRect;

	qreal desiredIconHeight = std::min<qreal>(rect.height() * 0.56, 20.0);
	qreal desiredIconWidth = desiredIconHeight;

	QSizeF textSize = fm.size(Qt::TextSingleLine, txt);
	qreal totalWidth = 0.0;

	if (hasIcon)
		totalWidth += desiredIconWidth;
	if (hasText)
		totalWidth += textSize.width();
	if (hasIcon && hasText)
		totalWidth += spacing;

	// Calculates rects
	qreal startX = rect.center().x() - totalWidth / 2.0;
	qreal centerY = rect.center().y();

	if (hasIcon) {
		iconSizeF = QSizeF(desiredIconWidth, desiredIconHeight);
		iconRect = QRectF(startX,
		                  centerY - iconSizeF.height() / 2.0,
		                  iconSizeF.width(),
		                  iconSizeF.height());
		startX += desiredIconWidth + spacing;
	}

	if (hasText) {
		textRect = QRectF(startX,
		                  centerY - textSize.height() / 2.0,
		                  textSize.width(),
		                  textSize.height());
	}

	// draw Icons
	if (hasIcon) {
		QIcon::Mode mode = btn->isEnabled() ? QIcon::Normal : QIcon::Disabled;
		QIcon::State state = btn->isChecked() ? QIcon::On : QIcon::Off;
		QPixmap pm = btn->icon().pixmap(iconSizeF.toSize(), mode, state);

		QPixmap tinted(pm.size());
		tinted.fill(Qt::transparent);
		{
			QPainter tp(&tinted);
			tp.setRenderHint(QPainter::Antialiasing, true);
			tp.drawPixmap(0, 0, pm);
			tp.setCompositionMode(QPainter::CompositionMode_SourceIn);
			tp.fillRect(tinted.rect(), textColor_);
		}
		tinted.setDevicePixelRatio(pm.devicePixelRatioF());
		pm = tinted;

		qreal dpr = pm.devicePixelRatioF();
		QRectF sourceRect(0, 0, pm.width() / dpr, pm.height() / dpr);

		p.setRenderHint(QPainter::SmoothPixmapTransform, true);
		p.drawPixmap(iconRect, pm, sourceRect);
	}

	// draw text then
	p.setPen(textColor_);
	p.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, txt);
}

#include "MaterialPropertyString.h"

bool ButtonMaterialPaintContext::propertySettings(const QString property, const QVariant value) {
	using namespace CCWidgetLibrary::MaterialProperty::Button::Style;
	using namespace CCWidgetLibrary::MaterialProperty::Button::Border;
	if (property == STYLE) {
		QString style_val = value.toString();
		if (style_val == FLATED) {
			setBorderColor(Qt::transparent);
			setBorderWidth(0);
		} else if (style_val == OUTLINED) {
			setBorderWidth(3);
			setBorderColor(Qt::black);
		} else {
			return false; // Unknown styles
		}
		return true;
	} else if (property == BORDERCOLOR && value.canConvert<QColor>()) {
		QColor color = value.value<QColor>();
		setBorderColor(color);
		return true;
	} else if (property == BORDERWIDTH) {
		bool ok = false;
		int width = value.toInt(&ok);

		if (!ok)
			return false;

		setBorderWidth(width);
		return true;
	}
	return false;
}

std::optional<QVariant> ButtonMaterialPaintContext::propertyGet(const QString property) {
	using namespace CCWidgetLibrary::MaterialProperty::Button::Style;
	using namespace CCWidgetLibrary::MaterialProperty::Button::Border;
	if (property == STYLE) {
		if (borderWidth_ > 0.0) {
			return { OUTLINED };
		} else {
			return { FLATED };
		}
	}

	if (property == BORDERCOLOR) {
		return { borderColor_ };
	}

	if (property == BORDERWIDTH) {
		return { borderWidth_ };
	}

	return std::nullopt;
}
}
