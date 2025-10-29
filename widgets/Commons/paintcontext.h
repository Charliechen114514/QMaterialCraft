#ifndef PAINTCONTEXT_H
#define PAINTCONTEXT_H
#include <QObject>
#include <QString>
#include <QtClassHelperMacros>
class QPainter;
class QMouseEvent;
class QResizeEvent;
class QWidget;

namespace CCWidgetLibrary {

enum class MouseEventType {
	MOUSE_PRESS,
	MOUSE_MOVE,
	MOUSE_RELEASE
};

enum class HoverEventType {
	HOVER_IN,
	HOVER_OUT
};

/**
 * @brief   PaintContext is the abstract class for
 *          designs, like you can load different Context
 *          to override the behavior of the widgets apperance
 */
class PaintContext : public QObject {
public:
	explicit PaintContext(QWidget* attached_widget = nullptr);

	virtual ~PaintContext() = default;

	/**
	 * Paint interface for the widget paintings
	 */
	virtual bool paint(QPainter& p) = 0;

	/**
	 * @brief handleMouseEvent will using to
	 * @param type mouseEvent type
	 * @param ev mouseEvent
	 */
	virtual void handleMouseEvent(
	    const MouseEventType type, QMouseEvent* ev);

	virtual void handleResizeEvent(const QResizeEvent* ev);

	virtual void handleHoverEvent(const HoverEventType type, QEvent* ev);

	virtual bool checkContextAvalible();

	QString context_name() const noexcept {
		return _context_name;
	};

protected:
	QWidget* attached_widget;
	QString _context_name;

private:
	PaintContext() = delete;
	Q_DISABLE_COPY_MOVE(PaintContext);
};
}

#endif // PAINTCONTEXT_H
