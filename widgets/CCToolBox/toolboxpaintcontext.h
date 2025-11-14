#ifndef TOOLBOXPAINTCONTEXT_H
#define TOOLBOXPAINTCONTEXT_H

#include <paintcontext.h>
class QToolBox;

namespace CCWidgetLibrary {
class ToolBoxPaintContext : public PaintContext {
public:
	ToolBoxPaintContext(QToolBox* toolbox);

	virtual int addItemAction(QWidget* widget, const QString& text) = 0;
	virtual int addItemAction(QWidget* widget, const QIcon& icon, const QString& text) = 0;

	virtual int insertItemAction(
	    int index, QWidget* widget, const QString& text)
	    = 0;
	virtual int insertItemAction(
	    int index, QWidget* widget,
	    const QIcon& icon, const QString& text)
	    = 0;

	virtual void removeItemAction(int index) = 0;
};
}

#endif // TOOLBOXPAINTCONTEXT_H
