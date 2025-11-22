#include "markdownhighlighter.h"
#include <QRegularExpression>

namespace {
struct HighlightingRule {
	QRegularExpression pattern;
	QTextCharFormat format;
};

const std::vector<HighlightingRule>& getMarkdownRules() {
	static const std::vector<HighlightingRule> rules = []() {
		std::vector<HighlightingRule> r;

		// === Header (#, ##, ### ...) ===
		QTextCharFormat hfmt;
		hfmt.setFontWeight(QFont::Bold);
		hfmt.setForeground(QColor(0x1f2937));
		hfmt.setFontPointSize(14);
		r.push_back({ QRegularExpression(R"(^#{1,6}\s+.*)"), hfmt });

		// === Bold **text** ===
		QTextCharFormat bfmt;
		bfmt.setFontWeight(QFont::Bold);
		r.push_back({ QRegularExpression(R"(\*\*[^*]+\*\*)"), bfmt });

		// === Italic *text* ===
		QTextCharFormat ifmt;
		ifmt.setFontItalic(true);
		r.push_back({ QRegularExpression(R"(\*[^*]+\*)"), ifmt });

		// === Inline code `code` ===
		QTextCharFormat codeFmt;
		codeFmt.setFontFamilies({ "monospace", "Courier New", "Consolas" });
		codeFmt.setBackground(QColor(0xf3f4f6));
		codeFmt.setForeground(QColor(0xc7254e)); // 通常行内代码会有一点颜色区分
		r.push_back({ QRegularExpression(R"(`[^`]+`)"), codeFmt });

		// === Links [text](url) ===
		QTextCharFormat linkFmt;
		linkFmt.setForeground(QColor(0x0f62fe));
		linkFmt.setFontUnderline(true);
		r.push_back({ QRegularExpression(R"(\[[^\]]+\]\([^)]+\))"), linkFmt });

		return r;
	}();
	return rules;
}

QTextCharFormat getCodeBlockFormat() {
	static const QTextCharFormat fmt = []() {
		QTextCharFormat f;
		f.setFontFamilies({ "monospace", "Courier New", "Consolas" });
		f.setBackground(QColor(0xe5e7eb));
		// f.setForeground(QColor(0x333333));
		return f;
	}();
	return fmt;
}

}

namespace CCWidgetLibrary {

MarkdownHighLighter::MarkdownHighLighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent) {
}

void MarkdownHighLighter::highlightBlock(const QString& text) {
	const auto& rules = getMarkdownRules();
	for (const auto& rule : rules) {
		QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
		while (matchIterator.hasNext()) {
			QRegularExpressionMatch match = matchIterator.next();
			setFormat(match.capturedStart(), match.capturedLength(), rule.format);
		}
	}

	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = -1;

	static const QRegularExpression startExp(R"(^```)");
	static const QRegularExpression endExp(R"(^```)");

	QTextCharFormat codeBlockFmt = getCodeBlockFormat();
	QRegularExpressionMatch startMatch = startExp.match(text);

	if (previousBlockState() == 1) {
		startIndex = 0;
	} else if (startMatch.hasMatch()) {
		startIndex = startMatch.capturedStart();
	}

	if (startIndex >= 0) {
		QRegularExpressionMatch endMatch = endExp.match(text, startIndex + (previousBlockState() == 1 ? 0 : 3));

		int commentLength = 0;
		if (endMatch.hasMatch()) {
			commentLength = endMatch.capturedEnd() - startIndex;
			setCurrentBlockState(0);
		} else {
			commentLength = text.length() - startIndex;
			setCurrentBlockState(1);
		}

		setFormat(startIndex, commentLength, codeBlockFmt);
	}
}
}
