#ifndef CCCARD_H
#define CCCARD_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include "privates/cccard_components_name.h"
#include <QFrame>

CONTEXT_PAINT_PREANNOUNCE;

class QVBoxLayout;
class CCCardHeader;
class CCCardContent;
class CCCardActions;

class CCWIDGET_EXPORT CCCard : public QFrame {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = CCWidgetLibrary::Card::WIDGET_NAME;
	explicit CCCard(QWidget* parent = nullptr);

	using ApplierSession = std::function<void(QWidget*)>;
	/**
	 * @brief applyHeaders
	 * @param s session functions, which will provided the
	 * header widgets in CCCardHeader
	 */
	void applyHeaders(ApplierSession s);
	/**
	 * @brief applySubHeaders
	 * @param s session functions, which will provided the
	 * subheader widgets in CCCardHeader
	 */
	void applySubHeaders(ApplierSession s);
	/**
	 * @brief applyContents
	 * @param s session functions, these will pass the content widget
	 * in the CCCardContent
	 */
	void applyContents(ApplierSession s);

	void setContentsWidget(QWidget* widget);
	QWidget* contentWidget() const;

	void setActionVisible(bool visible);
	bool actionVisible() const;

protected:
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;

public:
	/* High Self Defined Interfaces */
	CCCardHeader* header() const;
	void setHeader(CCCardHeader* newHeader);
	CCCardContent* content() const;
	void setContent(CCCardContent* newContent);
	CCCardActions* actions() const;
	void setActions(CCCardActions* newActions);

private:
	CCCardHeader* header_;
	CCCardContent* content_;
	CCCardActions* actions_;

	bool hovered_ = false;
	QImage shadowCache_;

	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCCARD_H
