#ifndef CCIMAGEWIDGET_H
#define CCIMAGEWIDGET_H
#include "CCWidgets_BuildDefine.h"
#include "context_request_macros.h"
#include <QWidget>

CONTEXT_PAINT_PREANNOUNCE;

class CCWIDGET_EXPORT CCImageWidget : public QWidget {
	Q_OBJECT
public:
	static constexpr const char* WIDGET_NAME = "image-widget";
	enum ScaleMode { Cover,
		             Contain,
		             Stretch };
	Q_ENUM(ScaleMode)
	explicit CCImageWidget(QWidget* parent = nullptr);

	ScaleMode scale_mode() const;
	void setScale_mode(const ScaleMode& newScale_mode);

	void setPixmap(const QPixmap& pixmap);
	QPixmap pixmap() const;

	struct BlankColor {
		QColor colorA;
		QColor colorB;
	};

	void setEmptyImage(const BlankColor& color);
	BlankColor emptyWhenColor() const;

signals:
	void image_loaded();

protected:
	CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE;
	CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE;

private:
	ScaleMode scale_mode_;

private:
	CONTEXT_PAINT_ANNOUNCE;
};

#endif // CCIMAGEWIDGET_H
