#pragma once
#include <ctime>

using namespace std;

class DelayManager
{
private:
	clock_t startTime;
	int delayTime;
public:
	DelayManager();

	void SetDelayTime(const int& time);
	const int& GetDelayTime();

	void SetStartTime();

	const bool CkEndDelay();
};

