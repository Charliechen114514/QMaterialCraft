#include "calendarwidgetmaterialpaintcontext.h"
#include <QCalendarWidget>
#include <QHeaderView>
#include <QPainter>

namespace CCWidgetLibrary {

MaterialCalendarWidgetPaintContext::
    MaterialCalendarWidgetPaintContext(QCalendarWidget* w)
    : CalendarWidgetPaintContext(w) {
	calendar = w;
	holder = new OpacityAnimation(w);
	holder->applyConfigs([this](AnimationHelper::SettingsConfig& c) {
		c.curve = QEasingCurve::OutCubic;
		c.period_time = 280;
	});
	w->setNavigationBarVisible(true);
	w->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	w->setFirstDayOfWeek(Qt::Monday);

	w->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	connect(calendar, &QCalendarWidget::selectionChanged, this, [this]() {
		holder->activate_as_fadeIn();
	});

	QWidget* nav = calendar->findChild<QWidget*>("qt_calendar_navigationbar");
	if (nav) {
		nav->setStyleSheet("background-color: rgba(0,0,0,0.04); border: none;");
	}
	QHeaderView* header = calendar->findChild<QHeaderView*>();
	if (header) {
		header->setStyleSheet("QHeaderView::section { background: transparent; color: rgba(0,0,0,0.6); border: none; }");
	}
}

bool MaterialCalendarWidgetPaintContext::paint(QPainter& p) {
	QWidget* nav = calendar->findChild<QWidget*>(QStringLiteral("qt_calendar_navigationbar"));
	if (nav) {
		QPainter p(nav);
		p.setRenderHint(QPainter::Antialiasing, true);
		QRect r = nav->rect();
		QColor bg = calendar->palette().color(QPalette::Window);
		// Slight elevation effect
		QLinearGradient g(r.topLeft(), r.bottomLeft());
		g.setColorAt(0.0, bg.lighter(102));
		g.setColorAt(1.0, bg);
		p.fillRect(r, g);
	}
	return true;
}

QColor MaterialCalendarWidgetPaintContext::accentColor() const {
	return accentColor_;
}

void MaterialCalendarWidgetPaintContext::setAccentColor(const QColor& c) {
	accentColor_ = c;
	calendar->update();
}

int MaterialCalendarWidgetPaintContext::cornerRadius() const {
	return cornerRadius_;
}

void MaterialCalendarWidgetPaintContext::setCornerRadius(int r) {
	cornerRadius_ = r;
	calendar->update();
}

void MaterialCalendarWidgetPaintContext::paintCell(QPainter* painter, const QRect& rect, const QDate& date) {

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing, true);

	const QDate sel = calendar->selectedDate();
	const QDate today = QDate::currentDate();

	// Background fill for the cell (transparent by default)
	painter->setPen(Qt::NoPen);

	// Draw selected date background with animated alpha
	if (date == sel) {
		QColor fill = accentColor_;
		// Animated alpha: from 0.28 -> 1.0 (subtle entrance)
		qreal alphaBase = 0.9; // base alpha to multiply
		int a = qRound(255 * (0.12 + 0.88 * holder->opacity()));
		fill.setAlpha(a);
		QRectF r = rect.adjusted(4, 4, -4, -4);
		painter->setBrush(fill);
		painter->drawRoundedRect(r, cornerRadius_, cornerRadius_);

		// Day number in contrast color
		painter->setPen(Qt::white);
		painter->setFont(calendar->font());
		painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));

		painter->restore();
		return;
	}

	// Draw today indicator (outline)
	if (date == today) {
		QRectF centerRect = rect.adjusted(8, 8, -8, -8);
		QColor outline = accentColor_;
		outline.setAlpha(180);
		painter->setPen(QPen(outline, 1.5));
		painter->setBrush(Qt::NoBrush);
		painter->drawEllipse(centerRect);

		// day number with accent color
		painter->setPen(accentColor_);
		painter->setFont(calendar->font());
		painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));

		painter->restore();
		return;
	}

	// Normal day
	painter->setPen(calendar->palette().color(QPalette::WindowText));
	painter->setFont(calendar->font());
	painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));

	painter->restore();
}
}
