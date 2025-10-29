#ifndef SHADOWOFFSETSANIMATIONHELPER_H
#define SHADOWOFFSETSANIMATIONHELPER_H
#include "animation_helpers.h"
#include "paintcontext.h"
#include <QColor>
#include <QObject>

namespace CCWidgetLibrary {
class ShadowOffsetsAnimation : public QObject {
	Q_OBJECT
	Q_PROPERTY(int shadowMargin READ shadowMargin WRITE setShadowMargin
	               NOTIFY shadowMarginChanged)
	Q_PROPERTY(int shadowHeight READ shadowHeight WRITE setShadowHeight
	               NOTIFY shadowHeightChanged)
	Q_PROPERTY(qreal offsetY READ offsetY
	               WRITE setoffsetY NOTIFY offsetYChanged)
public:
	static constexpr const short MAX_OFFSETY = 3.0;
	static constexpr const short DURATION_TIME = 80;
	explicit ShadowOffsetsAnimation(QWidget* parent = nullptr);

	void apply_duration(const int duration_new);
	int duration() const;

	int shadowMargin() const;
	int shadowHeight() const;
	void setShadowMargin(int margin);
	void setShadowHeight(int height);

	void process_shadowoffset_action(const MouseEventType e);

	qreal getMaxOffsetY() const;
	void setMaxOffsetY(qreal maxOffsetY);

	void setoffsetY(qreal v);
	qreal offsetY() const;

signals:
	void shadowMarginChanged(int margin);
	void shadowHeightChanged(int height);
	void offsetYChanged(qreal v);
	void offsetYMaxChanged(qreal v);

protected:
	QWidget* attached_widget;
	std::unique_ptr<AnimationHolder> shadow_offset_holder;
	std::unique_ptr<AnimationHolder> offsetY_animation;

	int shadow_margin { 4 };
	int shadow_height { 8 };

	qreal offsetY_ { 0.0 };
	qreal maxOffsetY_ { MAX_OFFSETY };

	QColor shadows_color { 0, 0, 0, 80 };
};

}

#endif // SHADOWOFFSETSANIMATIONHELPER_H
