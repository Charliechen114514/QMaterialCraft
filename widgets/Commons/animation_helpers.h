#ifndef ANIMATION_HELPERS_H
#define ANIMATION_HELPERS_H
#include <QEasingCurve>
#include <QPointer>
#include <QVariant>
#include <QtClassHelperMacros>
#include <functional>
#include <stdexcept>

class QVariantAnimation;

namespace CCWidgetLibrary {

class InvalidAnimation : public std::runtime_error {
public:
	InvalidAnimation()
	    : std::runtime_error("Holding an invalid aniamtion!") { }
};

class AnimationHelper {
public:
	AnimationHelper(QVariantAnimation* binding_animations);
	AnimationHelper() = delete;
	Q_DISABLE_COPY_MOVE(AnimationHelper);

	~AnimationHelper();

	struct SettingsConfig {
		int period_time;
		QEasingCurve curve;
	};

	struct RuntimeConfig {
		QVariant start;
		QVariant end;
	};

	using ApplySettingsHandler = std::function<void(SettingsConfig&)>;
	using ApplyConfigHandler = std::function<void(RuntimeConfig&)>;

	AnimationHelper& applySettings(ApplySettingsHandler conf);
	AnimationHelper& applySession(ApplyConfigHandler conf);

private:
	QPointer<QVariantAnimation> holding_src {};
};

class AnimationHolder {
public:
	AnimationHolder() = delete;
	explicit AnimationHolder(QObject* attached_object = nullptr);
	explicit AnimationHolder(QObject* attached_object, QByteArray property);
	~AnimationHolder();
	Q_DISABLE_COPY_MOVE(AnimationHolder);

	inline AnimationHelper* get_helpers() const {
		return helpers.get();
	};

	inline QVariantAnimation* get_animations() const {
		return animations;
	}

private:
	std::unique_ptr<AnimationHelper> helpers;
	QVariantAnimation* animations;
};
}

#endif // ANIMATION_HELPERS_H
