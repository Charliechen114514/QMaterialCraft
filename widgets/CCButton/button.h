#ifndef BUTTON_H
#define BUTTON_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QPushButton>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCButton : public QPushButton {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "button";
	explicit CCButton(QWidget* parentWidget = nullptr);
	~CCButton();

	void setTextColor(const QColor baseColor, bool autoContrast = false);
	void setBackGroundColor(const QColor baseColor, bool autoContrast = false);

	/**
	 * @brief setBorderWidth set the boarder Width
	 * @param width
	 */
	void setBorderWidth(qreal width);

	/**
	 * @brief setBorderColor set the Boarder Color
	 * @param color
	 */
	void setBorderColor(const QColor& color);

	bool setStyle(const char* style_type);

protected:
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // BUTTON_H
