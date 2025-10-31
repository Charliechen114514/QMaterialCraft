#include "paintcontextregisters.h"
#include "themes/material/MaterialThemeMarker.h"
#include "themes/material/buttonmaterialpaintcontext.h"
#include "themes/material/components/cardmaterialpaintcontext.h"
#include "themes/material/labelbadgematerialpaintcontext.h"
#include "themes/material/labelmaterialpaintcontext.h"
#include "themes/material/materialtextindicator.h"
#include "themes/material/progressbarmaterialpaintcontext.h"
#include "themes/material/slidermaterialpaintcontext.h"
#include <QPushButton>
#include <QSlider>
void CCWidgetLibrary::PaintContextRegisters::
    registersMemoryDefaults(
        PaintContextAllocator& inst) {
	inst.setStyles(MaterialThemeMarker().style_name());
	inst.runRegister(SliderMaterialPaintContext::SLIDER_NAME, [](QWidget* who) {
		return new SliderMaterialPaintContext(dynamic_cast<QSlider*>(who));
	});
	inst.runRegister(ButtonMaterialPaintContext::BUTTON_NAME, [](QWidget* who) {
		return new ButtonMaterialPaintContext(dynamic_cast<QPushButton*>(who));
	});
	inst.runRegister(LabelMaterialPaintContext::LABEL_NAME, [](QWidget* who) {
		return new LabelMaterialPaintContext(dynamic_cast<QLabel*>(who));
	});
	inst.runRegister(LabelBadgeMaterialPaintContext::WIDGET_NAME, [](QWidget* who) {
		return new LabelBadgeMaterialPaintContext(dynamic_cast<QLabel*>(who));
	});
	inst.runRegister(ProgressBarMaterialPaintContext::WIDGET_NAME, [](QWidget* who) {
		return new ProgressBarMaterialPaintContext(dynamic_cast<QProgressBar*>(who));
	});
	inst.runRegister(CardMaterialPaintContext::WIDGET_NAME, [](QWidget* who) {
		return new CardMaterialPaintContext(who);
	});
}

void CCWidgetLibrary::PaintContextRegisters::getTextIndicator(PaintContextAllocator& inst) {
	inst.textIndicator = std::make_unique<MaterialTextIndicator>();
}
