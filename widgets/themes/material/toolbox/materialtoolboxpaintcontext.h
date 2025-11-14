#ifndef MATERIALTOOLBOXPAINTCONTEXT_H
#define MATERIALTOOLBOXPAINTCONTEXT_H

#include "CCToolBox/toolboxpaintcontext.h"
class CCToolButton;
namespace CCWidgetLibrary {
class MaterialHeaderBar;
class MaterialToolBoxPaintContext : public ToolBoxPaintContext {
public:
	MaterialToolBoxPaintContext(QToolBox* toolbox);
	bool paint(QPainter& p) override;
	bool propertySettings(const QString property, const QVariant value) override;
	std::optional<QVariant> propertyGet(const QString property) override;
	void handleResizeEvent(const QResizeEvent* ev) override;

	int addItemAction(QWidget* widget, const QString& text) override;
	int addItemAction(QWidget* widget, const QIcon& icon, const QString& text) override;
	int insertItemAction(int index, QWidget* widget, const QString& text) override;
	int insertItemAction(int index, QWidget* widget, const QIcon& icon, const QString& text) override;
	void removeItemAction(int index) override;

	void setPrimaryColor(const QColor c);
	QColor primaryColor() const;

private slots:
	void onCurrentChanged(int idx);

private:
	void addHeaderButton(int idx, const QString& text, const QIcon& icon);
	void syncButtons();

private:
	QVector<QMetaObject::Connection> connections;
	QList<CCToolButton*> buttons;
	MaterialHeaderBar* header_bar;
};
}

#endif // MATERIALTOOLBOXPAINTCONTEXT_H
