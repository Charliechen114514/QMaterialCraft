#include "materialpaintcontextregisters.h"
#include "CCCards/cccard.h"
#include "CCImageWidget/ccimagewidget.h"
#include "CCProgressBar/progressbar.h"
#include "CCTextField/cctextfield.h"
#include "CCToolBox/cctoolbox.h"
#include "CCToolButton/cctoolbutton.h"
#include "Composers/CCListView/cclistview.h"
#include "Composers/CCListWidget/cclistwidget.h"
#include "Composers/CCTableView/cctableview.h"
#include "Composers/CCTableWidget/cctablewidget.h"
#include "Composers/CCTreeView/cctreeview.h"
#include "Composers/CCTreeWidget/cctreewidget.h"
#include "button.h"
#include "ccbadgelabel.h"
#include "cclabel.h"
#include "slider.h"
#include "themes/material/MaterialThemeMarker.h"
#include "themes/material/buttonmaterialpaintcontext.h"
#include "themes/material/components/cardmaterialpaintcontext.h"
#include "themes/material/components/cctextfieldmaterialpaintcontext.h"
#include "themes/material/delegates/materialcontainercommondelegate.h"
#include "themes/material/imagewidgetmaterialpaintcontext.h"
#include "themes/material/labelbadgematerialpaintcontext.h"
#include "themes/material/labelmaterialpaintcontext.h"
#include "themes/material/materiallistviewpaintcontext.h"
#include "themes/material/materiallistwidgetpaintcontext.h"
#include "themes/material/materialtableviewpaintcontext.h"
#include "themes/material/materialtablewidgetpaintcontext.h"
#include "themes/material/materialtextindicator.h"
#include "themes/material/materialtreeviewpaintcontext.h"
#include "themes/material/materialtreewidgetpaintcontext.h"
#include "themes/material/progressbarmaterialpaintcontext.h"
#include "themes/material/slidermaterialpaintcontext.h"
#include "themes/material/toolbox/materialtoolboxpaintcontext.h"
#include "themes/material/toolbuttonmaterialpaintcontext.h"
#include <QPushButton>
#include <QSlider>
namespace CCWidgetLibrary {
void MaterialPaintContextRegisters::
    registersMemoryDefaults() {
	inst.setStyles(MaterialThemeMarker().style_name());
	inst.runRegister(CCSlider::WIDGET_NAME, [](QWidget* who) {
		return new SliderMaterialPaintContext(dynamic_cast<QSlider*>(who));
	});
	inst.runRegister(CCButton::WIDGET_NAME, [](QWidget* who) {
		return new ButtonMaterialPaintContext(dynamic_cast<QPushButton*>(who));
	});
	inst.runRegister(CCLabel::WIDGET_NAME, [](QWidget* who) {
		return new LabelMaterialPaintContext(dynamic_cast<QLabel*>(who));
	});
	inst.runRegister(CCBadgeLabel::WIDGET_NAME, [](QWidget* who) {
		return new LabelBadgeMaterialPaintContext(dynamic_cast<QLabel*>(who));
	});
	inst.runRegister(CCProgressBar::WIDGET_NAME, [](QWidget* who) {
		return new ProgressBarMaterialPaintContext(dynamic_cast<QProgressBar*>(who));
	});
	inst.runRegister(CCCard::WIDGET_NAME, [](QWidget* who) {
		return new CardMaterialPaintContext(who);
	});
	inst.runRegister(CCTextField::WIDGET_NAME, [](QWidget* who) {
		return new CCTextFieldMaterialPaintContext(dynamic_cast<CCTextField*>(who));
	});
	inst.runRegister(CCImageWidget::WIDGET_NAME, [](QWidget* who) {
		return new ImageWidgetMaterialPaintContext(dynamic_cast<CCImageWidget*>(who));
	});
	inst.runRegister(CCTreeWidget::WIDGET_NAME, [](QWidget* who) {
		return new MaterialTreeWidgetPaintContext(dynamic_cast<QTreeWidget*>(who));
	});
	inst.runRegister(CCTreeView::WIDGET_NAME, [](QWidget* who) {
		return new MaterialTreeViewPaintContext(dynamic_cast<QTreeView*>(who));
	});
	inst.runRegister(CCListWidget::WIDGET_NAME, [](QWidget* who) {
		return new MaterialListWidgetPaintContext(dynamic_cast<QListWidget*>(who));
	});

	inst.runRegister(CCListView::WIDGET_NAME, [](QWidget* who) {
		return new MaterialListViewPaintContext(dynamic_cast<QListView*>(who));
	});

	inst.runRegister(CCTableWidget::WIDGET_NAME, [](QWidget* who) {
		return new MaterialTableWidgetPaintContext(dynamic_cast<QTableWidget*>(who));
	});

	inst.runRegister(CCTableView::WIDGET_NAME, [](QWidget* who) {
		return new MaterialTableViewPaintContext(dynamic_cast<QTableView*>(who));
	});

	inst.runRegister(CCToolButton::WIDGET_NAME, [](QWidget* who) {
		return new MaterialToolButtonPaintContext(dynamic_cast<QToolButton*>(who));
	});

	inst.runRegister(CCToolBox::WIDGET_NAME, [](QWidget* who) {
		return new MaterialToolBoxPaintContext(dynamic_cast<QToolBox*>(who));
	});
}

std::unique_ptr<TextIndiator>
MaterialPaintContextRegisters::alloca_indicator() {
	return std::make_unique<MaterialTextIndicator>();
}

void MaterialPaintContextRegisters::registerDelegates() {
	inst.setStyles(MaterialThemeMarker().style_name());
	inst.runDelegateRegister(MaterialContainerCommonDelegate::DELEGATE_NAME,
	                         [](QAbstractItemView* itemView) {
		                         return new MaterialContainerCommonDelegate(itemView);
	                         });
}

}
