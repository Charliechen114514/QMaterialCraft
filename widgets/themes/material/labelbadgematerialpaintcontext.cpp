#include "labelbadgematerialpaintcontext.h"
#include "paintcontextallocator.h"
#include <QLabel>
#include <QPainter>
#include <QStyle>

namespace CCWidgetLibrary {

LabelBadgeMaterialPaintContext::LabelBadgeMaterialPaintContext(
    QWidget* attached_parent)
    : LabelPaintContext(attached_parent) {
}

bool LabelBadgeMaterialPaintContext::paint(QPainter& p) {
	p.setRenderHint(QPainter::Antialiasing);

	QLabel* label = qobject_cast<QLabel*>(attached_widget);
	if (!label)
		return false;

	const QString text = label->text();
	const QFont font = label->font();
	QFontMetrics fm(font);

	QRect textRect = fm.boundingRect(text);
	QRect bgRect = label->rect().adjusted(
	    padding_h_,
	    padding_v_,
	    -padding_h_,
	    -padding_v_);

	QRect actualAcceptRect = QStyle::alignedRect(
	    label->layoutDirection(),
	    label->alignment(),
	    textRect.size(),
	    bgRect);

	QRect real_bg_rect = actualAcceptRect.adjusted(
	    -padding_h_,
	    -padding_v_,
	    padding_h_,
	    padding_v_);
	const float radius = 0.3f * std::min(real_bg_rect.width(), real_bg_rect.height());

	real_bg_rect.adjust(radius / 2, radius / 2, -radius / 2, -radius / 2);

	// background
	p.setPen(Qt::NoPen);
	p.setBrush(bg_color_);
	p.drawRoundedRect(real_bg_rect, radius, radius);

	// text
	p.setPen(text_color_);
	p.setFont(font);
	p.drawText(real_bg_rect, Qt::AlignCenter, text);
	return true;
}

void LabelBadgeMaterialPaintContext::setTextStyle(TextStyle style) {
	if (style_ == style)
		return;
	style_ = style;
	CCWidgetLibrary::TextIndiator* textIndicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();
	textIndicator->applyTo(attached_widget, style);
	attached_widget->updateGeometry();
	attached_widget->update();
}

QSize LabelBadgeMaterialPaintContext::sizeHint() const {
	CCWidgetLibrary::TextIndiator* textIndicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();
	QFontMetrics fm(textIndicator->fontFor(style_));
	QLabel* label = qobject_cast<QLabel*>(attached_widget);
	QSize s = fm.size(Qt::TextSingleLine, label->text());
	s.setWidth(s.width() + padding_h_ * 2);
	s.setHeight(s.height() + padding_v_ * 2);
	return s;
}

void LabelBadgeMaterialPaintContext::setBackgroundColor(const QColor& c) {
	bg_color_ = c;
	attached_widget->update();
}

void LabelBadgeMaterialPaintContext::setTextColor(const QColor& c) {
	text_color_ = c;
	attached_widget->update();
}

void LabelBadgeMaterialPaintContext::setPadding(qreal h, qreal v) {
	padding_h_ = h;
	padding_v_ = v;
	attached_widget->updateGeometry();
}

QColor LabelBadgeMaterialPaintContext::backGroundColor() const {
	return bg_color_;
}

QColor LabelBadgeMaterialPaintContext::textColor() const {
	return text_color_;
}

std::pair<qreal, qreal> LabelBadgeMaterialPaintContext::padding() const {
	return { padding_h_, padding_v_ };
}

}
