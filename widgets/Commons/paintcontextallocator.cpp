#include "paintcontextallocator.h"
#include "setups/paintcontextregisters.h"
namespace CCWidgetLibrary {

void PaintContextAllocator::runRegister(
    const QString& paintContextName, RegisterActor actor, ActPolicy policy) {
	QString check;
	switch (policy) {
	case ActPolicy::AUTO:
		check = composed_style(paintContextName);
		break;
	case ActPolicy::MANUAL:
		check = paintContextName;
		break;
	}
	factory.insert(check, actor);
}

PaintContextAllocator& PaintContextAllocator::instance() {
	static PaintContextAllocator _inst;
	return _inst;
}

void PaintContextAllocator::setStyles(const QString& current_style) {
	this->current_style = current_style;
	emit styleChanged(current_style);
}

TextIndiator* PaintContextAllocator::text_indicator() const {
	return textIndicator.get();
}

PaintContext* PaintContextAllocator::allocate_paintContext(
    const QString& paintContextName, QWidget* who, ActPolicy policy) {
	QString check;
	switch (policy) {
	case ActPolicy::AUTO:
		check = composed_style(paintContextName);
		break;
	case ActPolicy::MANUAL:
		check = paintContextName;
		break;
	}

	auto factor = factory.find(check);
	if (factor == factory.end()) {
		return nullptr;
	}
	return (*factor)(who);
}

PaintContextAllocator::PaintContextAllocator()
    : QObject {} {
	PaintContextRegisters::registersMemoryDefaults(*this);
	PaintContextRegisters::getTextIndicator(*this);
}

QString PaintContextAllocator::composed_style(const QString& widget_name) {
	if (current_style.isEmpty()) {
		return widget_name;
	} else {
		return current_style + "_" + widget_name;
	}
}
}
