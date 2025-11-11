#ifndef CCTEXTFIELDMATERIALPAINTCONTEXT_H
#define CCTEXTFIELDMATERIALPAINTCONTEXT_H

#include "CCTextField/cctextfieldpaintcontext.h"
#include "animation_helpers.h"
#include "themes/material/MaterialThemeMarker.h"
#include <QColor>

namespace CCWidgetLibrary {

class CCTextFieldMaterialPaintContext : public CCTextFieldPaintContext,
                                        public MaterialThemeMarker {
	Q_OBJECT
	Q_PROPERTY(qreal labelProgress READ labelProgress
	               WRITE setLabelProgress NOTIFY labelProgressChanged FINAL)
	Q_PROPERTY(qreal underlineProgress READ underlineProgress
	               WRITE setUnderlineProgress NOTIFY underlineProgressChanged FINAL)
public:
	static constexpr const short DURATION = 180;
	CCTextFieldMaterialPaintContext(CCTextField* attached_widget);

	bool paint(QPainter& p) override;
	void animateFloatingLabel(bool requestAnimate) override;
	void animateUnderLine(bool requestAnimate) override;

	QColor errorColor() const override;
	void setErrorColor(const QColor& newErrorColor) override;
	void handleResizeEvent(const QResizeEvent* ev) override;
	void animate_error() override;
signals:
	void underlineProgressChanged(qreal v);
	void labelProgressChanged(qreal v);

protected:
	bool eventFilter(QObject* obj, QEvent* ev) override;

private:
	QColor errorColor_ = 0xB00020;
	QColor primary_ = 0x6200EE;
	QColor onSurface_ = Qt::black;
	std::unique_ptr<AnimationHolder> underline_animation;
	std::unique_ptr<AnimationHolder> floating_animation;

private:
	qreal labelProgress_ = 0.0; // 0..1 (0 = inline, 1 = floated)
	qreal underlineProgress_ = 0.0; // 0..1 for animated thickness/color
	bool focused_ = false;
	bool hovered_ = false;

private:
	qreal labelProgress() const;
	void setLabelProgress(qreal p);

	qreal underlineProgress() const;
	void setUnderlineProgress(qreal p);

	void updateFloatingLabelGeometry();
};
}

#endif // CCTEXTFIELDMATERIALPAINTCONTEXT_H
