#include "material_color_helper.h"

namespace CCWidgetLibrary {
QColor MaterialColorHelper::contrastColorSimple(const QColor& baseColor) {
	return luminance(baseColor) > 0.5 ? QColor(0, 0, 0) : QColor(255, 255, 255);
}

QColor MaterialColorHelper::harmonizeColor(
    const QColor& base,
    double lightnessFactor,
    double saturationFactor) {
	QColor hsl = base.toHsl();
	int h = hsl.hue();
	double s = std::clamp(hsl.saturationF() * saturationFactor, 0.0, 1.0);
	double l = std::clamp(hsl.lightnessF() * lightnessFactor, 0.0, 1.0);
	return QColor::fromHslF(h / 360.0, s, l);
}

double MaterialColorHelper::luminance(const QColor& color) {
	auto luminance_vector = [](double v) {
		v /= 255.0;
		return (v <= 0.03928) ? (v / 12.92) : std::pow((v + 0.055) / 1.055, 2.4);
	};

	double r = luminance_vector(color.red());
	double g = luminance_vector(color.green());
	double b = luminance_vector(color.blue());
	return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}

QColor MaterialColorHelper::contrastColorDuplicate(const QColor& baseColor, const float strength) {
	float h, s, l, a;
	baseColor.getHslF(&h, &s, &l, &a);
	l = (1.0 - l) * (0.5 + 0.5 * strength);
	s *= 0.6 + 0.4 * (1.0 - strength);
	QColor result;
	result.setHslF(h, s, l, a);
	return result;
}
}
