#include "list_vw_gallery.h"
#include "Composers/CCListView/cclistview.h"
#include "Composers/CCListWidget/cclistwidget.h"
#include <QStandardItemModel>
#include <QVBoxLayout>
QWidget* Gallery::createListViewWidgetGallery(QWidget* parent) {
	QWidget* win = new QWidget(parent);
	QVBoxLayout* layout = new QVBoxLayout(win);

	// ListWidget
	auto* lw = new CCListWidget(win);
	for (int i = 0; i < 6; ++i) {
		QListWidgetItem* it = new QListWidgetItem(QString("LW %1").arg(i + 1));
		it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
		it->setCheckState(Qt::Unchecked);
		lw->addItem(it);
	}

	// ListView + model
	auto* lv = new CCListView(win);
	QStandardItemModel* listModel = new QStandardItemModel;
	for (int i = 0; i < 6; ++i) {
		QStandardItem* it = new QStandardItem(QString("LV %1").arg(i + 1));
		it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
		it->setCheckable(true);
		it->setCheckState(Qt::Unchecked);
		listModel->appendRow(it);
	}
	lv->setModel(listModel);

	// Pack into UI
	layout->addWidget(lw);
	layout->addWidget(lv);

	return win;
}
