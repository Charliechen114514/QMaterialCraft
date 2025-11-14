#ifndef TOOLBUTTONPAINTCONTEXT_H
#define TOOLBUTTONPAINTCONTEXT_H

#include <paintcontext.h>
class QToolButton;
namespace CCWidgetLibrary {
class ToolButtonPaintContext : public PaintContext {
public:
	ToolButtonPaintContext(QToolButton* attached_button);
};
}

#endif // TOOLBUTTONPAINTCONTEXT_H
