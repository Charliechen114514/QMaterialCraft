#include "cccard.h"

CCCard::CCCard(QWidget* parent) {
	setAttribute(Qt::WA_Hover);
	setMouseTracking(true);
	setContentsMargins(0, 0, 0, 0);
}

void CCCard::setTitle(const QString& t) {
}

void CCCard::setSubtitle(const QString& s) {
}

void CCCard::setContentWidget(QWidget* w) {
}
