#pragma once
#include "diskdrive.h"
class CCheckDisk :
	public CDiskDrive
{
public:
	CCheckDisk(void);
	~CCheckDisk(void);


private:
	HANDLE m_hDisks;
	UINT m_DiskCount;
};

