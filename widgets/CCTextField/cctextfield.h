#ifndef CCTEXTFIELD_H
#define CCTEXTFIELD_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QWidget>
class QLineEdit;
class QTextEdit;
class QValidator;
class CCLabel;
namespace CCWidgetLibrary {
class CCTextFieldPaintContext;
}

CONTEXT_PAINT_PREANNOUNCE;

namespace CCWidgetLibrary {
class CCTextFieldPaintContext;
}

class CCWIDGET_EXPORT CCTextField : public QWidget {
	Q_OBJECT
public:
	friend class CCWidgetLibrary::CCTextFieldPaintContext;
	static constexpr const char* WIDGET_NAME = "textfield";
	explicit CCTextField(QWidget* parent = nullptr);

	void setMultiline(bool multiline);
	bool isMultiline() const { return multiline_; }

	void setPlaceholderText(const QString& text);
	void setFloatingLabelText(const QString& text);
	QString placeHolderText() const;
	QString floatingLabelText() const;

	void setPasswordMode(bool on);
	void setClearButtonEnabled(bool enabled);

	using ValidationCallBack = std::function<bool(const QString&)>;
	void setValidator(QValidator* validator);
	void setValidationCallback(ValidationCallBack cb);

	QString text() const;
	void setText(const QString& text);
	QString errorText() const;
	void setErrorText(const QString& newErrorText);
	void clearError();
	void validateAndUpdate();

	bool errorOccured() const;

signals:
	void textChanged(const QString& text);
	void editingFinished();
	void validationFailed(const QString& reason);

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE;
	QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;
private slots:
	void onClearClicked();
	void onVisibilityToggled();
	void onInternalTextChanged(const QString& text);
	void onEditingFinished();

private:
	QLineEdit* lineEdit;
	QTextEdit* textEdit;
	CCLabel* floatingLabel;
	CCLabel* helperLabel;
	QToolButton* clearBtn;
	QToolButton* visibilityBtn;

	QValidator* validator_ = nullptr;
	ValidationCallBack validationCb_;
	QString errorText_;
	bool errorOccured_ { false };
	bool multiline_ { false };
	bool clearEnabled_ { true };

private:
	CCWidgetLibrary::CCTextFieldPaintContext* paintContext;

private:
	void updateButtons();
	void internal_setError();
};

#endif // CCTEXTFIELD_H
