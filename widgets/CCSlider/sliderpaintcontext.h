#ifndef SLIDERPAINTCONTEXT_H
#define SLIDERPAINTCONTEXT_H
#include "paintcontext.h"
#include <QObject>
#include <QPoint>

namespace CCWidgetLibrary {
class SliderPaintContext : public PaintContext {
	Q_OBJECT
public:
	static constexpr const float WIDTH_PERCENTAGE = 0.8;
	static constexpr const float HEIGHT_PERCENTAGE = 0.3;

	explicit SliderPaintContext(QWidget* attached_widget = nullptr);
	virtual ~SliderPaintContext() = default;

	void setPercentage(const float percentage) noexcept;
	float percentage() const noexcept;

	QPoint lefttop_positions() const noexcept;
	void set_lefttop_positions(const QPoint& p) noexcept;

	virtual float mappings_from_mousepoint(const QMouseEvent* ev);
	virtual float expected_visible_width() const noexcept;
	virtual float expected_visible_height() const noexcept;
signals:
	void percentage_changed(float new_value);

protected:
	float process_percentage { 0.0 };
	QPoint start_postion;
};
}

#endif // SLIDERPAINTCONTEXT_H
