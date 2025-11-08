#ifndef MATERIALPROPERTYSTRING_H
#define MATERIALPROPERTYSTRING_H

#include "property_string.h"

namespace CCWidgetLibrary {

namespace MaterialProperty {
	namespace Button {
		namespace Style {
			static constexpr const char* STYLE = CCWidgetLibrary::Commons::STYLE;
			static constexpr const char* FLATED = "flated";
			static constexpr const char* OUTLINED = "outlined";
		}

		namespace Border {
			static constexpr const char* BORDERCOLOR = "border-color";
			static constexpr const char* BORDERWIDTH = "border-width";
			// should pass QColor or int as result
		}
	}

	namespace ImageWidget {
		namespace StyleColor {
			static constexpr const char* COLORA = CCImageWidget::COLORA;
			static constexpr const char* COLORB = CCImageWidget::COLORB;
		}
	}
}
}

#endif // MATERIALPROPERTYSTRING_H
