#include "demogallerytabhelper.h"
#include <QTabWidget>

void DemoGalleryTabHelper::addRegistries(WidgetGalleryRegistry register_func) {
	registries.emplaceBack(register_func);
}

void DemoGalleryTabHelper::init() {
	for (const auto& each : std::as_const(registries)) {
		auto [widget, galleryName] = each();
		attached_tabwidget->addTab(widget, { galleryName.data() });
	}
}

#include "buttongalleries.h"
#include "cardgallery.h"
#include "labelgallery.h"
#include "progressbargallery.h"
#include "textgallery.h"
DemoGalleryTabHelper::DemoGalleryTabHelper(QTabWidget* parent)
    : QObject { parent } {
	attached_tabwidget = parent;

	addRegistries([this]() {
		return std::pair {
			Gallery::createCardGallery(attached_tabwidget),
			std::string_view { "Card" }
		};
	});

	addRegistries([this]() {
		return std::pair {
			Gallery::createButtonGalleryWidgets(attached_tabwidget),
			std::string_view { "Button" }
		};
	});

	addRegistries([this]() {
		return std::pair {
			Gallery::createTextGalleryWidgets(attached_tabwidget),
			std::string_view { "Text" }
		};
	});

	addRegistries([this]() {
		return std::pair {
			Gallery::createLabelGallery(attached_tabwidget),
			std::string_view { "Labels" }
		};
	});

	addRegistries([this]() {
		return std::pair {
			Gallery::createProgressBarGallery(attached_tabwidget),
			std::string_view { "ProgressBar" }
		};
	});
}
