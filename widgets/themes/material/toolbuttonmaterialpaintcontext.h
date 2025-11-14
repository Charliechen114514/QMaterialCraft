#ifndef TOOLBUTTONMATERIALPAINTCONTEXT_H
#define TOOLBUTTONMATERIALPAINTCONTEXT_H

#include "CCToolButton/toolbuttonpaintcontext.h"
#include <QColor>

namespace CCWidgetLibrary {

class HoverColorAnimation;

class MaterialToolButtonPaintContext : public ToolButtonPaintContext {
public:
	explicit MaterialToolButtonPaintContext(QToolButton* attached_widget);

	bool paint(QPainter& p) override;
	void handleHoverEvent(const HoverEventType type, QEvent* ev) override;
	QSize sizeHint() const override;

	bool propertySettings(const QString property, const QVariant value) override;
	std::optional<QVariant> propertyGet(const QString property) override;

private:
	QColor background_color { 0x6200EE };
	QColor checked_text_color { 0x2196F3 };
	QColor unchecked_text_color { 0, 0, 0, static_cast<int>(0.87 * 255) };
	HoverColorAnimation* hover_animation;
};
}

#endif // TOOLBUTTONMATERIALPAINTCONTEXT_H
