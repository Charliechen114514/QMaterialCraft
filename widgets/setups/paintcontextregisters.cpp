#include "material/materialpaintcontextregisters.h"
#include "paintcontextallocator.h"
namespace CCWidgetLibrary {

PaintContextRegisters* factorize_registers(const QString& theme_name,
                                           PaintContextAllocator& inst) {
	return new MaterialPaintContextRegisters(inst);
}

PaintContextRegisters::PaintContextRegisters(
    PaintContextAllocator& inst)
    : inst(inst) {
}

void PaintContextRegisters::register_indicator() {
	inst.textIndicator = alloca_indicator();
}
}
