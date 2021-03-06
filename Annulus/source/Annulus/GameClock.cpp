#include "pch.h"
#include "GameClock.h"
#include "GameTime.h"
#include <chrono>

using namespace std::chrono;

namespace Annulus
{
	GameClock::GameClock() : mStartTime(), mCurrentTime(), mLastTime()
	{
		Reset();
	}

	const high_resolution_clock::time_point& GameClock::StartTime() const
	{
		return mStartTime;
	}

	const high_resolution_clock::time_point& GameClock::CurrentTime() const
	{
		return mCurrentTime;
	}

	const high_resolution_clock::time_point& GameClock::LastTime() const
	{
		return mLastTime;
	}

	void GameClock::Reset()
	{
		mStartTime = high_resolution_clock::now();
		mCurrentTime = mStartTime;
		mLastTime = mCurrentTime;
	}

	void GameClock::UpdateGameTime(GameTime& gameTime)
	{
		mCurrentTime = high_resolution_clock::now();

		gameTime.SetCurrentTime(mCurrentTime);
		gameTime.SetTotalGameTime((mCurrentTime - mStartTime));
		gameTime.SetElapsedGameTime((mCurrentTime - mLastTime));
		mLastTime = mCurrentTime;
	}
}