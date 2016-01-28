//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//


#include "Nextpeer_WinRT.h"
#include "NextpeerNotifier.h"

#include <memory>
#include <string>
#include <cpprest/rawptrstream.h>
#include <cpprest/producerconsumerstream.h>

using namespace std;
using namespace web;
using namespace web::websockets::client;
using namespace Concurrency::streams;

//static std::wstring sUrl = L"ws://uforun2.azurewebsites.net:8080";
static std::wstring sUrl = L"ws://127.0.0.1:8080";
//static std::wstring sUrl = L"ws://echo.websocket.org";

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



	void Nextpeer_WinRT::initialize(const char* apiKey)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        m_ws.connect(sUrl.c_str()).then([](Concurrency::task<void> t)
        { /* We've finished connecting. */

            try
            {
                t.get();
            }
            catch (Platform::Exception^ ex)
            {
                Platform::String^ s = ex->ToString();

            }

          // This initializes the event queue and starts the scheduler
            NextpeerNotifier::getInstance()->queueScheduler();       
        });

        // set receive handler
        m_ws.set_message_handler([](websocket_incoming_message msg)
        {
            msg.extract_string().then([](std::string body) {
                NextpeerNotifier::getInstance()->broadcastReceiveSynchronizedEvent(CCString::create(NEXTPEER_NOTIFICATION_RECEIVE_SYNCHRONIZED_EVENT));
                std::string foo = body;
            });
        });

#endif
	}

	void Nextpeer_WinRT::launchDashboard()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        CCNotificationCenter::sharedNotificationCenter()->postNotification(NEXTPEER_NOTIFICATION_TOURNAMENT_STARTED, nullptr);
#endif
 	}

	void Nextpeer_WinRT::reportScoreForCurrentTournament(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		//callStaticVoidMethod("reportScoreForCurrentTournament", "(I)V", score);
        return;
#endif
	}

	void Nextpeer_WinRT::reportControlledTournamentOverWithScore(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		//callStaticVoidMethod("reportControlledTournamentOverWithScore", "(I)V", score);
#endif
	}

	void Nextpeer_WinRT::reportForfeitForCurrentTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		//callStaticVoidMethod("reportForfeitForCurrentTournament", "()V");
#endif
	}

	uint32_t Nextpeer_WinRT::timeLeftInTournament()
    {
        return 0;
	}

	bool Nextpeer_WinRT::isCurrentlyInTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)

		return true;
#endif
	}

	std::string Nextpeer_WinRT::getCurrentPlayerId()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        return string("");
#endif
	}

	std::string Nextpeer_WinRT::getCurrentPlayerName()
	{
        return string("");
	}

	void Nextpeer_WinRT::unreliablePushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
        if (length > 0)
        {
            pushData(pBuffer, length);
        }
	}

	void Nextpeer_WinRT::pushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
        if (length > 0)
        {
            pushData(pBuffer, length);
        }
	}

    void Nextpeer_WinRT::pushData(void* pBuffer, uint32_t length)
    {
        concurrency::streams::producer_consumer_buffer<uint8_t> pcbuf;

        auto send_task = pcbuf.putn_nocopy((uint8_t*)pBuffer, length).then([&](size_t length) {
            websocket_outgoing_message wom;
            wom.set_binary_message(pcbuf.create_istream(), length);
            return m_ws.send(wom);
        }).then([](pplx::task<void> t)
        {
            try
            {
                t.get();
            }
            catch (const websocket_exception& ex)
            {
                std::cout << ex.what();
            }
        });
        send_task.wait();
    }


    void Nextpeer_WinRT::enableRankingDisplay(bool enableRankingDisplay) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        //callStaticVoidMethod("enableRankingDisplay", "(Z)V", enableRankingDisplay);
#endif
    }
    
    void Nextpeer_WinRT::reportScoreModifierForRecording(const char* recordingPlayerId, int32_t modifier)
    {

    }

    void Nextpeer_WinRT::requestPauseRecording(const char* recordingPlayerId)
    {

    }

    void Nextpeer_WinRT::requestResumeRecording(const char* recordingPlayerId)
    {

    }

    void Nextpeer_WinRT::requestStopRecording(const char* recordingPlayerId)
    {


    }

    void Nextpeer_WinRT::requestRewindRecording(const char* recordingPlayerId, uint32_t timeDelta)
    {


    }

    void Nextpeer_WinRT::requestFastForwardRecording(const char* recordingPlayerId, uint32_t timeDelta)
    {

    }
    void Nextpeer_WinRT::registerToSynchronizedEvent(const char* eventName, uint32_t timeout)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        int syncTimeout = (int)(timeout > INT_MAX ? INT_MAX : timeout);
        //callStaticVoidMethod("registerToSynchronizedEvent", "(Ljava/lang/String;I)V", event, syncTimeout);
#endif
    }
} // namespace nextpeer

