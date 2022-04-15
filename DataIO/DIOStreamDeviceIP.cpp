/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOStreamDeviceIP.cpp
*
* @class      DIOSTREAMDEVICEIP
* @brief      Data Input/Output Stream Device IP class
* @ingroup    DATAIO
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XTrace.h"

#include "DIOStreamDeviceIP.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEIP::DIOSTREAMDEVICEIP()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEIP::DIOSTREAMDEVICEIP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMDEVICEIP::~ DIOSTREAMDEVICEIP()
* @brief      IOSTREAMDEVICEIP
* @ingroup    DATAIO
*
* @return     DIOSTREAMDEVICEIP::~ :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMDEVICEIP::~ DIOSTREAMDEVICEIP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOSTREAMDEVICEIP::GetIP()
* @brief      GetIP
* @ingroup    DATAIO
*
* @return     DIOIP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOSTREAMDEVICEIP::GetIP()
{
  return &IP;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMAC* DIOSTREAMDEVICEIP::GetMAC()
* @brief      GetMAC
* @ingroup    DATAIO
*
* @return     DIOMAC* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOMAC* DIOSTREAMDEVICEIP::GetMAC()
{
  return &MAC;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMIPDEVICE_TYPE DIOSTREAMDEVICEIP::GetIPType()
* @brief      GetIPType
* @ingroup    DATAIO
*
* @return     DIOSTREAMIPDEVICE_TYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMIPDEVICE_TYPE DIOSTREAMDEVICEIP::GetIPType()
{
  return iptype;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEIP::SetIPType(DIOSTREAMIPDEVICE_TYPE iptype)
* @brief      SetIPType
* @ingroup    DATAIO
*
* @param[in]  iptype :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEIP::SetIPType(DIOSTREAMIPDEVICE_TYPE iptype)
{
  this->iptype = iptype;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAMDEVICEIP::DebugPrintInfo()
* @brief      DebugPrintInfo
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAMDEVICEIP::DebugPrintInfo()
{
  XSTRING line;
  XSTRING data;

  DIOSTREAMDEVICE::DebugPrintInfo();

  DIOSTREAMIPDEVICE_TYPE IPtype = GetIPType();

  switch(IPtype)
    {                           default       :
      case DIOSTREAMIPDEVICE_TYPE_UNKNOWN     : data = __L("Unknown");      break;
      case DIOSTREAMIPDEVICE_TYPE_ETHERNET    : data = __L("Ethernet");     break;
      case DIOSTREAMIPDEVICE_TYPE_WIFI        : data = __L("Wi-Fi");        break;
      case DIOSTREAMIPDEVICE_TYPE_PPP         : data = __L("PPP");          break;
      case DIOSTREAMIPDEVICE_TYPE_LOOPBACK    : data = __L("Loopback");     break;
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Type             : %s") , data.Get());

  GetMAC()->GetXString(data);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("MAC              : %s") , data.Get());

  GetIP()->GetXString(data);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("IP               : %s") , data.Get());

 
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAMDEVICEIP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAMDEVICEIP::Clean()
{
  type   = DIOSTREAMDEVICE_TYPE_IP;

  iptype = DIOSTREAMIPDEVICE_TYPE_UNKNOWN;
}



