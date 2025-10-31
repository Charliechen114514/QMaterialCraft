#ifndef PROGRESSBARMATERIALPAINTCONTEXT_H
#define PROGRESSBARMATERIALPAINTCONTEXT_H
#include "MaterialThemeMarker.h"
#include "animation_helpers.h"
#include "progressbar.h"
#include "progressbarpaintcontext.h"
#include <QColor>
#include <QObject>

namespace CCWidgetLibrary {

class HoverColorAnimation;
class RippleAnimation;

class ProgressBarMaterialPaintContext : public ProgressBarPaintContext,
                                        public MaterialThemeMarker {
	Q_OBJECT

	Q_PROPERTY(qreal visualProgress READ visualProgress
	               WRITE setVisualProgress NOTIFY visualProgressChanged FINAL)
	Q_PROPERTY(qreal thickness READ thickness
	               WRITE setThickness NOTIFY thicknessChanged)
	Q_PROPERTY(QColor indicatorColor READ indicatorColor
	               WRITE setIndicatorColor NOTIFY indicatorColorChanged)
	Q_PROPERTY(QColor trackColor READ trackColor
	               WRITE setTrackColor NOTIFY trackColorChanged)
	static constexpr const short VISUAL_DURATION = 180;

public:
	static constexpr const char* WIDGET_NAME = CCProgressBar::WIDGET_NAME;
	explicit ProgressBarMaterialPaintContext(QWidget* parent = nullptr);

	void applyConig(AnimationHelper::ApplySettingsHandler handler);

	qreal visualProgress() const;
	void setVisualProgress(qreal v);

	qreal thickness() const override;
	void setThickness(qreal t) override;

	QColor indicatorColor() const override;
	void setIndicatorColor(const QColor& c) override;

	QColor trackColor() const override;
	void setTrackColor(const QColor& c) override;

	bool paint(QPainter& p) override;
	void handleMouseEvent(const MouseEventType type, QMouseEvent* ev) override;
	void handleHoverEvent(const HoverEventType type, QEvent* ev) override;
	void handleResizeEvent(const QResizeEvent* ev) override;

	bool forceRounded();
	void setForceRounded(bool f);

signals:
	void visualProgressChanged(qreal);
	void thicknessChanged(qreal);
	void indicatorColorChanged(QColor);
	void trackColorChanged(QColor);

private:
	qreal visualProgress_ { 0.0 };
	qreal thickness_;
	QColor indicatorColor_ { Qt::blue };
	QColor trackColor_ { Qt::white };
	std::unique_ptr<AnimationHolder> visual_progress_animation;
	RippleAnimation* ripple_animation;
	HoverColorAnimation* hover_color_animation;
	bool force_rounded { true };
	QColor borderColor_;
	qreal borderWidth_ { 2.0 };

private:
	qreal normalizedValue(int v) const;
	void animateToNormalized(qreal target);
};
}

#endif // PROGRESSBARMATERIALPAINTCONTEXT_H
