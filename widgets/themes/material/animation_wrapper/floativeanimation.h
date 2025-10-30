#ifndef FLOATIVEANIMATION_H
#define FLOATIVEANIMATION_H
#include "animation_helpers.h"
#include "paintcontext.h"
#include <QObject>

namespace CCWidgetLibrary {
class FloativeAnimation : public QObject {
	Q_OBJECT

	Q_PROPERTY(qreal floative_y READ floative_y
	               WRITE setFloative_y NOTIFY floativeYChanged)

public:
	static constexpr short FLOATIVE_ANIMATION = 150;
	explicit FloativeAnimation(QWidget* parent = nullptr);

	void applyConfig(AnimationHelper::ApplySettingsHandler handler);
	qreal floative_y() const;
	void setFloative_y(const qreal floative_y);

	qreal getFloative_y_max() const;
	void setFloative_y_max(qreal newFloative_y_max);

	void activate_floatup();
	void activate_sinkdown();

	void activete_with_hover(const HoverEventType ev);

signals:
	void floativeYChanged(qreal v);

private:
	QWidget* attached_parent;
	qreal floative_y_max { 5.0 };
	qreal floative_y_ { 0.0 };
	std::unique_ptr<AnimationHolder>
	    floating_animation;
};
}
#endif // FLOATIVEANIMATION_H
