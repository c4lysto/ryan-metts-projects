#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include <Windows.h>

class CriticalSection
{
private:
	CRITICAL_SECTION m_CriticalSection;

public:
	CriticalSection(DWORD dwSpinCount = 1000);
	~CriticalSection();

	void Lock();
	bool TryLock();
	void Unlock();
};

class ScopedCriticalSection
{
private:
	CriticalSection& m_CriticalSection;

public:
	ScopedCriticalSection(CriticalSection& critSection, bool bAutoLock = true);
	~ScopedCriticalSection();
};
#endif