#include "cccard.h"
#include "paintcontextallocator.h"
#include "privates/cccardactions.h"
#include "privates/cccardcontent.h"
#include "privates/cccardheader.h"
#include <QEnterEvent>
#include <QPainter>
#include <QVBoxLayout>

CONTEXT_HOVER_IMPL(CCCard);
CONTEXT_MOUSE_IMPL(CCCard);
CONTEXT_PAINT_IMPL(CCCard, QWidget)

CCCard::CCCard(QWidget* parent) {
	ALLOCATE_PAINTCONTEXT();
	setAttribute(Qt::WA_Hover);
	setMouseTracking(true);
	setContentsMargins(0, 0, 0, 0);

	auto layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setAlignment(Qt::AlignCenter);
	header_ = new CCCardHeader(this);
	content_ = new CCCardContent(this);
	actions_ = new CCCardActions(this);
	layout->addStretch();
	layout->addWidget(header_);
	layout->addWidget(content_);
	layout->addWidget(actions_);
	layout->addStretch();
}

void CCCard::applyHeaders(ApplierSession s) {
	if (!header_) {
		s(nullptr);
		return;
	}

	s(header_->roleWidget(CCCardHeader::HeaderRole::TITLE));
}

void CCCard::applySubHeaders(ApplierSession s) {
	if (!header_) {
		s(nullptr);
		return;
	}

	s(header_->roleWidget(CCCardHeader::HeaderRole::SUBTITLE));
}

void CCCard::applyContents(ApplierSession s) {
	if (!content_) {
		s(nullptr);
		return;
	}

	s(content_->getContentWidget());
}

void CCCard::setContentsWidget(QWidget* widget) {
	if (!content_) {
		return;
	}

	content_->setContentWidget(widget);
}

QWidget* CCCard::contentWidget() const {
	if (!content_) {
		return nullptr;
	}

	return content_->getContentWidget();
}

void CCCard::setActionVisible(bool visible) {
	if (!actions_)
		return;
	actions_->setVisible(visible);
}

bool CCCard::actionVisible() const {
	return actions_ && actions_->isVisible();
}

CCCardHeader* CCCard::header() const {
	return header_;
}

void CCCard::setHeader(CCCardHeader* newHeader) {
	header_ = newHeader;
}

CCCardContent* CCCard::content() const {
	return content_;
}

void CCCard::setContent(CCCardContent* newContent) {
	content_ = newContent;
}

CCCardActions* CCCard::actions() const {
	return actions_;
}

void CCCard::setActions(CCCardActions* newActions) {
	actions_ = newActions;
}
