#ifndef MATERIALCONTAINERDEFAULTPAINTCONTEXT_H
#define MATERIALCONTAINERDEFAULTPAINTCONTEXT_H
#include "helpers/animations/rippleanimation.h"
#include "paintcontext.h"
class QAbstractItemView;

namespace CCWidgetLibrary {
class MaterialContainerDefaultPaintHelpers {
public:
	explicit MaterialContainerDefaultPaintHelpers(
	    QAbstractItemView* binded_view = nullptr);

	bool paint(QPainter& p);
	void handleMouseEvent(
	    const MouseEventType type, QMouseEvent* ev);

private:
	RippleAnimation* ripple_animations;
	QAbstractItemView* binded_view;
	QPointF pressed_points {};
};
}

#endif // MATERIALCONTAINERDEFAULTPAINTCONTEXT_H
