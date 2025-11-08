#include "imagewidgetgallery.h"
#include "CCImageWidget/ccimagewidget.h"
#include "button.h"
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
	CCButton* button = new CCButton(root);
	button->setFixedSize(20, 20);
	v->addWidget(button);

	QObject::connect(button, &CCButton::clicked, root, [image]() {
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
