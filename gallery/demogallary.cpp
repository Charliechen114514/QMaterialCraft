#include "demogallary.h"
#include "./ui_demogallary.h"
#include "helpers/demogallerytabhelper.h"

DemoGallary::DemoGallary(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DemoGallary) {
	ui->setupUi(this);
	tabHelpers = new DemoGalleryTabHelper(ui->tabWidget);
	tabHelpers->init();
}

DemoGallary::~DemoGallary() {
	delete ui;
}
