#ifndef OPACITYANIMATION_H
#define OPACITYANIMATION_H
#include "animation_helpers.h"
#include <QObject>

namespace CCWidgetLibrary {
class OpacityAnimation : public QObject {
	Q_OBJECT
	Q_PROPERTY(qreal opacity READ opacity
	               WRITE setOpacity NOTIFY opacityChanged)

public:
	explicit OpacityAnimation(QWidget* parent = nullptr);
	void setOpacity(qreal opacity);
	qreal opacity() const;

	void applyConfigs(AnimationHelper::ApplySettingsHandler handler);

	void activate_as_fadeIn();
	void activate_as_fadeOut();

	void setMaxOpacity(qreal maxOpacity);
	qreal maxOpacity() const;

	void setMinOpacity(qreal minOpacity);
	qreal minOpacity() const;

signals:
	void opacityChanged();

private:
	std::unique_ptr<AnimationHolder> opacity_animation;
	QWidget* attached_parent;
	qreal opacity_ { 0.5 };
	qreal max_opacity_ { 1.0 };
	qreal min_opacity_ { 0.5 };
};
}

#endif // OPACITYANIMATION_H
