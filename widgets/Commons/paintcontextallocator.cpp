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

void PaintContextAllocator::runDelegateRegister(const QString& delegateName,
                                                DelegateRegisterActor actor,
                                                ActPolicy policy) {
	QString check;
	switch (policy) {
	case ActPolicy::AUTO:
		check = composed_style(delegateName);
		break;
	case ActPolicy::MANUAL:
		check = delegateName;
		break;
	}
	delegate_factory.insert(check, actor);
}

ContainerCommonDelegate* PaintContextAllocator::allocate_delegate(
    const QString& delegate_name, QAbstractItemView* view, ActPolicy policy) {
	QString check;
	switch (policy) {
	case ActPolicy::AUTO:
		check = composed_style(delegate_name);
		break;
	case ActPolicy::MANUAL:
		check = delegate_name;
		break;
	}

	auto factor = delegate_factory.find(check);
	if (factor == delegate_factory.end()) {
		return nullptr;
	}
	return (*factor)(view);
}

PaintContextAllocator& PaintContextAllocator::instance() {
	static PaintContextAllocator _inst;
	return _inst;
}

void PaintContextAllocator::setThemes(const QString& themes) {
	PaintContextRegisters* application_registers = factorize_registers("Dummy", instance());
	application_registers->registersMemoryDefaults();
	application_registers->registerDelegates();
	application_registers->register_indicator();
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
	PaintContextRegisters* application_registers = factorize_registers("Dummy", *this);
	application_registers->registersMemoryDefaults();
	application_registers->registerDelegates();
	application_registers->register_indicator();
}

QString PaintContextAllocator::composed_style(const QString& widget_name) {
	if (current_style.isEmpty()) {
		return widget_name;
	} else {
		return current_style + "_" + widget_name;
	}
}
}
