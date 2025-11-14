#ifndef MATERIALHEADERBAR_H
#define MATERIALHEADERBAR_H

#include "CCToolButton/cctoolbutton.h"
#include <QWidget>
class QHBoxLayout;

namespace CCWidgetLibrary {
class AnimationHolder;

class IndicatorWidget : public QWidget {
	Q_OBJECT
public:
	explicit IndicatorWidget(QWidget* parent = nullptr);
	QColor primaryColor() const { return pri; }
	void setPrimaryColor(const QColor c);
	void setRadius(int radius);

	int getRadius() const;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	int radius { 2 };
	QColor pri { 0x42a5f5 };
};

class MaterialHeaderBar : public QWidget {
	Q_OBJECT
public:
	explicit MaterialHeaderBar(QWidget* parent = nullptr);
	void addButton(CCToolButton* toolButton);
	CCToolButton* buttonAt(int index) const;
	int count() const;
	IndicatorWidget* indicator_widgets() const { return indicator; };
	void moveIndicatorUnder(CCToolButton* btn, bool animate = true);

protected:
	void resizeEvent(QResizeEvent* ev) override;

private:
	QHBoxLayout* buttonsLayouts;
	IndicatorWidget* indicator;
	AnimationHolder* geometry_animation;
	QList<CCToolButton*> toolButtons;
};
}

#endif // MATERIALHEADERBAR_H
