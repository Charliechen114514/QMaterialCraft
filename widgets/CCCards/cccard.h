#ifndef CCCARD_H
#define CCCARD_H

#include <QFrame>

class QVBoxLayout;
class CCCardHeader;
class CCCardContent;
class CCCardActions;

class CCCard : public QFrame {
	Q_OBJECT
public:
	explicit CCCard(QWidget* parent = nullptr);
	void setTitle(const QString& t);
	void setSubtitle(const QString& s);
	void setContentWidget(QWidget* w);

private:
	QVBoxLayout* layout_;
	CCCardHeader* header_;
	CCCardContent* content_;
	CCCardActions* actions_;

	bool hovered_ = false;
	QImage shadowCache_;
};

#endif // CCCARD_H
