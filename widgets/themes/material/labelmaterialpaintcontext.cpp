#include "labelmaterialpaintcontext.h"
#include "paintcontextallocator.h"
#include "themes/material/animation_wrapper/opacityanimation.h"
#include <QLabel>
#include <QPainter>

namespace CCWidgetLibrary {
LabelMaterialPaintContext::LabelMaterialPaintContext(
    QWidget* attached_widget)
    : LabelPaintContext(attached_widget) {
	opacity_animation = new OpacityAnimation(attached_widget);
	opacity_animation->applyConfigs([](AnimationHelper::SettingsConfig& conf) {
		conf.period_time = 400;
		conf.curve = QEasingCurve::InOutQuad;
	});

	CCWidgetLibrary::TextIndiator* textIndicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();
	textIndicator->applyTo(attached_widget, style_);
	attached_widget->updateGeometry();
	attached_widget->update();
}

bool LabelMaterialPaintContext::paint(QPainter& p) {
	p.setRenderHint(QPainter::TextAntialiasing);
	p.setOpacity(opacity_animation->opacity());
	p.setPen(color_);
	p.setFont(attached_widget->font());

	QLabel* label = qobject_cast<QLabel*>(attached_widget);

	QTextOption opt(label->alignment());
	opt.setWrapMode(QTextOption::WordWrap);

	QRectF bounds = attached_widget->rect();

	p.drawText(bounds, label->text(), opt);

	return true;
}

void LabelMaterialPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	switch (type) {
	case HoverEventType::HOVER_IN:
		opacity_animation->activate_as_fadeIn();
		break;
	case HoverEventType::HOVER_OUT:
		opacity_animation->activate_as_fadeOut();
		break;
	}
}

void LabelMaterialPaintContext::setTextStyle(TextStyle style) {
	if (style_ == style)
		return;
	style_ = style;
	CCWidgetLibrary::TextIndiator* textIndicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();
	textIndicator->applyTo(attached_widget, style);
	attached_widget->updateGeometry();
	attached_widget->update();
}

void LabelMaterialPaintContext::setTextColor(const QColor& color) {
	color_ = color;
	attached_widget->update();
}
}
