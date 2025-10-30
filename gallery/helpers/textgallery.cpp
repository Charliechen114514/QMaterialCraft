#include "textgallery.h"
#include "Commons/TextIndiator.h"
#include "paintcontext.h"
#include "paintcontextallocator.h"
#include <QLabel>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

QWidget* Gallery::createTextGalleryWidgets(QWidget* parent) {
	static QString sampleText = QStringLiteral(
	    "Material Typography 示例 — 这是一段示例文本，用于演示每种样式的大小、行高与字距。");

	QWidget* root = new QWidget(parent);
	auto* v = new QVBoxLayout(root);
	v->setSpacing(16);
	v->setContentsMargins(16, 16, 16, 16);
	using TextStyle = CCWidgetLibrary::TextStyle;
	QList<TextStyle> allStyles = {
		TextStyle::DisplayLarge, TextStyle::DisplayMedium, TextStyle::DisplaySmall,
		TextStyle::HeadlineLarge, TextStyle::HeadlineMedium, TextStyle::HeadlineSmall,
		TextStyle::TitleLarge, TextStyle::TitleMedium, TextStyle::TitleSmall,
		TextStyle::BodyLarge, TextStyle::BodyMedium, TextStyle::BodySmall,
		TextStyle::LabelLarge, TextStyle::LabelMedium, TextStyle::LabelSmall
	};

	CCWidgetLibrary::TextIndiator* textIndicator = CCWidgetLibrary::PaintContextAllocator::instance().text_indicator();

	for (TextStyle s : allStyles) {
		QLabel* lblTitle = new QLabel(textIndicator->styleName(s));
		lblTitle->setContentsMargins(0, 0, 0, 0);
		// 小标题用 TitleSmall 风格
		textIndicator->applyTo(lblTitle, TextStyle::TitleSmall);
		v->addWidget(lblTitle);

		QLabel* lbl = new QLabel(sampleText);
		lbl->setWordWrap(true);
		textIndicator->applyTo(lbl, s);
		v->addWidget(lbl);
	}

	QScrollArea* sc = new QScrollArea;
	sc->setWidgetResizable(true);
	sc->setWidget(root);

	QWidget* textGallery = new QWidget(parent);
	QVBoxLayout* mainLayout = new QVBoxLayout(textGallery);
	mainLayout->addWidget(sc);

	return textGallery;
}
