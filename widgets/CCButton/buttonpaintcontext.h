#ifndef BUTTONPAINTCONTEXT_H
#define BUTTONPAINTCONTEXT_H

#include "paintcontext.h"

namespace CCWidgetLibrary {
class ButtonPaintContext : public PaintContext {
public:
	ButtonPaintContext(QWidget* attachted_widget);
	/**
	 * @brief setBackgroundColor: This interfaces sets the
	 * @param c the color we set
	 * @param autoContrast shell auto flip the background Color
	 */
	virtual void setBackgroundColor(const QColor& c, bool autoContrast = false) = 0;

	/**
	 * @brief setTextColor
	 * @param c
	 * @param autoContrast
	 */
	virtual void setTextColor(const QColor& c, bool autoContrast = false) = 0;

	/**
	 * @brief setBorderWidth set the boarder Width
	 * @param width
	 */
	virtual void setBorderWidth(qreal width) = 0;

	/**
	 * @brief setBorderColor set the Boarder Color
	 * @param color
	 */
	virtual void setBorderColor(const QColor& color) = 0;
};
}

#endif // BUTTONPAINTCONTEXT_H
