#ifndef DEMOGALLERYTABHELPER_H
#define DEMOGALLERYTABHELPER_H
#include <QObject>
class QTabWidget;

class DemoGalleryTabHelper : public QObject {
	Q_OBJECT
public:
	explicit DemoGalleryTabHelper(QTabWidget* parent = nullptr);
	using WidgetGalleryInfo = std::pair<QWidget*, std::string_view>;
	using WidgetGalleryRegistry = std::function<WidgetGalleryInfo()>;
	void addRegistries(WidgetGalleryRegistry register_func);
	void init();

signals:
private:
private:
	QTabWidget* attached_tabwidget;
	QList<WidgetGalleryRegistry> registries;
};

#endif // DEMOGALLERYTABHELPER_H
