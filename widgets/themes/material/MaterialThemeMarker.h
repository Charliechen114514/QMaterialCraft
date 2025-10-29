#ifndef MATERIALTHEMEMARKER_H
#define MATERIALTHEMEMARKER_H
#include "Commons/ThemeMarker.h"

namespace CCWidgetLibrary {

class MaterialThemeMarker : public ThemeMarker {
public:
	QString style_name() const noexcept override {
		return "material";
	}
};
}

#endif // MATERIALTHEMEMARKER_H
