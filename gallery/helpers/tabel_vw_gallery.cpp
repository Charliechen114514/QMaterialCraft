#include "tabel_vw_gallery.h"
#include "Composers/CCTableView/cctableview.h"
#include "Composers/CCTableWidget/cctablewidget.h"
#include <QStandardItem>
#include <QVBoxLayout>

QWidget* Gallery::createTableViewWidgetGallery(QWidget* parent) {
	QWidget* win = new QWidget(parent);
	QVBoxLayout* layout = new QVBoxLayout(win);

	// TableWidget
	auto* tw = new CCTableWidget(win);
	tw->setColumnCount(3);
	tw->setRowCount(3);
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			QTableWidgetItem* it = new QTableWidgetItem(QString("TW R%1C%2").arg(r + 1).arg(c + 1));
			it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
			it->setCheckState(Qt::Unchecked);
			tw->setItem(r, c, it);
		}
	}

	// TableView + model
	auto* tv = new CCTableView(win);
	QStandardItemModel* tableModel = new QStandardItemModel(3, 3);
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			QStandardItem* it = new QStandardItem(QString("TV R%1C%2").arg(r + 1).arg(c + 1));
			it->setFlags(it->flags() | Qt::ItemIsEditable | Qt::ItemIsUserCheckable);
			it->setCheckable(true);
			it->setCheckState(Qt::Unchecked);
			tableModel->setItem(r, c, it);
		}
	}
	tv->setModel(tableModel);

	// Pack into UI
	layout->addWidget(tw);
	layout->addWidget(tv);

	return win;
}
