#ifndef SLIDERMATERIALPAINTCONTEXT_H
#define SLIDERMATERIALPAINTCONTEXT_H
#include "CCSlider/slider.h"
#include "CCSlider/sliderpaintcontext.h"
#include "animation_helpers.h"

#include "themes/material/MaterialThemeMarker.h"
#include "themes/material/animation_wrapper/rippleanimation.h"
#include <QColor>
#include <QObject>
class QPropertyAnimation;
class QVariantAnimation;

namespace CCWidgetLibrary {

struct MaterialSliderHelpers {
	static QColor autoTrackColor(const QColor& thumbColor) noexcept;
	static QColor autoThumbColor(const QColor& trackColor) noexcept;
	static QColor pressedColor(const QColor& base) noexcept;
};

class SliderMaterialPaintContext : public SliderPaintContext,
                                   public MaterialThemeMarker {
	Q_OBJECT
	Q_PROPERTY(float radius READ _radius WRITE setRadius
	               NOTIFY knobRadiusChanged)

public:
	static constexpr const char* SLIDER_NAME = CCSlider::WIDGET_NAME;
	static constexpr const float PRESSED_STREEED = 1.3;
	static constexpr const float UNPRESSED_STREEED = 1.1;

	explicit SliderMaterialPaintContext(QSlider* widget = nullptr);
	~SliderMaterialPaintContext();

	qreal computeRippleTargetRadius() const;

	enum class Roles {
		Knob,
		Track
	};

	void setColor(const QColor& color,
	              const Roles which);
	QColor color(const Roles which) const noexcept;

	float _radius() const noexcept;
	void setRadius(float radius);

	bool paint(QPainter& p) override;
	void handleMouseEvent(
	    const MouseEventType type, QMouseEvent* ev) override;
	void handleResizeEvent(const QResizeEvent* ev) override;

signals:
	void knobRadiusChanged(float new_radius);

private:
	QColor knobColor { 0x6200EE };
	QColor trackColor { 0xE0E0E0 };
	QColor pressedColor;

	float current_knob_radius;

private: // Animations
	static constexpr const int ANI_RADIUS_DURATION = 150;
	QPropertyAnimation* ani_radius;
	QVariantAnimation* ani_ripple;
	std::unique_ptr<AnimationHelper> ani_radius_helpers;
	RippleAnimation* rippleAnimation;

private:
	void handle_mouseclicked_session(QMouseEvent* ev);
	void handle_mouserelease_session(QMouseEvent* ev);
	int validify_knob_radius(int val);
};
}

#endif // SLIDERMATERIALPAINTCONTEXT_H
