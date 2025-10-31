#include "cccardheader.h"
#include "ccbadgelabel.h"
#include "cclabel.h"
#include "paintcontext.h"

#include <QVBoxLayout>

CCCardHeader::CCCardHeader(QWidget* parent)
    : QWidget { parent } {
	QHBoxLayout* v = new QHBoxLayout(this);
	v->setContentsMargins(16, 8, 16, 8);
	v->setSpacing(0);
	v->setAlignment(Qt::AlignCenter);
	setLayout(v);
	CCCardHeader::initNativeWidget();
}

void CCCardHeader::setHeaderRoleWidget(const HeaderRole role, QWidget* widget) {
	auto w = widgets.value(role);

	if (w) {
		widgets.remove(role);
		w->hide();
		layout()->replaceWidget(w, widget);
	} else {
		layout()->addWidget(widget);
	}

	widgets.insert(role, widget);

	emit roleWidgetChanged(role, widget);
}

QWidget* CCCardHeader::roleWidget(const HeaderRole role) const {
	return widgets.value(role, nullptr);
}

void CCCardHeader::resumeNativeWidgets() {
	setHeaderRoleWidget(HeaderRole::TITLE, nativeTitleWidget);
	setHeaderRoleWidget(HeaderRole::SUBTITLE, nativeSubTitleWidget);
}

void CCCardHeader::initNativeWidget() {
	nativeSubTitleWidget = new CCBadgeLabel(this);
	nativeTitleWidget = new CCLabel(this);
	nativeSubTitleWidget->setTextStyle(CCWidgetLibrary::TextStyle::BodyMedium);
	nativeTitleWidget->setTextStyle(CCWidgetLibrary::TextStyle::TitleLarge);
	resumeNativeWidgets();
}
