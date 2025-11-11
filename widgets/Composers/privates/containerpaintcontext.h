#ifndef CONTAINERPAINTCONTEXT_H
#define CONTAINERPAINTCONTEXT_H
#include <paintcontext.h>

class QAbstractItemView;

namespace CCWidgetLibrary {
class ContainerPaintContext : public PaintContext {
public:
	explicit ContainerPaintContext(QAbstractItemView* attached_view = nullptr);
	virtual bool initBaseStyleOptions();
	virtual void install_delegates();
	virtual QString get_delegate_name() const = 0;

protected:
	QAbstractItemView* as_item_view() const;

private:
};
}

#endif // CONTAINERPAINTCONTEXT_H
