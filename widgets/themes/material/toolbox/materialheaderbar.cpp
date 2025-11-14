#include "materialheaderbar.h"
#include "animation_helpers.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace CCWidgetLibrary {

IndicatorWidget::IndicatorWidget(QWidget* parent)
    : QWidget(parent) {
	setAttribute(Qt::WA_TranslucentBackground);
}

void IndicatorWidget::setPrimaryColor(const QColor c) {
	pri = c;
	update();
}

void IndicatorWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	QLinearGradient gradient(0, 0, width(), 0);
	gradient.setColorAt(0.0, pri);
	gradient.setColorAt(1.0, pri.darker(120));
	QPainterPath path;
	path.addRoundedRect(rect(), radius, radius);

	painter.fillPath(path, gradient);
}

int IndicatorWidget::getRadius() const {
	return radius;
}

MaterialHeaderBar::MaterialHeaderBar(QWidget* parent)
    : QWidget { parent } {
	buttonsLayouts = new QHBoxLayout(this);
	buttonsLayouts->setContentsMargins(4, 3, 4, 5);
	buttonsLayouts->setSpacing(6);
	buttonsLayouts->addStretch();
	indicator = new IndicatorWidget(this);
	indicator->setFixedHeight(3);
	indicator->raise();

	geometry_animation = new AnimationHolder(indicator, "geometry");

	geometry_animation->get_helpers()->applySettings([](AnimationHelper::SettingsConfig& config) {
		config.curve = QEasingCurve::OutCubic;
		config.period_time = 240;
	});
}

void MaterialHeaderBar::addButton(CCToolButton* toolButton) {
	buttonsLayouts->insertWidget(buttonsLayouts->count() - 1, toolButton);
	toolButtons.push_back(toolButton);
	toolButton->show();
}

CCToolButton* MaterialHeaderBar::buttonAt(int index) const {
	return toolButtons.at(index);
}

int MaterialHeaderBar::count() const {
	return int(toolButtons.size());
}

void MaterialHeaderBar::moveIndicatorUnder(CCToolButton* btn,
                                           bool animate) {
	QRect btnRect = btn->geometry();
	int margin = indicator->getRadius();
	QRect target(btnRect.left() + margin,
	             height() - indicator->height(),
	             btnRect.width() - margin * 2,
	             indicator->height());
	if (animate) {
		geometry_animation->get_helpers()->applySession(
		    [this, target](AnimationHelper::RuntimeConfig& conf) {
			    conf.start = indicator->geometry();
			    conf.end = target;
		    });
	} else {
		indicator->setGeometry(target);
	}
}

void MaterialHeaderBar::resizeEvent(QResizeEvent* ev) {
	QWidget::resizeEvent(ev);
	for (auto* b : std::as_const(toolButtons)) {
		if (b->isChecked()) {
			moveIndicatorUnder(b, false);
			break;
		}
	}
}
}
