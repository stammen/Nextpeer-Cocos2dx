//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//


#include "Nextpeer_WinRT.h"
#include "NextpeerNotifier.h"



using namespace std;


// CCNextpeer
namespace nextpeer
{
    CCNextpeer::CCNextpeer() {}
    CCNextpeer::~CCNextpeer() {}
    CCNextpeer* CCNextpeer::getInstance()
    {
        return Nextpeer_WinRT::getInstance();
    }
}

// Nextpeer_WinRT
namespace nextpeer
{
    Nextpeer_WinRT* Nextpeer_WinRT::_sharedInstance = NULL;

    Nextpeer_WinRT* Nextpeer_WinRT::getInstance()
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
            if (_sharedInstance == NULL) {
                _sharedInstance = new Nextpeer_WinRT();
            }
        #endif

        return _sharedInstance;
    }

	const char *NextpeerClass = "com.nextpeer.android.NextpeerCocos2DX";

	/*
		Helper function for calling static functions on the main Nextpeer class
	 */
	static void callStaticVoidMethod(const char *name, const char *signature, ...)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if ( cocos2d::JniHelper::getStaticMethodInfo( methodInfo,
												NextpeerClass,
				                                name,
				                                signature) ) {
			va_list args;
			va_start(args, signature);
			methodInfo.env->CallStaticVoidMethodV(methodInfo.classID, methodInfo.methodID, args);
			va_end(args);
		}
#endif
	}

	static int callStaticIntMethod(const char *name, const char *signature, ...)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		jint ret = 0;

		if ( cocos2d::JniHelper::getStaticMethodInfo( methodInfo,
												NextpeerClass,
				                                name,
				                                signature) ) {
			va_list args;
			va_start(args, signature);
			ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, args);
			va_end(args);
		}
		return ret;
#else
		return 0;
#endif
	}


	void Nextpeer_WinRT::initialize(const char* apiKey)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "initialize", "(Ljava/lang/String;)V")) {
			jstring stringArg = methodInfo.env->NewStringUTF(apiKey);
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
			methodInfo.env->DeleteLocalRef(stringArg);
		}

        // This initializes the event queue and starts the scheduler
        NextpeerNotifier::getInstance()->queueScheduler();
#endif
	}

	void Nextpeer_WinRT::launchDashboard()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("launch", "()V");
#endif
 	}

	void Nextpeer_WinRT::reportScoreForCurrentTournament(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportScoreForCurrentTournament", "(I)V", score);
#endif
	}

	void Nextpeer_WinRT::reportControlledTournamentOverWithScore(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportControlledTournamentOverWithScore", "(I)V", score);
#endif
	}

	void Nextpeer_WinRT::reportForfeitForCurrentTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportForfeitForCurrentTournament", "()V");
#endif
	}

	uint32_t Nextpeer_WinRT::timeLeftInTournament()
    {
        return 0;
	}

	bool Nextpeer_WinRT::isCurrentlyInTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;
		jboolean ret = 0;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "isCurrentlyInTournament", "()Z")) {
			ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		}

		return (bool)ret;
#else
		return false;
#endif
	}

	std::string Nextpeer_WinRT::getCurrentPlayerId()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "getCurrentPlayerId", "()Ljava/lang/String;")) {
			jstring id = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
			if (!id) return string("");

			return cocos2d::JniHelper::jstring2string(id);
		}
		else {
			return string("");
		}
#else
		return string("");
#endif
	}

	std::string Nextpeer_WinRT::getCurrentPlayerName()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "getCurrentPlayerName", "()Ljava/lang/String;")) {
			jstring name = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
			if (!name) return string("");

			return cocos2d::JniHelper::jstring2string(name);
		}
#endif
        return string("");
	}

	void Nextpeer_WinRT::unreliablePushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (length == 0) return;

		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "unreliablePushDataToOtherPlayers", "([B)V")) {
			jbyteArray javaArray = methodInfo.env->NewByteArray(length);
			methodInfo.env->SetByteArrayRegion(javaArray, 0, length, (const jbyte*)pBuffer);

			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, javaArray);

			methodInfo.env->DeleteLocalRef(javaArray);
		}
#endif
	}

	void Nextpeer_WinRT::pushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (length == 0) return;

		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "pushDataToOtherPlayers", "([B)V")) {
			jbyteArray javaArray = methodInfo.env->NewByteArray(length);
			methodInfo.env->SetByteArrayRegion(javaArray, 0, length, (const jbyte*)pBuffer);

			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, javaArray);

			methodInfo.env->DeleteLocalRef(javaArray);
		}
#endif
	}

    void Nextpeer_WinRT::enableRankingDisplay(bool enableRankingDisplay) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        callStaticVoidMethod("enableRankingDisplay", "(Z)V", enableRankingDisplay);
#endif
    }
    void Nextpeer_WinRT::reportScoreModifierForRecording(const char* recordingPlayerId, int32_t modifier)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);
        jint jModifier = (jint)(modifier > INT_MAX ? INT_MAX : modifier);

        callStaticVoidMethod("requestRecordingControlScoreModifier", "(Ljava/lang/String;I)V", playerId, jModifier);

        env->DeleteLocalRef(playerId);
#endif
    }

    void Nextpeer_WinRT::requestPauseRecording(const char* recordingPlayerId)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);

        callStaticVoidMethod("requestRecordingControlPauseRecording", "(Ljava/lang/String;)V", playerId);

        env->DeleteLocalRef(playerId);
#endif
    }

    void Nextpeer_WinRT::requestResumeRecording(const char* recordingPlayerId)
    {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);

        callStaticVoidMethod("requestRecordingControlResumeRecording", "(Ljava/lang/String;)V", playerId);

        env->DeleteLocalRef(playerId);
#endif
    }

    void Nextpeer_WinRT::requestStopRecording(const char* recordingPlayerId)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);

        callStaticVoidMethod("requestRecordingControlStopRecording", "(Ljava/lang/String;)V", playerId);

        env->DeleteLocalRef(playerId);
#endif

    }

    void Nextpeer_WinRT::requestRewindRecording(const char* recordingPlayerId, uint32_t timeDelta)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);
        jint delta = (jint)(timeDelta > INT_MAX ? INT_MAX : timeDelta);

        callStaticVoidMethod("requestRecordingControlRewindRecording", "(Ljava/lang/String;I)V", playerId, timeDelta);

        env->DeleteLocalRef(playerId);
#endif

    }

    void Nextpeer_WinRT::requestFastForwardRecording(const char* recordingPlayerId, uint32_t timeDelta)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JNIEnv* env = NULL;
        if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

        jstring playerId = (jstring)env->NewStringUTF(recordingPlayerId);
        jint delta = (jint)(timeDelta > INT_MAX ? INT_MAX : timeDelta);

        callStaticVoidMethod("requestRecordingControlFastForwardRecording", "(Ljava/lang/String;I)V", playerId, timeDelta);

        env->DeleteLocalRef(playerId);
#endif
    }
        void Nextpeer_WinRT::registerToSynchronizedEvent(const char* eventName, uint32_t timeout)
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            JNIEnv* env = NULL;
            if (!Nextpeer_WinRTJNIHelper::getEnv(&env)) return;

            jstring event = (jstring)env->NewStringUTF(eventName);
            jint syncTimeout = (jint)(timeout > INT_MAX ? INT_MAX : timeout);

            callStaticVoidMethod("registerToSynchronizedEvent", "(Ljava/lang/String;I)V", event, syncTimeout);

            env->DeleteLocalRef(event);
#endif
    }
} // namespace nextpeer

