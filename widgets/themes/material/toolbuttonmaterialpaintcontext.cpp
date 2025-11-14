#include "toolbuttonmaterialpaintcontext.h"
#include "Commons/property_string.h"
#include "helpers/animations/hoveranimationhelper.h"
#include <QPainter>
#include <QToolButton>

namespace CCWidgetLibrary {

MaterialToolButtonPaintContext::MaterialToolButtonPaintContext(
    QToolButton* attached_widget)
    : ToolButtonPaintContext(attached_widget) {
	attached_widget->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	attached_widget->setAutoRaise(true);
	attached_widget->setCursor(Qt::PointingHandCursor);
	attached_widget->setCheckable(true);
	attached_widget->setMouseTracking(true);

	hover_animation = new HoverColorAnimation(attached_widget);
	hover_animation->apply_duration(400);
}

bool MaterialToolButtonPaintContext::paint(QPainter& p) {
	p.save();
	QToolButton* btn = dynamic_cast<QToolButton*>(attached_widget);

	QColor current_shell_hover_color = attached_widget->isEnabled()
	    ? hover_animation->get_current_bgColor(background_color)
	    : background_color;

	p.setPen(Qt::NoPen);
	p.setBrush(current_shell_hover_color);
	p.drawRoundedRect(btn->rect(), 6, 6);

	QColor textColor = btn->isChecked() ? checked_text_color
	                                    : unchecked_text_color;

	p.setPen(textColor);

	QRect contentRect = btn->rect().adjusted(14, 8, -14, -8);

	QIcon icon = btn->icon();
	QSize iconSize = btn->iconSize();
	QPixmap pix;

	if (!icon.isNull()) {
		pix = icon.pixmap(iconSize,
		                  btn->isEnabled() ? QIcon::Normal : QIcon::Disabled);
	}

	if (btn->toolButtonStyle() == Qt::ToolButtonTextUnderIcon) {
		int spacing = 4;

		QRect iconRect(
		    contentRect.center().x() - iconSize.width() / 2,
		    contentRect.y(),
		    iconSize.width(),
		    iconSize.height());

		if (!pix.isNull())
			p.drawPixmap(iconRect.topLeft(), pix);

		QRect textRect(
		    contentRect.x(),
		    iconRect.bottom() + spacing,
		    contentRect.width(),
		    contentRect.height() - iconRect.height() - spacing);

		p.drawText(textRect, Qt::AlignHCenter | Qt::AlignTop, btn->text());
	} else {
		int spacing = 6;

		QRect iconRect(
		    contentRect.x(),
		    contentRect.center().y() - iconSize.height() / 2,
		    iconSize.width(),
		    iconSize.height());

		if (!pix.isNull())
			p.drawPixmap(iconRect.topLeft(), pix);

		QRect textRect(
		    iconRect.right() + spacing,
		    contentRect.y(),
		    contentRect.width() - iconRect.width() - spacing,
		    contentRect.height());

		p.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, btn->text());
	}

	p.restore();
	return true;
}

void MaterialToolButtonPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	hover_animation->activate_hover_animation(type);
}

QSize MaterialToolButtonPaintContext::sizeHint() const {
	QToolButton* btn = dynamic_cast<QToolButton*>(attached_widget);
	QFontMetrics fm(btn->font());
	int w = fm.horizontalAdvance(btn->text()) + 28;
	int h = fm.height() + 16;
	return QSize(w, h);
}

bool MaterialToolButtonPaintContext::
    propertySettings(const QString property, const QVariant value) {
	using namespace CCWidgetLibrary::CCToolButton;
	if (property == CHECKED_TEXT_COLOR) {
		auto c = value.value<QColor>();
		if (c.isValid()) {
			checked_text_color = c;
		} else {
			return false;
		}
		return true;
	} else if (property == UNCHECKED_TEXT_COLOR) {
		auto c = value.value<QColor>();
		if (c.isValid()) {
			unchecked_text_color = c;
		} else {
			return false;
		}
		return true;
	}

	return false;
}

std::optional<QVariant> MaterialToolButtonPaintContext::propertyGet(const QString property) {
	using namespace CCWidgetLibrary::CCToolButton;
	if (property == CHECKED_TEXT_COLOR) {
		return { checked_text_color };
	} else if (property == UNCHECKED_TEXT_COLOR) {
		return {
			unchecked_text_color
		};
	} else if (property == BACKGROUND_COLOR) {
	}
	return std::nullopt;
}
}
