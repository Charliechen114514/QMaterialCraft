#ifndef DEMOGALLARY_H
#define DEMOGALLARY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DemoGallary;
}
QT_END_NAMESPACE

class DemoGallary : public QMainWindow {
	Q_OBJECT

public:
	DemoGallary(QWidget* parent = nullptr);
	~DemoGallary();

private:
	Ui::DemoGallary* ui;
};
#endif // DEMOGALLARY_H
