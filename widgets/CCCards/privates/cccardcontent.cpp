#include "cccardcontent.h"
#include "paintcontextallocator.h"
#include <QLabel>
#include <QLayout>

CCCardContent::CCCardContent(QWidget* parent)
    : QWidget { parent } {
	contextLabel = new QLabel(this);
	helpers = new WidgetLayoutHelper(this);
	helpers->layout()->addWidget(contextLabel);
}

void CCCardContent::setContentTitle(const QString& title,
                                    CCWidgetLibrary::TextStyle style) {
	CCWidgetLibrary::TextIndiator* indicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();
	indicator->applyTo(contextLabel, style);
	contextLabel->setText(title);
}

void CCCardContent::setContentTitleVisible(bool visible) {
	contextLabel->setVisible(visible);
}

bool CCCardContent::contentTitleVisible() const {
	return contextLabel->isVisible();
}

QWidget* CCCardContent::getContentWidget() const {
	return contentWidget;
}

void CCCardContent::setContentWidget(QWidget* newContentWidget) {
	if (contentWidget == newContentWidget)
		return;

	helpers->layout()->removeWidget(contentWidget);
	contentWidget = newContentWidget;
	helpers->layout()->addWidget(contentWidget);
	emit contentWidgetChanged(newContentWidget);
	update();
}
