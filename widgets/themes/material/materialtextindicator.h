#ifndef MATERIALTEXTINDICATOR_H
#define MATERIALTEXTINDICATOR_H
#include "TextIndiator.h"

namespace CCWidgetLibrary {

class MaterialTextIndicator : public TextIndiator {
public:
	QString styleName(TextStyle s) override;
	QFont fontFor(TextStyle style) override;
	void applyTo(QWidget* w, TextStyle style) override;
	QTextDocument* createTextDocumentWithStyle(const QString& text, TextStyle style) override;
};
}

#endif // MATERIALTEXTINDICATOR_H
