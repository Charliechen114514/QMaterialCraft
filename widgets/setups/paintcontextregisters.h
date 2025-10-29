#ifndef PAINTCONTEXTREGISTERS_H
#define PAINTCONTEXTREGISTERS_H
#include "Commons/paintcontextallocator.h"

namespace CCWidgetLibrary {
class PaintContextRegisters {
public:
	static void registersMemoryDefaults(
	    PaintContextAllocator& inst);
	static void getTextIndicator(PaintContextAllocator& inst);
};
}

#endif // PAINTCONTEXTREGISTERS_H
