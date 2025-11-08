/**
 * @author  Charliechen114514
 * @date    2025-11-1
 * @brief   these file expected to provide some helpers
 *          for widget settings
 */
#ifndef COMMONWIDGETSETTINGSHELPER_H
#define COMMONWIDGETSETTINGSHELPER_H
#include "CCWidgets_BuildDefine.h"

class QWidget;
class QLabel;
class QColor;

namespace CCWidgetLibrary {
namespace WidgetHelpers {
	/**
	 * @brief   setWidgetBackgroundTransparent will set the
	 *          widget background transparent, these is using
	 *          for clip off the annoying rects
	 *          same as the QSS: {"background: transparent"}
	 * @param target_widget
	 */
	void CCWIDGET_EXPORT setWidgetBackgroundTransparent(QWidget* target_widget);

	/**
	 * @brief   setLabelFontWithColor will set the label font
	 *          with target color and size, same in QSS:
	 *          {"font-size: ${pixel_size}; color: ${font_color};"}
	 * @param label
	 * @param pixel_size
	 * @param font_color
	 */
	void CCWIDGET_EXPORT setLabelFontWithColor(QLabel* label,
	                                           const int pixel_size,
	                                           const QColor& font_color);
}
}

#endif // COMMONWIDGETSETTINGSHELPER_H
