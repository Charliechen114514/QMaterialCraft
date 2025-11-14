#include "toolbuttongallery.h"
#include "CCToolButton/cctoolbutton.h"
#include <QHBoxLayout>
#include <QStyle>
#include <QWidget>
QWidget* Gallery::createToolButtonGalleryWidgets(QWidget* parent) {
	QWidget* root = new QWidget(parent);

	auto* v = new QHBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);

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

	for (const auto& info : items) {
		CCToolButton* btn = new CCToolButton(root);
		btn->setText(info.text);

		// 使用系统默认图标
		QIcon icon = root->style()->standardIcon(info.icon);
		btn->setIcon(icon);

		btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		btn->setIconSize(QSize(48, 48)); // 你可以改小改大
		btn->setCheckable(false);

		// 推荐大小（Material gallery 风格）
		btn->setMinimumSize(96, 96);
		btn->setMaximumWidth(96);

		v->addWidget(btn);
	}

	return root;
}
