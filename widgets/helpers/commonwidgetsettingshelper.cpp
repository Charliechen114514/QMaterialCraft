#include "commonwidgetsettingshelper.h"
#include <QLabel>

namespace CCWidgetLibrary::WidgetHelpers {

void setWidgetBackgroundTransparent(QWidget* target_widget) {
	QPalette pal = target_widget->palette();
	pal.setColor(QPalette::Window, Qt::transparent);
	target_widget->setPalette(pal);
	target_widget->setAutoFillBackground(true);
}

void setLabelFontWithColor(QLabel* label,
                           const int pixel_size,
                           const QColor& font_color) {
	QFont font = label->font();
	font.setPointSize(pixel_size);
	label->setFont(font);

	QPalette pal = label->palette();
	pal.setColor(QPalette::WindowText, font_color);
	label->setPalette(pal);
}

}
