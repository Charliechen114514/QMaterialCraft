#ifndef WIDGETLAYOUTHELPER_H
#define WIDGETLAYOUTHELPER_H
#include <QObject>
class QWidget;
class QLayout;

class WidgetLayoutHelper : public QObject {
	Q_OBJECT
	Q_PROPERTY(LayoutDirection direction READ getDirection
	               WRITE setDirection NOTIFY directionChanged FINAL)
public:
	explicit WidgetLayoutHelper(QWidget* parent = nullptr);

	enum class LayoutDirection {
		Horizontal,
		Vertical
	};

	LayoutDirection getDirection() const;
	void setDirection(LayoutDirection newDirection);

	QLayout* layout() const;

signals:
	void directionChanged(LayoutDirection newDirection);

protected:
	void adjustLayouts();

protected:
	QWidget* attachedWidget;
	QLayout* holdingLayout;
	LayoutDirection direction { LayoutDirection::Vertical };
};

#endif // WIDGETLAYOUTHELPER_H
