/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOXTraceInterStreams.cpp
* 
* @class      DIOXTRACEINTERSTREAMS
* @brief      Data Input/Output XTrace InterStreams class
* @ingroup    DATAIO
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOXTraceInterStreams.h"

#include "XLog.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOXTRACEINTERSTREAMS::DIOXTRACEINTERSTREAMS(DIOSTREAM* DIOstream, bool iswithlog)
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* @param[in]  DIOstream : 
* @param[in]  iswithlog : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOXTRACEINTERSTREAMS::DIOXTRACEINTERSTREAMS(DIOSTREAM* DIOstream, bool iswithlog)
{
  Clean();

  this->DIOstream  = DIOstream;
  this->iswithlog = iswithlog;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOXTRACEINTERSTREAMS::~DIOXTRACEINTERSTREAMS()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOXTRACEINTERSTREAMS::~DIOXTRACEINTERSTREAMS()
{
  Clean();
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOXTRACEINTERSTREAMS::Process()
* @brief      Process
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOXTRACEINTERSTREAMS::Process()
{
  if(!DIOstream) return false;

  /*
  #ifdef XTRACE_ACTIVE

  XDWORD    publicIP;
  XDWORD    localIP;
  XBYTE     level;
  XDWORD    sequence;
  XDATETIME xtime;
  XBUFFER   data;

  if(!XTRACE::instance->GetTraceFromDIOStream(DIOstream, publicIP, localIP, level, sequence, &xtime, data))
    {
      if(iswithlog)
        {
          XLOGLEVEL xloglevel;

          switch(level & 0x0F)
            {

              case XTRACE_COLOR_BLACK  :
              case XTRACE_COLOR_BLUE   :
              case XTRACE_COLOR_GREEN  :
              case XTRACE_COLOR_GRAY   :
                               default : xloglevel = (XLOGLEVEL)XLOGLEVEL_INFO;      break;
              case XTRACE_COLOR_PURPLE : xloglevel = (XLOGLEVEL)XLOGLEVEL_WARNING;   break;
              case XTRACE_COLOR_RED    : xloglevel = (XLOGLEVEL)XLOGLEVEL_ERROR;     break;
            }

          GEN_XLOG.AddEntry(xloglevel, DIOXTRACEINTERSTREAMS_LOGSECTIONID, false, string.Get());
        }
       else
        {
          if(XTRACE::instance)
            {
              XTRACE::instance->Print(level, data.Get());
            }
        }
    }

  #endif
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOXTRACEINTERSTREAMS::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOXTRACEINTERSTREAMS::Clean()
{
  DIOstream  = NULL;
  iswithlog = false;
}


#pragma endregion






