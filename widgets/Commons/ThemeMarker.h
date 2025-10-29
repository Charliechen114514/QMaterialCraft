#ifndef THEMEMARKER_H
#define THEMEMARKER_H
#include <QString>
namespace CCWidgetLibrary {

class ThemeMarker {
public:
	virtual ~ThemeMarker() = default;
	virtual QString style_name() const noexcept = 0;
};

}

#endif // THEMEMARKER_H
