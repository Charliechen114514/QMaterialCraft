#ifndef CCSILDER_H
#define CCSILDER_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QSlider>

CONTEXT_PAINT_PREANNOUNCE;

/**
 * @brief   The CCSilder is a material or other style
 *          defines Slider for the QSlider
 */
class CCWIDGET_EXPORT CCSlider : public QSlider {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "slider";

	CCSlider(QWidget* parent = nullptr);
	~CCSlider();

protected:
	void resizeEvent(QResizeEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

private:
	bool isPressed { false };
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCSILDER_H
