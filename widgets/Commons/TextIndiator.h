#ifndef TEXTINDIATOR_H
#define TEXTINDIATOR_H
#include <QFont>
#include <QString>
class QTextDocument;

namespace CCWidgetLibrary {

enum class TextStyle {
	DisplayLarge,
	DisplayMedium,
	DisplaySmall,
	HeadlineLarge,
	HeadlineMedium,
	HeadlineSmall,
	TitleLarge,
	TitleMedium,
	TitleSmall,
	BodyLarge,
	BodyMedium,
	BodySmall,
	LabelLarge,
	LabelMedium,
	LabelSmall
};

class TextIndiator {
public:
	virtual QString styleName(TextStyle s) = 0;
	virtual QFont fontFor(TextStyle style) = 0;
	virtual void applyTo(QWidget* w, TextStyle style) = 0;
	virtual QTextDocument* createTextDocumentWithStyle(
	    const QString& text, TextStyle style)
	    = 0;
};
}

#endif // TEXTINDIATOR_H
