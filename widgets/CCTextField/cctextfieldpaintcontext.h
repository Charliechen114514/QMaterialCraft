#ifndef CCTEXTFIELDPAINTCONTEXT_H
#define CCTEXTFIELDPAINTCONTEXT_H

#include <paintcontext.h>

class QLineEdit;
class QTextEdit;
class QToolButton;
class CCTextField;
class CCLabel;

namespace CCWidgetLibrary {

class CCTextFieldPaintContext : public PaintContext {
public:
	explicit CCTextFieldPaintContext(CCTextField* attached_widget = nullptr);
	struct TextFieldInternalPackage {
		QLineEdit* lineEdit;
		QTextEdit* textEdit;
		CCLabel* floatingLabel;
		CCLabel* helperLabel;
		QToolButton* clearBtn;
		QToolButton* visibilityBtn;
	};

	virtual void animateFloatingLabel(bool requestAnimate = true) = 0;
	virtual void animateUnderLine(bool requestAnimate = true) = 0;

	virtual void setErrorColor(const QColor& c) = 0;
	virtual QColor errorColor() const = 0;

	virtual void animate_error() = 0;

protected:
	TextFieldInternalPackage internal_package;
};
}

#endif // CCTEXTFIELDPAINTCONTEXT_H
