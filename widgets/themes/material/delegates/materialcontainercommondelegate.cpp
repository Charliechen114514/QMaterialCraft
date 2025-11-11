#include "materialcontainercommondelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>

namespace CCWidgetLibrary {
MaterialContainerCommonDelegate::MaterialContainerCommonDelegate(QObject* parent)
    : ContainerCommonDelegate { parent } {
}

QSize MaterialContainerCommonDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const {
	QSize s = QStyledItemDelegate::sizeHint(option, index);
	// get the expected height or the icons + paddings
	s.setHeight(qMax(s.height(), iconSize_ + padding_));
	return s;
}

void MaterialContainerCommonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QStyleOptionViewItem opt(option);
	initStyleOption(&opt, index);
	painter->save();

	bool selected = opt.state & QStyle::State_Selected;
	bool hovered = opt.state & QStyle::State_MouseOver;
	QRect rect = opt.rect.adjusted(2, 2, -2, -2);

	QColor bg = opt.palette.color(QPalette::Base);
	if (selected)
		bg = opt.palette.color(QPalette::Highlight);
	else if (hovered)
		bg = bg.lighter(108);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setBrush(bg);
	painter->setPen(Qt::NoPen);
	painter->drawRoundedRect(rect, rowRadius_, rowRadius_);

	int x = rect.x() + padding_;
	int centerY = rect.center().y();

	QVariant iconVar = index.data(Qt::DecorationRole);
	if (iconVar.isValid()) {
		QIcon icon = qvariant_cast<QIcon>(iconVar);
		QRect iconRect(x, centerY - iconSize_ / 2, iconSize_, iconSize_);
		icon.paint(painter, iconRect);
		x += iconSize_ + 8;
	}

	// draw checkbox if item is checkable
	bool isCheckable = index.flags() & Qt::ItemIsUserCheckable;
	QRect cbRect;
	if (isCheckable) {
		Qt::CheckState state = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
		QStyleOptionButton checkOpt;
		checkOpt.state |= QStyle::State_Enabled;
		if (state == Qt::Checked)
			checkOpt.state |= QStyle::State_On;
		else if (state == Qt::PartiallyChecked)
			checkOpt.state |= QStyle::State_NoChange;
		else
			checkOpt.state |= QStyle::State_Off;

		cbRect = QRect(x, centerY - 8, 16, 16);
		checkOpt.rect = cbRect;
		QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkOpt, painter);
		x += 22;
	}

	QRect textRect(x, rect.y(), rect.width() - (x - rect.x()) - padding_, rect.height());
	painter->setPen(selected ? opt.palette.color(QPalette::HighlightedText) : opt.palette.color(QPalette::Text));
	painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, index.data(Qt::DisplayRole).toString());
	painter->restore();
}

bool MaterialContainerCommonDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) {
	if (!(index.flags() & Qt::ItemIsUserCheckable))
		return QStyledItemDelegate::editorEvent(event, model, option, index);

	QRect rect = option.rect.adjusted(2, 2, -2, -2);
	int x = rect.x() + padding_;
	QVariant iconVar = index.data(Qt::DecorationRole);
	if (iconVar.isValid())
		x += iconSize_ + 8;
	QRect cbRect = QRect(x, rect.center().y() - 8, 16, 16);

	// Combine the button to prevent duplicate clicks
	if (event->type() == QEvent::MouseButtonRelease) {
		QMouseEvent* me = static_cast<QMouseEvent*>(event);
		if (me->button() != Qt::LeftButton)
			return false;
		QPoint pos = me->pos(); // viewport coordinates
		if (cbRect.contains(pos)) {
			Qt::CheckState state = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
			Qt::CheckState next = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
			return model->setData(index, QVariant::fromValue<int>(next), Qt::CheckStateRole);
		}
	}

	// Key Space actions
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* ke = static_cast<QKeyEvent*>(event);
		if (ke->key() == Qt::Key_Space) {
			Qt::CheckState state = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
			Qt::CheckState next = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
			return model->setData(index, QVariant::fromValue<int>(next), Qt::CheckStateRole);
		}
	}

	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
}
