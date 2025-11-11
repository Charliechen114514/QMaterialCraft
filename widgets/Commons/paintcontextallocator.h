#ifndef PAINTCONTEXTALLOCATOR_H
#define PAINTCONTEXTALLOCATOR_H
#include "CCWidgets_BuildDefine.h"
#include "TextIndiator.h"
#include "paintcontext.h"
#include <QMap>
class QAbstractItemView;
namespace CCWidgetLibrary {
class ContainerCommonDelegate;

class CCWIDGET_EXPORT PaintContextAllocator : public QObject {
	Q_OBJECT
public:
	friend class PaintContextRegisters;
	static PaintContextAllocator& instance();
	static void setThemes(const QString& themes /* Unused Current */);
	using RegisterActor = std::function<PaintContext*(QWidget*)>;
	using DelegateRegisterActor = std::function<ContainerCommonDelegate*(QAbstractItemView*)>;
	enum class ActPolicy {
		AUTO,
		MANUAL
	};

	void setStyles(const QString& current_style);

	TextIndiator* text_indicator() const;

	PaintContext* allocate_paintContext(
	    const QString& paintContextName, QWidget* who, ActPolicy policy = ActPolicy::AUTO);

	void runRegister(const QString& paintContextName,
	                 RegisterActor actor, ActPolicy policy = ActPolicy::AUTO);

	void runDelegateRegister(const QString& delegateName,
	                         DelegateRegisterActor actor,
	                         ActPolicy policy = ActPolicy::AUTO);

	ContainerCommonDelegate* allocate_delegate(
	    const QString& delegate_name,
	    QAbstractItemView* view,
	    ActPolicy policy = ActPolicy::AUTO);

signals:
	void styleChanged(QString current_style);

private:
	PaintContextAllocator();
	Q_DISABLE_COPY_MOVE(PaintContextAllocator);

	QString composed_style(const QString& widget_name);
	std::unique_ptr<TextIndiator> textIndicator;
	QMap<QString, RegisterActor> factory;
	QMap<QString, DelegateRegisterActor> delegate_factory;
	QString current_style;
};
}

#endif // PAINTCONTEXTALLOCATOR_H
