#include "toolbuttonpaintcontext.h"
#include <QToolButton>
CCWidgetLibrary::ToolButtonPaintContext::
    ToolButtonPaintContext(QToolButton* attached_button)
    : PaintContext(attached_button) {
}
