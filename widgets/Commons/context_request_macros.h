/**
 *  @file   This file expected to provides some simple
 *          macro helpers to hide the request overrides and helpers for
 *          duplicate writings
 */

#ifndef CONTEXT_REQUEST_MACROS_H
#define CONTEXT_REQUEST_MACROS_H

/**
 * This is the pre-announcements of the PaintContext in CCWidgetLibrary
 */
#define CONTEXT_PAINT_PREANNOUNCE \
	namespace CCWidgetLibrary {   \
	class PaintContext;           \
	}

#define CONTEXT_PAINT_ANNOUNCE_VAR(varName) \
	CCWidgetLibrary::PaintContext* varName

#define CONTEXT_PAINT_ANNOUNCE CONTEXT_PAINT_ANNOUNCE_VAR(paintContext)

#define CONTEXT_PAINT_PAINTEVENT_REQUEST_OVERRIDE \
	void paintEvent(QPaintEvent* event) override;

#define CONTEXT_PAINT_MOUSEEVENT_REQUEST_OVERRIDE        \
	void mousePressEvent(QMouseEvent* event) override;   \
	void mouseReleaseEvent(QMouseEvent* event) override; \
	void mouseMoveEvent(QMouseEvent* event) override;

#define CONTEXT_PAINT_RESIZEEVENT_REQUEST_OVERRIDE \
	void resizeEvent(QResizeEvent* event) override;

#define CONTEXT_PAINT_HOVEREVENT_REQUEST_OVERRIDE \
	void enterEvent(QEnterEvent* event) override; \
	void leaveEvent(QEvent* event) override;

#endif // CONTEXT_REQUEST_MACROS_H
