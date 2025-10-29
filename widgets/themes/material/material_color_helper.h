#ifndef MATERIAL_COLOR_HELPER_H
#define MATERIAL_COLOR_HELPER_H
#include "colorhelper.h"

namespace CCWidgetLibrary {
class MaterialColorHelper : public ColorHelper {
public:
	MaterialColorHelper() = default;
	~MaterialColorHelper() override = default;

	QColor contrastColorSimple(const QColor& baseColor) override;
	QColor harmonizeColor(const QColor& base,
	                      double lightnessFactor,
	                      double saturationFactor) override;
	double luminance(const QColor& color) override;

	QColor contrastColorDuplicate(
	    const QColor& baseColor, const float strength) override;
};
}

#endif // MATERIAL_COLOR_HELPER_H
