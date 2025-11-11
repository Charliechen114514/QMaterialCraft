#ifndef HOVERANIMATIONHELPER_H
#define HOVERANIMATIONHELPER_H
#include "animation_helpers.h"
#include "paintcontext.h"
#include <QObject>

namespace CCWidgetLibrary {

class HoverAnimationHelper : public QObject {
	Q_OBJECT
	Q_PROPERTY(qreal hoverProcess READ hoverProcess
	               WRITE setHoverProcess NOTIFY hoverProcessChanged FINAL)
public:
	static constexpr short HOVER_TIME = 150;
	explicit HoverAnimationHelper(QWidget* parent = nullptr);
	virtual ~HoverAnimationHelper() = default;

	qreal hoverProcess() const;
	void setHoverProcess(qreal hoverProcess);

	void apply_duration(int duration_new);
	int duration() const;

	void activate_hover_animation(const HoverEventType type);

	bool isHovering() const;
signals:
	void hoverProcessChanged(qreal hoverProcess);

protected:
	bool isHovering_ { false };
	qreal hoverProcess_ { 0.0 };
	std::unique_ptr<AnimationHolder> hover_animation;
	QWidget* attached_parent { nullptr };

private:
	void activate_hover_in();
	void activate_hover_out();
};

class HoverColorAnimation : public HoverAnimationHelper {
	Q_OBJECT
	Q_PROPERTY(short light_level READ light_level
	               WRITE setLightLevel NOTIFY lightLevelChanged FINAL)
public:
	static constexpr const short LIGHT_WITH = 120;
	explicit HoverColorAnimation(QWidget* parent = nullptr);
	~HoverColorAnimation() override = default;

	QColor get_current_bgColor(const QColor& base) const;

	short light_level() const { return light_level_; }
	void setLightLevel(const short light_level) {
		if (light_level == light_level_)
			return;
		emit lightLevelChanged(light_level);
		light_level_ = light_level;
	}

signals:
	void lightLevelChanged(short light_level);

protected:
	short light_level_ { LIGHT_WITH };
};
}

#endif // HOVERANIMATIONHELPER_H
