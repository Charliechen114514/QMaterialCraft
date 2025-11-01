#include "cctextfieldpaintcontext.h"
#include "cctextfield.h"

namespace CCWidgetLibrary {

CCTextFieldPaintContext::CCTextFieldPaintContext(CCTextField* attached_widget)
    : PaintContext(attached_widget) {
	internal_package.textEdit = attached_widget->textEdit;
	internal_package.lineEdit = attached_widget->lineEdit;
	internal_package.floatingLabel = attached_widget->floatingLabel;
	internal_package.helperLabel = attached_widget->helperLabel;
	internal_package.clearBtn = attached_widget->clearBtn;
	internal_package.visibilityBtn = attached_widget->visibilityBtn;
}
}
