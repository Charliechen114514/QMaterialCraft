#include "demogallary.h"
#include "./ui_demogallary.h"
#include "slider.h"

DemoGallary::DemoGallary(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DemoGallary) {
	ui->setupUi(this);

	ui->widget->setMinimumHeight(40);
	ui->widget->setMinimum(0);
	ui->widget->setMaximum(100);
	ui->widget->setValue(50);

	ui->btn_widget->setMinimumHeight(100);
	ui->btn_widget->setMinimumWidth(200);
	ui->btn_widget->setText("Hello Button!");
	auto fonts = ui->btn_widget->font();
	fonts.setPixelSize(24);
	ui->btn_widget->setFont(fonts);
}

DemoGallary::~DemoGallary() {
	delete ui;
}
