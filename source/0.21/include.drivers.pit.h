// I think we should venture out of the WYOOS tutorial for the first time.

#ifndef __PIT_H // It's October 2024. I'm slowly rebooting this project, as seen with NanamiOS 1.00.29 (considered 0.09.30).
#define __PIT_H

	#include "include.common.types.h"
	#include "include.drivers.driver.h"
	#include "include.hwcom.port.h"
	
	class ProgrammableIntervalTimer : public Driver
	{
		Port8Bit Channel0;
		Port8Bit Channel1;
		Port8Bit Channel2;
		Port8Bit PITComPort;
		
	public:
		ProgrammableIntervalTimer();
		~ProgrammableIntervalTimer();
		
		uint32_t ReadPIT();
		void SetPITCount(uint32_t count);
	}; // initially forgot a semicolon (almost said semilion for some reason) -▿-

#endif