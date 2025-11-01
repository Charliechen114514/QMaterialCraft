#include "cctextfield.h"
#include "CCTextField/cctextfieldpaintcontext.h"
#include "cclabel.h"
#include "paintcontextallocator.h"
#include <QLineEdit>
#include <QPainter>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QValidator>
CONTEXT_PAINT_IMPL(CCTextField, QWidget);
CONTEXT_RESIZE_IMPL(CCTextField);

CCTextField::CCTextField(QWidget* parent)
    : QWidget { parent } {

	// --- 创建控件 ---
	lineEdit = new QLineEdit(this);
	textEdit = new QTextEdit(this);

	floatingLabel = new CCLabel(this);
	helperLabel = new CCLabel(this);

	clearBtn = new QToolButton(this);
	clearBtn->setText("✕");
	clearBtn->setCursor(Qt::PointingHandCursor);
	clearBtn->setToolTip(QStringLiteral("Clear"));
	clearBtn->setVisible(false);

	visibilityBtn = new QToolButton(this);
	visibilityBtn->setText("👁");
	visibilityBtn->setCursor(Qt::PointingHandCursor);
	visibilityBtn->setToolTip(QStringLiteral("Toggle visibility"));
	visibilityBtn->setVisible(false);

	connect(clearBtn, &QToolButton::clicked, this, &CCTextField::onClearClicked);
	connect(visibilityBtn, &QToolButton::clicked, this, &CCTextField::onVisibilityToggled);
	connect(lineEdit, &QLineEdit::textChanged, this, &CCTextField::onInternalTextChanged);
	connect(lineEdit, &QLineEdit::editingFinished, this, &CCTextField::onEditingFinished);
	connect(textEdit, &QTextEdit::textChanged, this, [this]() {
		onInternalTextChanged(textEdit->toPlainText());
	});

	// auto inputLayout = new QHBoxLayout();
	// inputLayout->setContentsMargins(0, 0, 0, 0);
	// inputLayout->setSpacing(4);
	// inputLayout->addWidget(lineEdit);
	// inputLayout->addWidget(textEdit);
	// inputLayout->addWidget(clearBtn);
	// inputLayout->addWidget(visibilityBtn);

	// // --- 整体布局 ---
	// auto mainLayout = new QVBoxLayout(this);
	// mainLayout->setContentsMargins(4, 8, 4, 4);
	// mainLayout->setSpacing(2);
	// // mainLayout->addWidget(floatingLabel);
	// mainLayout->addLayout(inputLayout);
	// mainLayout->addWidget(helperLabel);

	// setLayout(mainLayout);

	// --- PaintContext ---
	paintContext = dynamic_cast<CCWidgetLibrary::CCTextFieldPaintContext*>(
	    CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext(
	        WIDGET_NAME, this));
	if (!paintContext) {
		qWarning() << "failed to allocate the paintContext";
	}

	setMultiline(multiline_);
}

void CCTextField::onEditingFinished() {
	emit editingFinished();
	validateAndUpdate();
}

void CCTextField::setMultiline(bool multiline) {
	if (multiline_ == multiline)
		return;
	multiline_ = multiline;
	lineEdit->setVisible(!multiline_);
	textEdit->setVisible(multiline_);
	updateButtons();
	update();
}

void CCTextField::setPlaceholderText(const QString& text) {
	if (multiline_) {
		setFloatingLabelText(text);
	} else {
		lineEdit->setPlaceholderText(text);
	}
}

void CCTextField::setFloatingLabelText(const QString& text) {
	floatingLabel->setText(text);
	paintContext->animateFloatingLabel(false);
}

QString CCTextField::placeHolderText() const {
	return lineEdit->placeholderText();
}

QString CCTextField::floatingLabelText() const {
	return floatingLabel->text();
}

void CCTextField::setPasswordMode(bool on) {
	if (on) {
		lineEdit->setEchoMode(QLineEdit::Password);
		visibilityBtn->setVisible(true);
	} else {
		lineEdit->setEchoMode(QLineEdit::Normal);
		visibilityBtn->setVisible(false);
	}
	updateButtons();
}

void CCTextField::setClearButtonEnabled(bool enabled) {
	clearEnabled_ = enabled;
	updateButtons();
}

void CCTextField::setValidator(QValidator* v) {
	validator_ = v;
}
void CCTextField::setValidationCallback(std::function<bool(const QString&)> cb) {
	validationCb_ = std::move(cb);
}

QString CCTextField::text() const {
	return multiline_ ? textEdit->toPlainText() : lineEdit->text();
}

void CCTextField::setText(const QString& text) {
	if (multiline_)
		textEdit->setPlainText(text);
	else
		lineEdit->setText(text);
	onInternalTextChanged(text);
}

QString CCTextField::errorText() const {
	return errorText_;
}

void CCTextField::setErrorText(const QString& newErrorText) {
	errorText_ = newErrorText;
}

void CCTextField::internal_setError() {
	errorOccured_ = true;
	helperLabel->setText(errorText_);
	paintContext->animate_error();
	// animate underline to error state
	paintContext->animateUnderLine(true);
}

void CCTextField::validateAndUpdate() {
	const QString cur = text();
	bool ok = true;
	if (validator_) {
		int pos = 0;
		QValidator::State st = validator_->validate(const_cast<QString&>(cur), pos);
		ok = (st == QValidator::Acceptable);
	}
	if (ok && validationCb_)
		ok = validationCb_(cur);
	if (!ok) {
		internal_setError();
		emit validationFailed(errorText_);
	} else {
		clearError();
	}
}

bool CCTextField::errorOccured() const {
	return errorOccured_;
}

QVariant CCTextField::inputMethodQuery(Qt::InputMethodQuery query) const {
	if (query == Qt::ImCursorRectangle) {
		if (!lineEdit->isVisible())
			return QRect();

		int pos = lineEdit->cursorPosition();
		QFontMetrics fm(lineEdit->font());
		QString text = lineEdit->text().left(pos);
		int x = fm.horizontalAdvance(text);
		int y = 0;
		int height = fm.height();

		QRect cursorRect(x, y, 1, height);
		QPoint mappedPos = lineEdit->mapTo(this, cursorRect.topLeft());
		return QRect(mappedPos, cursorRect.size());
	}
	return QWidget::inputMethodQuery(query);
}

void CCTextField::clearError() {
	errorOccured_ = false;
	helperLabel->setVisible(false);
	paintContext->animateUnderLine(true);
}

void CCTextField::onClearClicked() {
	if (multiline_)
		textEdit->clear();
	else
		lineEdit->clear();
}

void CCTextField::onVisibilityToggled() {
	if (lineEdit->echoMode() == QLineEdit::Password) {
		lineEdit->setEchoMode(QLineEdit::Normal);
	} else {
		lineEdit->setEchoMode(QLineEdit::Password);
	}
}

void CCTextField::onInternalTextChanged(const QString& text) {
	emit textChanged(text);
	updateButtons();
	validateAndUpdate();
	paintContext->animateFloatingLabel(true);
}

void CCTextField::updateButtons() {
	bool hasText = !text().isEmpty();
	clearBtn->setVisible(clearEnabled_ && hasText);
	visibilityBtn->setVisible(lineEdit->isVisible() && lineEdit->echoMode() == QLineEdit::Password);
}
