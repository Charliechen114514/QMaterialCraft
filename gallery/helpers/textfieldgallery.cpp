#include "textfieldgallery.h"
#include "CCTextField/cctextfield.h"
#include <QIntValidator>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
QWidget* Gallery::createTextFieldGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCTextField* user = new CCTextField(root);
	user->setFloatingLabelText(QStringLiteral("用户名"));
	user->setPlaceholderText(QStringLiteral("请输入用户名"));
	user->setClearButtonEnabled(true);
	v->addWidget(user);

	CCTextField* password = new CCTextField(root);
	password->setFloatingLabelText(QStringLiteral("密码"));
	password->setPasswordMode(true);
	password->setClearButtonEnabled(false);
	v->addWidget(password);

	CCTextField* note = new CCTextField(root);
	note->setMultiline(true);
	note->setFloatingLabelText(QStringLiteral("备注"));
	note->setPlaceholderText(QStringLiteral("请填写备注..."));
	v->addWidget(note);

	auto* textField = new CCTextField(root);
	textField->setGeometry(50, 50, 300, 50);
	textField->setFloatingLabelText("请输入数字");
	textField->setClearButtonEnabled(true);
	QIntValidator* validator = new QIntValidator(0, 999, textField);
	textField->setValidator(validator);
	textField->setErrorText("Submit A number between 0 and 999!");
	v->addWidget(textField);
	textField->setValidationCallback([](const QString& input) -> bool {
		bool ok;
		int val = input.toInt(&ok);
		return ok && val >= 0 && val <= 999;
	});

	QObject::connect(textField, &CCTextField::validationFailed, [](const QString& reason) {
		qDebug() << "Validation failed:" << reason;
	});

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* cardGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(cardGallery);
	mainLayout->addWidget(sc);

	return cardGallery;
}
