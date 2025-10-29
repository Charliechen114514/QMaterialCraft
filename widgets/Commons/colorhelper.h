#ifndef COLORHELPER_H
#define COLORHELPER_H
#include <QColor>

namespace CCWidgetLibrary {

class ColorHelper {
public:
	ColorHelper() = default;
	virtual ~ColorHelper() = default;
	/**
	 * @brief interfaces expected to calculate the contrast color
	 * @param baseColor the base
	 * @return the contrast color
	 */
	virtual QColor contrastColorSimple(const QColor& baseColor) = 0;

	virtual QColor contrastColorDuplicate(const QColor& baseColor, const float strength);

	/**
	 * @brief harmonizeColor get the same color
	 * @param base
	 * @param lightnessFactor
	 * @param saturationFactor
	 * @return
	 */
	virtual QColor harmonizeColor(const QColor& base,
	                              double lightnessFactor,
	                              double saturationFactor)
	    = 0;

	/**
	 * @brief relative luminance calculator
	 * @param color expected to calculate in different color helpers
	 * @return luminance
	 */
	virtual double luminance(const QColor& color) = 0;
};

};

#endif // COLORHELPER_H
