#ifndef RIPPLEANIMATION_H
#define RIPPLEANIMATION_H

#include "animation_helpers.h"
#include "paintcontext.h"
#include <QObject>
#include <QPoint>

class QMouseEvent;
class QPainter;

namespace CCWidgetLibrary {
class RippleAnimation : public QObject {
	Q_OBJECT
	Q_PROPERTY(qreal rippleRadius READ rippleRadius
	               WRITE setRippleRadius NOTIFY rippleRadiusChanged)
	Q_PROPERTY(qreal rippleOpacity READ rippleOpacity
	               WRITE setRippleOpacity NOTIFY rippleOpacityChanged)
public:
	static constexpr const unsigned int RIPPLE_TIME = 400;
	explicit RippleAnimation(QWidget* parent = nullptr);

	void setRippleRadius(qreal v);
	void setRippleOpacity(qreal v);
	qreal rippleRadius() const;
	qreal rippleOpacity() const;

	void applyConfigs(AnimationHelper::ApplySettingsHandler handler);

	void apply_duration(int duration_new);
	int duration() const;

	void process_ripple_draw(QPainter& p, const QColor& baseColor);
	void process_ripple_draw(QPainter& p, const QPointF center, const QColor& baseColor);

	void activate_with_mouse_event(const MouseEventType e, QMouseEvent* ev);
	void activate(const MouseEventType e, QMouseEvent* ev, const qreal size);
	bool rippleAvaiable() const;

	qreal getMaxOpacity() const;
	void setMaxOpacity(qreal newMaxOpacity);

signals:
	void rippleRadiusChanged(qreal rippleRadius);
	void rippleOpacityChanged(qreal rippleOpacity);

private:
	std::unique_ptr<AnimationHolder> ripple_animation;
	qreal rippleRadius_ = 0.0;
	qreal rippleOpacity_ = 0.0;
	qreal maxOpacity { 0.4 };
	QPointF pressPosition;
	QWidget* attached_widget;
};
}

#endif // RIPPLEANIMATION_H
