#include "colorhelper.h"

QColor CCWidgetLibrary::ColorHelper::
    contrastColorDuplicate(const QColor& baseColor, const float strength) {
	return contrastColorSimple(baseColor);
}
