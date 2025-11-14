#include "cctoolbutton.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QHoverEvent>
#include <QPainter>

CCToolButton::CCToolButton(QWidget* parent)
    : QToolButton(parent) {
	ALLOCATE_PAINTCONTEXT();
}

CONTEXT_PAINT_IMPL(CCToolButton, QToolButton);
CONTEXT_HOVER_IMPL(CCToolButton);
