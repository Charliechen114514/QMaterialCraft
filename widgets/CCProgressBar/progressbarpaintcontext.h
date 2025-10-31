#ifndef PROGRESSBARPAINTCONTEXT_H
#define PROGRESSBARPAINTCONTEXT_H

#include <paintcontext.h>

namespace CCWidgetLibrary {
class ProgressBarPaintContext : public PaintContext {
public:
	explicit ProgressBarPaintContext(QWidget* attatch_parent = nullptr);
	virtual qreal thickness() const = 0;
	virtual void setThickness(qreal t) = 0;

	virtual QColor indicatorColor() const = 0;
	virtual void setIndicatorColor(const QColor& c) = 0;

	virtual QColor trackColor() const = 0;
	virtual void setTrackColor(const QColor& c) = 0;
};

}

#endif // PROGRESSBARPAINTCONTEXT_H
