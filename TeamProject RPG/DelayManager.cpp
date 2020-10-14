#include "DelayManager.h"

DelayManager::DelayManager()
{
	startTime = clock();
	delayTime = 1000;
}

void DelayManager::SetDelayTime(const int& time)
{
	delayTime = time;
}

const int& DelayManager::GetDelayTime()
{
	return delayTime;
}

void DelayManager::SetStartTime()
{
	startTime = clock();
}

const bool DelayManager::CkEndDelay()
{	
	if (((clock() - startTime) > delayTime)) 
	{
		startTime = clock();

		return true;
	}

	return false;
}
