#include "materialcontainercommondelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QTextLayout>

namespace CCWidgetLibrary {
MaterialContainerCommonDelegate::MaterialContainerCommonDelegate(QObject* parent)
    : ContainerCommonDelegate { parent } {
}

QSize MaterialContainerCommonDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const {
	QStyleOptionViewItem opt(option);
	initStyleOption(&opt, index);

	const QString text = opt.text;
	const QFont font = opt.font;

	const int pad = padding_;
	constexpr int iconGap = 8;
	constexpr int checkboxWidth = 22;
	constexpr int minHeight = 24;

	int viewWidth = option.rect.width();
	if (viewWidth <= 0 && option.widget)
		viewWidth = option.widget->width();
	if (viewWidth <= 0)
		viewWidth = 200; // 最后一手回退，防止除以 0

	int used = pad * 2; // 左右 padding
	if (index.data(Qt::DecorationRole).isValid())
		used += iconSize_ + iconGap;
	if (index.flags() & Qt::ItemIsUserCheckable)
		used += checkboxWidth;

	int availWidth = viewWidth - used;
	if (availWidth < 20)
		availWidth = 20; // 防止非常小

	QTextLayout layout(text, font);
	QTextOption to;
	to.setWrapMode(QTextOption::WordWrap);
	layout.setTextOption(to);

	layout.beginLayout();
	qreal textHeight = 0;
	int lineCount = 0;
	while (true) {
		QTextLine line = layout.createLine();
		if (!line.isValid())
			break;
		line.setLineWidth(availWidth);
		++lineCount;
		textHeight += line.height();
	}
	layout.endLayout();

	int totalH = qCeil(textHeight) + pad * 2;
	if (totalH < minHeight)
		totalH = minHeight;

	return QSize(viewWidth, totalH);
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
	painter->setFont(opt.font);
	QString text = opt.text;

	QTextOption to;
	to.setWrapMode(QTextOption::WordWrap);
	to.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	painter->setPen(selected
	                    ? opt.palette.color(QPalette::HighlightedText)
	                    : opt.palette.color(QPalette::Text));

	painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, text);
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
