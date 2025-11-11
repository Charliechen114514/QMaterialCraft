#ifndef CONTAINERCOMMONDELEGATE_H
#define CONTAINERCOMMONDELEGATE_H

#include <QStyledItemDelegate>

namespace CCWidgetLibrary {
class ContainerCommonDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	explicit ContainerCommonDelegate(QObject* parent = nullptr);
};
}

#endif // CONTAINERCOMMONDELEGATE_H
