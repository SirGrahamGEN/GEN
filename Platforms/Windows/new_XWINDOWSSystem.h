/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSSystem.h
* 
* @class      XWINDOWSSYSTEM
* @brief      WINDOWS eXtended Utils System class
* @ingroup    PLATFORM_WINDOWS
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

#ifndef _XWINDOWSSYSTEM_H_
#define _XWINDOWSSYSTEM_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <psapi.h>

#include "XSystem.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define XWINDOWSSYSTEM_MAXNETADDRIP															16

#define XWINDOWSSYSTEM_SYSTEM_OBJECT_INDEX											2					// 'System' object
#define XWINDOWSSYSTEM_PROCESS_OBJECT_INDEX											230				// 'Process' object
#define XWINDOWSSYSTEM_PROCESSOR_OBJECT_INDEX										238				// 'Processor' object
#define XWINDOWSSYSTEM_TOTAL_PROCESSOR_TIME_COUNTER_INDEX				240				// '% Total processor time' counter (valid in WinNT under 'System' object)
#define XWINDOWSSYSTEM_PROCESSOR_TIME_COUNTER_INDEX							6					// '% processor time' counter (for Win2K/XP)

#define XWINDOWSSYSTEM_TOTALBYTES																100*1024
#define XWINDOWSSYSTEM_BYTEINCREMENT														10*1024


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XWINDOWSWMIINTERFACE;


class XWINDOWSSYSTEM : public XSYSTEM
{
  public:
																								XWINDOWSSYSTEM																		();
    virtual																		 ~XWINDOWSSYSTEM																		();

    XSYSTEM_HARDWARETYPE												GetTypeHardware													          (int* revision = NULL);

		XSYSTEM_PLATFORM														GetPlatform																				(XSTRING* namestring = NULL);	

		bool																				GetOperativeSystemID  														(XSTRING& ID);

    XDWORD																			GetLanguageSO																			();

    XSTRING*																		GetBIOSSerialNumber																();

		XSTRING*																		GetCPUSerialNumber																();

		float																				GetCPUTemperature																	();

    bool																				GetMemoryInfo																			(XDWORD& total,XDWORD& free);
		
		int																					GetCPUUsageTotal																	();
    int																					GetCPUUsageForProcessName													(XCHAR* processname);
    int																					GetCPUUsageForProcessID														(XDWORD processID);

    XCHAR*																			GetEnviromentVariable															(XCHAR* variablename);
    bool																				SetEnviromentVariable															(XCHAR* variablename, XCHAR* value);
    bool																				DelEnviromentVariable															(XCHAR* variablename);

		bool																				GetUserAndDomain																	(XSTRING& user, XSTRING& domain);

    bool																				ShutDown																					(XSYSTEM_CHANGESTATUSTYPE type);

    int																					Sound_GetLevel																		();  
    bool																				Sound_SetLevel																		(int level); 
    bool																				Sound_SetMutex																		(bool on);   

		bool																				GetBatteryLevel																		(bool& isincharge, XBYTE& levelpercent);  

  private:
			
    uint64_t																		FileTime2UTC																			(const FILETIME *ftime);

    void																				Clean																							();
				
		XWINDOWSWMIINTERFACE*												wmiinterface;		
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

