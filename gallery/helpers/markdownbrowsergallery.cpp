#include "markdownbrowsergallery.h"
#include "CCMarkdownWidget/ccmarkdownbrowserwidget.h"
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

static const QString DEMO_MARKDOWN = R"(# ✨ Welcome to CCWidget
This is a demo of the **Markdown Browser Widget**. 

It supports typical Markdown syntax:
- *Italic text*
- **Bold text**
- `Inline Code`
- [Links](https://www.qt.io)

---

## 💻 Syntax Highlighting
The widget includes a custom highlighter. Try typing some C++ code:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!" << std::endl;
    return 0;
}
```
📄 Automatic Pagination
Notice how this content is split?

The browser automatically splits content into "Cards" or "Pages" whenever it encounters a Header 1 (#) or Header 2 (##).

Click the Source button to see raw text.

Click the Cards button to see the result.

Use the Arrows below to navigate pages.

🚀 Performance
This widget is optimized for:

Diff Updates: Only changed cards are re-rendered.

Memory: Rules are static and shared.

User Exp: Cursor position is preserved during edits.

Enjoy coding! )";

QWidget* Gallery::createMarkdownBrowserGalleryWidgets(QWidget* parent) {
	QWidget* container = new QWidget(parent);
	QVBoxLayout* layout = new QVBoxLayout(container);
	layout->setContentsMargins(10, 10, 10, 10);
	layout->setSpacing(10);

	QLabel* title = new QLabel("<h3>Markdown Browser Component</h3>", container);
	title->setTextFormat(Qt::RichText);
	title->setStyleSheet("color: #555; margin-bottom: 5px;");
	layout->addWidget(title);
	title->setMaximumHeight(50);

	auto* browser = new CCMarkdownBrowserWidget(container);
	browser->setMarkdown(DEMO_MARKDOWN);

	layout->addWidget(browser);

	return container;
}
