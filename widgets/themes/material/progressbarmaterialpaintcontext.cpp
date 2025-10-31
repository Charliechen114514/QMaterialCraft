#include "progressbarmaterialpaintcontext.h"
#include "material_color_helper.h"
#include "themes/material/animation_wrapper/hoveranimationhelper.h"
#include "themes/material/animation_wrapper/rippleanimation.h"
#include <QPainter>
#include <QProgressBar>

namespace CCWidgetLibrary {
ProgressBarMaterialPaintContext::ProgressBarMaterialPaintContext(
    QWidget* parent)
    : ProgressBarPaintContext { parent } {
	visual_progress_animation = std::make_unique<AnimationHolder>(this, "visualProgress");
	borderColor_ = indicatorColor_;
	applyConig([this](AnimationHelper::SettingsConfig& conf) {
		conf.period_time = VISUAL_DURATION;
		conf.curve = QEasingCurve::InOutCubic;
	});
	QProgressBar* bar = qobject_cast<QProgressBar*>(attached_widget);
	connect(bar, &QProgressBar::valueChanged, this, [this](int newVal) {
		animateToNormalized(normalizedValue(newVal));
	});

	ripple_animation = new RippleAnimation(attached_widget);
	hover_color_animation = new HoverColorAnimation(attached_widget);
}

void ProgressBarMaterialPaintContext::applyConig(AnimationHelper::ApplySettingsHandler handler) {
	visual_progress_animation->get_helpers()->applySettings(handler);
}

qreal ProgressBarMaterialPaintContext::visualProgress() const {
	return visualProgress_;
}

void ProgressBarMaterialPaintContext::setVisualProgress(qreal v) {
	v = qBound<qreal>(0.0, v, 1.0);
	if (!qFuzzyCompare(v, visualProgress_)) {
		visualProgress_ = v;
		emit visualProgressChanged(v);
		attached_widget->update();
	}
}

qreal ProgressBarMaterialPaintContext::thickness() const {
	return thickness_;
}

void ProgressBarMaterialPaintContext::setThickness(qreal t) {
	if (t == thickness_)
		return;
	thickness_ = t;
	emit thicknessChanged(t);
	attached_widget->update();
}

QColor ProgressBarMaterialPaintContext::indicatorColor() const {
	return indicatorColor_;
}

void ProgressBarMaterialPaintContext::setIndicatorColor(const QColor& c) {
	if (indicatorColor_ == c)
		return;
	indicatorColor_ = c;
	borderColor_ = indicatorColor_;
	emit indicatorColorChanged(c);
	attached_widget->update();
}

QColor ProgressBarMaterialPaintContext::trackColor() const {
	return trackColor_;
}

void ProgressBarMaterialPaintContext::setTrackColor(const QColor& c) {
	if (c == trackColor_)
		return;
	trackColor_ = c;
	emit trackColorChanged(c);
	attached_widget->update();
}

bool ProgressBarMaterialPaintContext::paint(QPainter& p) {
	p.save();
	p.setRenderHint(QPainter::Antialiasing, true);
	QRectF cr = attached_widget->contentsRect();

	const qreal h = std::min(thickness_, cr.height());
	const qreal y = cr.y() + (cr.height() - h) / 2.0;
	const qreal radius = h / 2.0;

	/*
	 * Tracker Colors
	 */
	QRectF trackRect(cr.x(), y, cr.width(), h);
	QBrush trackBrush(hover_color_animation->get_current_bgColor(trackColor_));
	// p.setPen(Qt::NoPen);
	if (borderWidth_ > 0.0) {
		qreal halfPen = borderWidth_ / 2.0;
		trackRect = trackRect.adjusted(halfPen, halfPen, -halfPen, -halfPen);
	}

	QPen pen;
	pen.setColor(borderColor_);
	if (borderWidth_ > 0.0) {
		pen = QPen(borderColor_, borderWidth_);
		pen.setJoinStyle(Qt::RoundJoin);
		pen.setCapStyle(Qt::RoundCap);
	} else {
		pen = Qt::NoPen;
	}
	p.setPen(pen);

	p.setBrush(trackBrush);
	p.drawRoundedRect(trackRect, radius, radius);

	const qreal w = cr.width() * qBound<qreal>(0.0, visualProgress_, 1.0);
	if (w > 0.0) {
		QRectF filledRect(cr.x(), y, w, h);
		p.setBrush(hover_color_animation->get_current_bgColor(indicatorColor_));
		p.drawRoundedRect(filledRect, radius, radius);
	}

	/*
	 * Text Render
	 */
	QProgressBar* bar = qobject_cast<QProgressBar*>(attached_widget);
	const QString txt = bar->text();

	if (!txt.isEmpty()) {
		const qreal centerX = cr.x() + cr.width() * 0.5;
		const QColor bgColorAtCenter = (centerX <= cr.x() + w) ? indicatorColor_ : trackColor_;
		const QColor text_color = MaterialColorHelper().contrastColorSimple(bgColorAtCenter);

		p.setPen(text_color);
		p.setBrush(Qt::NoBrush);
		// ensure eliding if too long
		QFontMetrics fm(bar->font());
		QString elided = fm.elidedText(txt, Qt::ElideRight, (int)trackRect.width() - 8);
		p.drawText(trackRect, Qt::AlignCenter, elided);
	}

	ripple_animation->process_ripple_draw(p, Qt::white);

	p.restore();
	return true;
}

void ProgressBarMaterialPaintContext::handleMouseEvent(const MouseEventType type, QMouseEvent* ev) {
	ripple_animation->activate_with_mouse_event(type, ev);
}

void ProgressBarMaterialPaintContext::handleHoverEvent(const HoverEventType type, QEvent* ev) {
	hover_color_animation->activate_hover_animation(type);
}

void ProgressBarMaterialPaintContext::handleResizeEvent(const QResizeEvent* ev) {
	if (!force_rounded)
		return; // not force rounded;
	QRectF cr = attached_widget->contentsRect();
	thickness_ = cr.height();
}

bool ProgressBarMaterialPaintContext::forceRounded() {
	return force_rounded;
}

void ProgressBarMaterialPaintContext::setForceRounded(bool f) {
	force_rounded = f;
}

qreal ProgressBarMaterialPaintContext::normalizedValue(int v) const {
	QProgressBar* bar = qobject_cast<QProgressBar*>(attached_widget);
	int lo = bar->minimum();
	int hi = bar->maximum();
	if (hi <= lo)
		return 0.0;
	return qBound<qreal>(0.0, (qreal)(v - lo) / (qreal)(hi - lo), 1.0);
}

void ProgressBarMaterialPaintContext::animateToNormalized(qreal target) {
	visual_progress_animation->get_helpers()->applySession(
	    [this, target](AnimationHelper::RuntimeConfig& conf) {
		    conf.start = visualProgress_;
		    conf.end = qBound<qreal>(0.0, target, 1.0);
	    });
}
}
