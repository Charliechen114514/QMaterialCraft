#ifndef APPEARANIMATION_H
#define APPEARANIMATION_H
#include "CCWidgets_BuildDefine.h"
#include "commons.h"
#include <QObject>
#include <QPoint>

class QGraphicsOpacityEffect;
class QParallelAnimationGroup;
class QPropertyAnimation;

namespace CCWidgetLibrary {
namespace animation {
	class CCWIDGET_EXPORT AppearAnimation : public QObject {
		Q_OBJECT
	public:
		explicit AppearAnimation(QWidget* parent = nullptr);

		void apply_config(const AnimationConfig& config);

		void appear();
		void disappear(bool hide = true);

		QPoint getStartPos() const;
		void setStartPos(QPoint newStartPos);
		QPoint getEndPos() const;
		void setEndPos(QPoint newEndPos);
		qreal getAppear_opacity() const;
		void setAppear_opacity(qreal newAppear_opacity);
		qreal getDisappear_opacity() const;
		void setDisappear_opacity(qreal newDisappear_opacity);

	signals:
		void finished();

	private:
		QWidget* widget;
		QWidget* container;
		QPoint startPos;
		QPoint endPos;
		qreal appear_opacity { 1.0 };
		qreal disappear_opacity { 0.0 };
		QParallelAnimationGroup* animation_group;
		QPropertyAnimation* position_animation;
		QPropertyAnimation* opacity_animation;
	};

}
}

#endif // APPEARANIMATION_H
