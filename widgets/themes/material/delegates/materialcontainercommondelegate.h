#ifndef MATERIALCONTAINERCOMMONDELEGATE_H
#define MATERIALCONTAINERCOMMONDELEGATE_H
#include "Composers/privates/container_delegates_keys.h"
#include "Composers/privates/containercommondelegate.h"
namespace CCWidgetLibrary {
class MaterialContainerCommonDelegate : public ContainerCommonDelegate {
	Q_OBJECT
public:
	static constexpr const char* DELEGATE_NAME = FALLBACK_DELEGATE_NAME;
	explicit MaterialContainerCommonDelegate(QObject* parent = nullptr);

	/**
	 * @brief sizeHint size providers
	 * @param option
	 * @param index
	 * @return
	 */
	QSize sizeHint(const QStyleOptionViewItem& option,
	               const QModelIndex& index) const override;

	void paint(QPainter* painter,
	           const QStyleOptionViewItem& option,
	           const QModelIndex& index) const override;

	bool editorEvent(QEvent* event,
	                 QAbstractItemModel* model,
	                 const QStyleOptionViewItem& option,
	                 const QModelIndex& index) override;

private:
	int rowRadius_ { 6 };
	int padding_ { 12 };
	int iconSize_ { 20 };
};
}

#endif // MATERIALCONTAINERCOMMONDELEGATE_H
