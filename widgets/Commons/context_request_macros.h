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

#define CONTEXT_HOVER_IMPL(ClassName)                                                      \
	void ClassName::enterEvent(QEnterEvent* event) {                                       \
		paintContext->handleHoverEvent(CCWidgetLibrary::HoverEventType::HOVER_IN, event);  \
	}                                                                                      \
	void ClassName::leaveEvent(QEvent* event) {                                            \
		paintContext->handleHoverEvent(CCWidgetLibrary::HoverEventType::HOVER_OUT, event); \
	}

#define CONTEXT_MOUSE_IMPL(ClassName)                                                          \
	void ClassName::mousePressEvent(QMouseEvent* event) {                                      \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_PRESS, event);   \
	}                                                                                          \
	void ClassName::mouseReleaseEvent(QMouseEvent* event) {                                    \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_RELEASE, event); \
	}                                                                                          \
	void ClassName::mouseMoveEvent(QMouseEvent* event) {                                       \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_MOVE, event);    \
	}

#define CONTEXT_MOUSE_IMPL_REQUEST_CALL_OLD(ClassName, OrgClass)                               \
	void ClassName::mousePressEvent(QMouseEvent* event) {                                      \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_PRESS, event);   \
		OrgClass::mousePressEvent(event);                                                      \
	}                                                                                          \
	void ClassName::mouseReleaseEvent(QMouseEvent* event) {                                    \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_RELEASE, event); \
		OrgClass::mouseReleaseEvent(event);                                                    \
	}                                                                                          \
	void ClassName::mouseMoveEvent(QMouseEvent* event) {                                       \
		paintContext->handleMouseEvent(CCWidgetLibrary::MouseEventType::MOUSE_MOVE, event);    \
		OrgClass::mouseMoveEvent(event);                                                       \
	}

#define CONTEXT_RESIZE_IMPL(ClassName)                 \
	void ClassName::resizeEvent(QResizeEvent* event) { \
		paintContext->handleResizeEvent(event);        \
	}

#define CONTEXT_PAINT_IMPL(ClassName, OrgClass)                       \
	void ClassName::paintEvent(QPaintEvent* event) {                  \
		if (!paintContext) {                                          \
			qWarning() << "paintContext NULL, use the default paint"; \
			OrgClass::paintEvent(event);                              \
		} else {                                                      \
			QPainter painter(this);                                   \
			paintContext->paint(painter);                             \
		}                                                             \
	}

#define CONTEXT_PAINT_IMPL_WITH_OLD(ClassName, OrgClass)              \
	void ClassName::paintEvent(QPaintEvent* event) {                  \
		if (!paintContext) {                                          \
			qWarning() << "paintContext NULL, use the default paint"; \
			OrgClass::paintEvent(event);                              \
		} else {                                                      \
			QPainter painter(this);                                   \
			OrgClass::paintEvent(event);                              \
			paintContext->paint(painter);                             \
		}                                                             \
	}

#define ALLOCATE_PAINTCONTEXT()                                                                  \
	do {                                                                                         \
		paintContext = CCWidgetLibrary::PaintContextAllocator::instance().allocate_paintContext( \
		    WIDGET_NAME, this);                                                                  \
		if (!paintContext) {                                                                     \
			qWarning() << "failed to allocate the paintContext";                                 \
		}                                                                                        \
	} while (0)

#endif // CONTEXT_REQUEST_MACROS_H
