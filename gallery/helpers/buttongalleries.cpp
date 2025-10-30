#include "buttongalleries.h"
#include "button.h"
#include "themes/material/MaterialPropertyString.h"
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

QWidget* Gallery::createButtonGalleryWidgets(QWidget* parent) {
	using namespace CCWidgetLibrary::MaterialProperty::Button::Style;
	QWidget* this_widget = new QWidget(parent);
	auto* root = new QVBoxLayout(this_widget);
	root->setContentsMargins(12, 12, 12, 12);
	root->setSpacing(10);

	auto* title = new QLabel("<h2>CCButton — Gallery</h2>");
	root->addWidget(title);

	// Global controls
	auto* ctrl = new QHBoxLayout;
	auto* disableAll = new QCheckBox("Disable all (except explicit Disabled)");
	ctrl->addWidget(disableAll);
	root->addLayout(ctrl);

	// Scroll area for many buttons
	auto* sa = new QScrollArea;
	sa->setWidgetResizable(true);
	auto* container = new QWidget;
	auto* grid = new QGridLayout(container);
	grid->setContentsMargins(8, 8, 8, 8);
	grid->setSpacing(12);

	// Helper to create CCButton and set dynamic properties only via public API.
	auto makeBtn = [&](const QString& text,
	                   const QString& variant = FLATED,
	                   const QString& size = QString(),
	                   const QIcon& icon = QIcon(),
	                   bool checkable = false,
	                   bool explicitlyDisabled = false) -> CCButton* {
		CCButton* b = new CCButton();
		b->setText(text);
		if (!icon.isNull())
			b->setIcon(icon);
		b->setCheckable(checkable);
		b->setEnabled(!explicitlyDisabled);

		if (variant == FLATED) {
			b->setStyle(FLATED);
		} else if (variant == OUTLINED) {
			b->setStyle(OUTLINED);
		}

		if (size.isEmpty() || size == "small")
			b->setFixedHeight(48);
		if (!size.isEmpty() && size == "large")
			b->setFixedHeight(68);
		b->setMinimumWidth(100);

		return b;
	};

	// Row: Primary
	CCButton* p1 = makeBtn("Primary");
	CCButton* p2 = makeBtn("Primary Icon", FLATED, QString(),
	                       this_widget->style()->standardIcon(QStyle::SP_DialogApplyButton));
	CCButton* p3 = makeBtn("", FLATED, QString(), this_widget->style()->standardIcon(QStyle::SP_DialogApplyButton));
	p3->setFixedSize(40, 40);

	grid->addWidget(new QLabel("Primary"), 0, 0);
	grid->addWidget(p1, 0, 1);
	grid->addWidget(p2, 0, 2);
	grid->addWidget(p3, 0, 3);

	// Row: Secondary
	CCButton* s1 = makeBtn("Secondary", FLATED);
	CCButton* s2 = makeBtn("Secondary Icon", FLATED, QString(),
	                       this_widget->style()->standardIcon(QStyle::SP_DialogHelpButton));
	CCButton* s3 = makeBtn("", FLATED, QString(), this_widget->style()->standardIcon(QStyle::SP_DialogApplyButton));
	s3->setFixedSize(40, 40);
	grid->addWidget(new QLabel("Secondary"), 1, 0);
	grid->addWidget(s1, 1, 1);
	grid->addWidget(s2, 1, 2);
	grid->addWidget(s3, 1, 3);

	// Row: Flat / Outlined
	CCButton* f1 = makeBtn(FLATED, FLATED);
	CCButton* o1 = makeBtn(OUTLINED, OUTLINED);
	grid->addWidget(new QLabel("Flat / Outlined"), 2, 0);
	grid->addWidget(f1, 2, 1);
	grid->addWidget(o1, 2, 2);

	// Row: Sizes
	CCButton* smallBtn = makeBtn("Small", FLATED, "small");
	CCButton* largeBtn = makeBtn("Large", FLATED, "large");
	grid->addWidget(new QLabel("Sizes"), 3, 0);
	grid->addWidget(smallBtn, 3, 1);
	grid->addWidget(largeBtn, 3, 2);

	// Row: Checkable
	CCButton* checkable = makeBtn("Toggle", FLATED, QString(), QIcon(), true);
	grid->addWidget(new QLabel("Checkable"), 4, 0);
	grid->addWidget(checkable, 4, 1);

	// Row: Explicit disabled example (kept disabled always)
	CCButton* disabled = makeBtn("Disabled", FLATED, QString(), QIcon(), false, true);
	grid->addWidget(new QLabel("Explicit Disabled"), 5, 0);
	grid->addWidget(disabled, 5, 1);

	// Keep list for toggling
	QList<CCButton*> allButtons = { p1, p2, p3, s1, s2, s3, f1, o1, smallBtn, largeBtn, checkable /*, disabled intentionally omitted */ };

	QObject::connect(disableAll, &QCheckBox::toggled, this_widget, [allButtons](bool on) {
		for (CCButton* b : allButtons) {
			b->setEnabled(!on);
		}
	});

	QList<CCButton*> colorSelections;
	colorSelections << allButtons << disabled;
	QObject::connect(p3, &QPushButton::clicked, this_widget, [colorSelections]() {
		QColor getTextColor = QColorDialog::getColor();
		if (!getTextColor.isValid()) {
			return;
		}

		for (CCButton* b : colorSelections) {
			b->setTextColor(getTextColor, true);
		}
	});

	QObject::connect(s3, &QPushButton::clicked, this_widget, [colorSelections]() {
		QColor getTextColor = QColorDialog::getColor();
		if (!getTextColor.isValid()) {
			return;
		}

		for (CCButton* b : colorSelections) {
			b->setBackGroundColor(getTextColor, true);
		}
	});

	sa->setWidget(container);
	root->addWidget(sa, /*stretch*/ 1);

	// footer
	auto* footer = new QLabel("this_widget gallery only uses CCButton's public API (setText, setIcon, setEnabled, setCheckable, setProperty, etc.).");
	root->addWidget(footer);

	return this_widget;
}
