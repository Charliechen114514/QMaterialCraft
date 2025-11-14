#include "toolboxgallery.h"
#include "CCToolBox/cctoolbox.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QWidget>

QWidget* Gallery::createToolBoxGalleryWidgets(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QHBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

	CCToolBox* toolbox = new CCToolBox(root);

	struct ItemInfo {
		QString text;
		QStyle::StandardPixmap icon;
	};

	QVector<ItemInfo> items = {
		{ "Open", QStyle::SP_DialogOpenButton },
		{ "Save", QStyle::SP_DialogSaveButton },
		{ "Dir", QStyle::SP_DirIcon },
		{ "File", QStyle::SP_FileIcon },
		{ "Trash", QStyle::SP_TrashIcon },
		{ "Computer", QStyle::SP_ComputerIcon }
	};
	int i = 0;
	for (const auto& item : items) {
		QWidget* page = new QWidget();
		QVBoxLayout* v = new QVBoxLayout(page);
		QLabel* label = new QLabel(QString("内容页 %1").arg(i));
		label->setAlignment(Qt::AlignCenter);
		v->addWidget(label);
		toolbox->addItem(page, root->style()->standardIcon(item.icon), QString("部分 %1").arg(items[i].text));
		i++;
	}
	v->addWidget(toolbox);
	return root;
}
