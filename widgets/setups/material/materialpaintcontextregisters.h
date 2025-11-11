#ifndef MATERIALPAINTCONTEXTREGISTERS_H
#define MATERIALPAINTCONTEXTREGISTERS_H
#include "setups/paintcontextregisters.h"

namespace CCWidgetLibrary {
class MaterialPaintContextRegisters : public PaintContextRegisters {
public:
	using PaintContextRegisters::PaintContextRegisters;
	void registersMemoryDefaults() override;
	void registerDelegates() override;

protected:
	std::unique_ptr<TextIndiator> alloca_indicator() override;
};
}

#endif // MATERIALPAINTCONTEXTREGISTERS_H
