#ifndef MARKDOWNHIGHLIGHTER_H
#define MARKDOWNHIGHLIGHTER_H
#include <QRegularExpression>
#include <QSyntaxHighlighter>

namespace CCWidgetLibrary {
class MarkdownHighLighter : public QSyntaxHighlighter {
public:
	MarkdownHighLighter(QTextDocument* parent = nullptr);

protected:
	void highlightBlock(const QString& text) override;
};
}

#endif // MARKDOWNHIGHLIGHTER_H
