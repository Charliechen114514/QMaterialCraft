#include "tree_wv_gallery.h"
#include "Composers/CCTreeView/cctreeview.h"
#include "Composers/CCTreeWidget/cctreewidget.h"
#include <QStandardItemModel>
#include <QVBoxLayout>

QWidget* Gallery::createTreeViewWidgetGallery(QWidget* parent) {
	QWidget* win = new QWidget(parent);
	QVBoxLayout* layout = new QVBoxLayout(win);
	auto* tree = new CCTreeWidget(win);
	tree->setHeaderHidden(false);
	tree->setHeaderLabel("Row");
	tree->setColumnCount(1);
	for (int i = 0; i < 4; ++i) {
		auto* top = new QTreeWidgetItem(tree);
		top->setText(0, QString("Item %1").arg(i + 1));
		top->setCheckState(0, Qt::Unchecked);
		for (int j = 0; j < 3; ++j) {
			auto* child = new QTreeWidgetItem(top);
			child->setText(0, QString("Child %1.%2").arg(i + 1).arg(j + 1));
			child->setFlags(child->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
			child->setCheckState(0, Qt::Unchecked);
		}
	}

	auto* view = new CCTreeView;
	auto* model = new QStandardItemModel;
	model->setHorizontalHeaderLabels({ "Column" });
	for (int i = 0; i < 4; ++i) {
		QStandardItem* it = new QStandardItem(QString("Row %1").arg(i + 1));
		it->setFlags(it->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
		it->setCheckable(true);
		it->setIcon(QIcon::fromTheme("folder"));
		for (int j = 0; j < 2; ++j) {
			QStandardItem* c = new QStandardItem(QString("Row %1.%2").arg(i + 1).arg(j + 1));
			c->setFlags(c->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
			c->setCheckable(true);
			it->appendRow(c);
		}
		model->appendRow(it);
	}
	view->setModel(model);
	view->expandAll();

	// Pack into UI
	layout->addWidget(tree);
	layout->addWidget(view);

	return win;
}
