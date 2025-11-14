#include "cctoolbox.h"
#include "CCToolBox/toolboxpaintcontext.h"
#include "paintcontextallocator.h"
#include <QPainter>

CCToolBox::CCToolBox(QWidget* parent)
    : QToolBox(parent) {
	ALLOCATE_PAINTCONTEXT();
}

int CCToolBox::addItem(QWidget* widget, const QString& text) {
	using ToolBoxPaintContext = CCWidgetLibrary::ToolBoxPaintContext;
	ToolBoxPaintContext* tbpc = dynamic_cast<ToolBoxPaintContext*>(paintContext);
	return tbpc->addItemAction(widget, text);
}

int CCToolBox::addItem(QWidget* widget, const QIcon& icon, const QString& text) {
	using ToolBoxPaintContext = CCWidgetLibrary::ToolBoxPaintContext;
	ToolBoxPaintContext* tbpc = dynamic_cast<ToolBoxPaintContext*>(paintContext);
	return tbpc->addItemAction(widget, icon, text);
}

int CCToolBox::insertItem(int index, QWidget* widget, const QString& text) {
	using ToolBoxPaintContext = CCWidgetLibrary::ToolBoxPaintContext;
	ToolBoxPaintContext* tbpc = dynamic_cast<ToolBoxPaintContext*>(paintContext);
	return tbpc->insertItemAction(index, widget, text);
}

int CCToolBox::insertItem(int index, QWidget* widget, const QIcon& icon, const QString& text) {
	using ToolBoxPaintContext = CCWidgetLibrary::ToolBoxPaintContext;
	ToolBoxPaintContext* tbpc = dynamic_cast<ToolBoxPaintContext*>(paintContext);
	return tbpc->insertItemAction(index, widget, icon, text);
}

void CCToolBox::removeItem(int index) {
	using ToolBoxPaintContext = CCWidgetLibrary::ToolBoxPaintContext;
	ToolBoxPaintContext* tbpc = dynamic_cast<ToolBoxPaintContext*>(paintContext);
	tbpc->removeItemAction(index);
}

CONTEXT_PAINT_IMPL(CCToolBox, QToolBox);
CONTEXT_RESIZE_IMPL_WITH_OLD(CCToolBox, QToolBox);
