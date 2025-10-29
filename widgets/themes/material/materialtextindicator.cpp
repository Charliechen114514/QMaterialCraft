#include "materialtextindicator.h"
#include <QFont>
#include <QMap>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QTextDocument>
#include <QWidget>

namespace {

static constexpr const char* defaultFamily { "Roboto" };
static constexpr const qreal globalScale = 1.0;

struct TypographyToken {
	QString family; // font family
	qreal pointSize;
	int weight;
	qreal lineHeightEm;
	qreal letterSpacingEm;
};

using TextStyle = CCWidgetLibrary::TextStyle;

static const QMap<TextStyle, TypographyToken> map = []() {
	QMap<TextStyle, TypographyToken> m;
	m[TextStyle::DisplayLarge] = { defaultFamily, 57.0, 400, 1.12, -0.25 / 57.0 }; // letter-spacing in em ~ converted later
	m[TextStyle::DisplayMedium] = { defaultFamily, 45.0, 400, 1.11, -0.02 / 45.0 };
	m[TextStyle::DisplaySmall] = { defaultFamily, 36.0, 400, 1.11, 0.0 / 36.0 };
	m[TextStyle::HeadlineLarge] = { defaultFamily, 32.0, 400, 1.125, 0.0 / 32.0 };
	m[TextStyle::HeadlineMedium] = { defaultFamily, 28.0, 400, 1.14, 0.0 / 28.0 };
	m[TextStyle::HeadlineSmall] = { defaultFamily, 24.0, 400, 1.166, 0.0 / 24.0 };
	m[TextStyle::TitleLarge] = { defaultFamily, 22.0, 400, 1.18, 0.0 / 22.0 };
	m[TextStyle::TitleMedium] = { defaultFamily, 16.0, 500, 1.25, 0.15 / 16.0 };
	m[TextStyle::TitleSmall] = { defaultFamily, 14.0, 500, 1.28, 0.1 / 14.0 };
	m[TextStyle::BodyLarge] = { defaultFamily, 16.0, 400, 1.5, 0.5 / 16.0 };
	m[TextStyle::BodyMedium] = { defaultFamily, 14.0, 400, 1.43, 0.25 / 14.0 };
	m[TextStyle::BodySmall] = { defaultFamily, 12.0, 400, 1.33, 0.4 / 12.0 };
	m[TextStyle::LabelLarge] = { defaultFamily, 14.0, 500, 1.0, 0.1 / 14.0 };
	m[TextStyle::LabelMedium] = { defaultFamily, 12.0, 500, 1.0, 0.5 / 12.0 };
	m[TextStyle::LabelSmall] = { defaultFamily, 11.0, 500, 1.0, 0.5 / 11.0 };
	return m;
}();

QFont::Weight weightToQt(int weight) {
	if (weight >= 700)
		return QFont::Bold; // 75
	if (weight >= 600)
		return QFont::DemiBold; // 63
	if (weight >= 500)
		return QFont::Medium; // 57
	return QFont::Normal; // 50
}

TypographyToken tokenFor(TextStyle style) {
	return map.value(style);
}

}

namespace CCWidgetLibrary {

QFont MaterialTextIndicator::fontFor(TextStyle style) {
	TypographyToken t = tokenFor(style);
	QFont f(t.family);
	f.setPointSizeF(t.pointSize * globalScale);
	f.setWeight(weightToQt(t.weight));
	// letter spacing: convert em -> absolute pixels using pointSize as approx.
	// QFont::setLetterSpacing(QFont::AbsoluteSpacing, pixels)
	qreal pixels = t.letterSpacingEm * t.pointSize * globalScale;
	f.setLetterSpacing(QFont::AbsoluteSpacing, pixels);
	// Set style hint for better antialiasing (optional)
	f.setStyleStrategy(QFont::PreferAntialias);
	return f;
}

void MaterialTextIndicator::applyTo(QWidget* w, TextStyle style) {
	if (!w)
		return;
	QFont f = fontFor(style);
	w->setFont(f);
}

QTextDocument* MaterialTextIndicator::createTextDocumentWithStyle(const QString& text, TextStyle style) {
	TypographyToken t = tokenFor(style);
	qreal pt = t.pointSize * globalScale;
	QFont f(t.family);
	f.setPointSizeF(pt);
	f.setWeight(weightToQt(t.weight));
	qreal lineHeightPx = t.lineHeightEm * pt;
	auto* doc = new QTextDocument;
	doc->setDefaultFont(f);
	QTextCursor cur(doc);
	cur.insertText(text);
	QTextBlockFormat fmt;
	fmt.setLineHeight(int(lineHeightPx), QTextBlockFormat::FixedHeight);
	cur.select(QTextCursor::Document);
	cur.setBlockFormat(fmt);
	return doc;
}

QString MaterialTextIndicator::styleName(TextStyle s) {
	switch (s) {
	case TextStyle::DisplayLarge:
		return "DisplayLarge";
	case TextStyle::DisplayMedium:
		return "DisplayMedium";
	case TextStyle::DisplaySmall:
		return "DisplaySmall";
	case TextStyle::HeadlineLarge:
		return "HeadlineLarge";
	case TextStyle::HeadlineMedium:
		return "HeadlineMedium";
	case TextStyle::HeadlineSmall:
		return "HeadlineSmall";
	case TextStyle::TitleLarge:
		return "TitleLarge";
	case TextStyle::TitleMedium:
		return "TitleMedium";
	case TextStyle::TitleSmall:
		return "TitleSmall";
	case TextStyle::BodyLarge:
		return "BodyLarge";
	case TextStyle::BodyMedium:
		return "BodyMedium";
	case TextStyle::BodySmall:
		return "BodySmall";
	case TextStyle::LabelLarge:
		return "LabelLarge";
	case TextStyle::LabelMedium:
		return "LabelMedium";
	case TextStyle::LabelSmall:
		return "LabelSmall";
	default:
		return "Unknown";
	}
}

}
