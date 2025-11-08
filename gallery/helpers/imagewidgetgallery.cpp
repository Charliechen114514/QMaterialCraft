#include "imagewidgetgallery.h"
#include "CCImageWidget/ccimagewidget.h"
#include "button.h"
#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QWidget>

QWidget* Gallery::createImageWidgetGallery(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QHBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCImageWidget* image = new CCImageWidget(root);

	v->addWidget(image);

	auto v2 = new QVBoxLayout;

	auto btn_applier = [root, v2](const QString& text) {
		CCButton* button = new CCButton(root);
		button->setMaximumWidth(100);
		button->setText(text);
		v2->addWidget(button);
		return button;
	};

	QComboBox* combo = new QComboBox(root);
	combo->addItems({ "Contain", "Cover", "Stretch" });
	v2->addWidget(combo);
	QObject::connect(combo, &QComboBox::textActivated,
	                 root, [image](const QString& t) {
		                 if (t == "Contain") {
			                 image->setScale_mode(CCImageWidget::Contain);
		                 } else if (t == "Cover") {
			                 image->setScale_mode(CCImageWidget::Cover);
		                 } else {
			                 image->setScale_mode(CCImageWidget::Stretch);
		                 }
	                 });

	CCButton* image_button = btn_applier("Select Image");
	CCButton* colorA_btn = btn_applier("ColorA");
	CCButton* colorB_btn = btn_applier("ColorB");

	QObject::connect(colorA_btn, &QPushButton::clicked,
	                 root, [image]() {
		                 QColor getTextColor = QColorDialog::getColor();
		                 if (!getTextColor.isValid()) {
			                 return;
		                 }
		                 image->setEmptyImage({ getTextColor, image->emptyWhenColor().colorB });
	                 });

	QObject::connect(colorB_btn, &QPushButton::clicked,
	                 root, [image]() {
		                 QColor getTextColor = QColorDialog::getColor();
		                 if (!getTextColor.isValid()) {
			                 return;
		                 }
		                 image->setEmptyImage({ image->emptyWhenColor().colorA, getTextColor });
	                 });
	v->addLayout(v2);

	QObject::connect(image_button, &CCButton::clicked, root, [image]() {
		QString filePath = QFileDialog::getOpenFileName(
		    image,
		    QObject::tr("Select Image"),
		    QString(),
		    QObject::tr("Image (*.png *.jpg *.jpeg *.bmp *.gif)"));

		if (!filePath.isEmpty()) {
			QPixmap pix(filePath);
			if (!pix.isNull()) {
				image->setPixmap(pix);
			}
		}
	});

	return root;
}
