#ifndef PAINTCONTEXTREGISTERS_H
#define PAINTCONTEXTREGISTERS_H
#include "Commons/paintcontextallocator.h"

namespace CCWidgetLibrary {

PaintContextRegisters* factorize_registers(const QString& theme_name, PaintContextAllocator& inst);

class PaintContextRegisters {
public:
	PaintContextRegisters(PaintContextAllocator& inst);
	virtual void registersMemoryDefaults() = 0;
	virtual void register_indicator();
	virtual void registerDelegates() = 0;

protected:
	virtual std::unique_ptr<TextIndiator> alloca_indicator() = 0;
	PaintContextAllocator& inst;
};
}

#endif // PAINTCONTEXTREGISTERS_H
