#include "cctextfieldmaterialpaintcontext.h"
#include "CCTextField/cctextfield.h"
#include "cclabel.h"
#include "helpers/commonwidgetsettingshelper.h"
#include <QEvent>
#include <QLineEdit>
#include <QPainter>
#include <QTextEdit>
#include <QToolButton>

namespace CCWidgetLibrary {

CCTextFieldMaterialPaintContext::CCTextFieldMaterialPaintContext(
    CCTextField* attached_widget)
    : CCTextFieldPaintContext(attached_widget) {
	attached_widget->setAttribute(Qt::WA_Hover, true);
	attached_widget->setMinimumHeight(64);
	attached_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	attached_widget->setAttribute(Qt::WA_InputMethodEnabled, true);
	internal_package.textEdit->hide();
	internal_package.textEdit->setAcceptRichText(false);
	internal_package.textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	internal_package.floatingLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
	WidgetHelpers::setWidgetBackgroundTransparent(internal_package.floatingLabel);

	WidgetHelpers::setLabelFontWithColor(internal_package.helperLabel, 11, { 0, 0, 0, 153 });
	internal_package.helperLabel->setVisible(false);

	// focus handling
	internal_package.lineEdit->installEventFilter(this);
	internal_package.textEdit->installEventFilter(this);
	attached_widget->installEventFilter(this);

	floating_animation = std::make_unique<AnimationHolder>(this, "labelProgress");
	underline_animation = std::make_unique<AnimationHolder>(this, "underlineProgress");

	floating_animation->get_helpers()->applySettings([this](AnimationHelper::SettingsConfig& conf) {
		conf.curve = QEasingCurve::InOutCubic;
		conf.period_time = DURATION;
	});

	underline_animation->get_helpers()->applySettings([this](AnimationHelper::SettingsConfig& conf) {
		conf.curve = QEasingCurve::InOutCubic;
		conf.period_time = DURATION;
	});
}

bool CCTextFieldMaterialPaintContext::paint(QPainter& p) {
	p.save();
	p.setRenderHint(QPainter::Antialiasing);
	auto* text_field = dynamic_cast<CCTextField*>(attached_widget);

	// draw background if needed (transparent by default)

	// underline baseline
	int y = (text_field->isMultiline() ? internal_package.textEdit->geometry().bottom() : internal_package.lineEdit->geometry().bottom());
	int lineY = y + 8;

	// base line (thin)
	QColor base = onSurface_;
	base.setAlpha(90);
	p.setPen(QPen(base, 1));
	p.drawLine(12, lineY, text_field->width() - 12, lineY);

	// animated overlay line (thicker, primary or error)
	qreal t = underlineProgress_; // 0..1
	if (t > 0.0 && focused_) {
		QColor col = !text_field->errorOccured() ? primary_ : errorColor_;
		// interpolate alpha/width
		qreal w = 1.0 + 2.0 * t; // 1..3 px
		p.setPen(QPen(col, w, Qt::SolidLine, Qt::RoundCap));
		// draw with slight inset for animation nicety
		const int inset = static_cast<int>(6 * (1.0 - t));
		p.drawLine(12 + inset, lineY, text_field->width() - 12 - inset, lineY);
	}
	p.restore();
	return true;
}

void CCTextFieldMaterialPaintContext::animateFloatingLabel(bool requestAnimate) {
	auto* text_field = dynamic_cast<CCTextField*>(attached_widget);

	bool shouldFloat = focused_ || !text_field->text().isEmpty();
	qreal target = shouldFloat ? 1.0 : 0.0;
	if (requestAnimate) {
		underline_animation->get_helpers()->applySession([target](AnimationHelper::RuntimeConfig& conf) {
			conf.end = target;
		});
	} else {
		setLabelProgress(target);
	}
}

void CCTextFieldMaterialPaintContext::animateUnderLine(bool requestAnimate) {
	underline_animation->get_helpers()->applySession([](AnimationHelper::RuntimeConfig& conf) {
		conf.end = 1.0;
	});
}

QColor CCTextFieldMaterialPaintContext::errorColor() const {
	return errorColor_;
}

void CCTextFieldMaterialPaintContext::setErrorColor(const QColor& newErrorColor) {
	errorColor_ = newErrorColor;
}

void CCTextFieldMaterialPaintContext::handleResizeEvent(const QResizeEvent* ev) {
	auto* text_field = dynamic_cast<CCTextField*>(attached_widget);
	if (!text_field)
		return;

	const int margin = 12;
	int totalH = text_field->height();
	int inputTop = 28;
	int helperH = 16;
	int inputH = totalH - inputTop - helperH - 8;

	if (!text_field->isMultiline()) {
		internal_package.lineEdit->setGeometry(
		    margin, inputTop,
		    text_field->width() - margin * 2, 28);
		internal_package.textEdit->setVisible(false);
		internal_package.lineEdit->setVisible(true);
	} else {
		internal_package.textEdit->setGeometry(
		    margin, inputTop,
		    text_field->width() - margin * 2, inputH);
		internal_package.lineEdit->setVisible(false);
		internal_package.textEdit->setVisible(true);
	}

	// helper label
	internal_package.helperLabel->setGeometry(
	    margin,
	    totalH - helperH - 4,
	    text_field->width() - margin * 2,
	    helperH);

	constexpr int btnW = 22;
	constexpr int btnH = 22;
	bool rtl = (attached_widget->layoutDirection() == Qt::RightToLeft);
	int btnX = rtl ? margin : attached_widget->width() - margin - btnW;
	int btnY = inputTop + (28 - btnH) / 2;
	internal_package.clearBtn->setGeometry(btnX, btnY, btnW, btnH);
	int visX = rtl ? (btnX + btnW + 6) : (btnX - btnW - 6);
	internal_package.visibilityBtn->setGeometry(visX, btnY, btnW, btnH);

	auto labelRect = internal_package.floatingLabel->geometry();
	labelRect.setWidth(text_field->width() - margin * 2);
	internal_package.floatingLabel->setGeometry(labelRect);
}

void CCTextFieldMaterialPaintContext::animate_error() {
	WidgetHelpers::setLabelFontWithColor(internal_package.helperLabel, 11, errorColor_);
	internal_package.helperLabel->setTextColor(errorColor_);
	internal_package.helperLabel->setVisible(true);
}

bool CCTextFieldMaterialPaintContext::eventFilter(QObject* obj, QEvent* ev) {
	auto* text_field = dynamic_cast<CCTextField*>(attached_widget);

	if (obj == internal_package.lineEdit || obj == internal_package.textEdit) {
		if (ev->type() == QEvent::FocusIn) {
			focused_ = true;
			animateFloatingLabel(true);
			animateUnderLine(true);
			attached_widget->update();
		} else if (ev->type() == QEvent::FocusOut) {
			focused_ = false;
			animateFloatingLabel(true);
			animateUnderLine(true);
			attached_widget->update();
			text_field->validateAndUpdate();
		}
	}
	if (ev->type() == QEvent::HoverEnter) {
		hovered_ = true;
		attached_widget->update();
	} else if (ev->type() == QEvent::HoverLeave) {
		hovered_ = false;
		attached_widget->update();
	}
	return QObject::eventFilter(obj, ev);
}

qreal CCTextFieldMaterialPaintContext::labelProgress() const {
	return labelProgress_;
}

void CCTextFieldMaterialPaintContext::setLabelProgress(qreal p) {
	if (p == labelProgress_)
		return;
	labelProgress_ = p;
	updateFloatingLabelGeometry();
	emit labelProgressChanged(p);
}

qreal CCTextFieldMaterialPaintContext::underlineProgress() const {
	return underlineProgress_;
}

void CCTextFieldMaterialPaintContext::setUnderlineProgress(qreal p) {
	if (p == underlineProgress_)
		return;
	underlineProgress_ = p;
	attached_widget->update();
	emit underlineProgressChanged(p);
}

void CCTextFieldMaterialPaintContext::updateFloatingLabelGeometry() {
	QFont f = attached_widget->font();
	// positions
	constexpr int inlineY = 26; // inside input
	constexpr int floatedY = 6; // top padding
	constexpr int x = 14;
	int y = static_cast<int>(inlineY + (floatedY - inlineY) * labelProgress_);
	internal_package.floatingLabel->move(x, y);

	// scale font smoothly
	qreal startPt = f.pointSizeF();
	if (startPt <= 0)
		startPt = f.pixelSize() > 0 ? f.pixelSize() : 12;
	qreal endPt = startPt * 0.78;
	qreal cur = startPt + (endPt - startPt) * labelProgress_;
	QFont lf = f;
	lf.setPointSizeF(cur);
	internal_package.floatingLabel->setFont(lf);

	QColor col = onSurface_;
	int alpha = static_cast<int>(160 + 95 * labelProgress_); // more visible when floated
	col.setAlpha(alpha);
	QPalette pal = internal_package.floatingLabel->palette();
	pal.setColor(QPalette::WindowText, col);
	internal_package.floatingLabel->setPalette(pal);
	internal_package.floatingLabel->adjustSize();
}
}
