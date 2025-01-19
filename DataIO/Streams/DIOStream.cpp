/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStream.cpp
* 
* @class      DIOSTREAM
* @brief      Data Input/Output Stream class
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

#include "DIOStream.h"

#include <string.h>

#include "XFactory.h"
#include "XBuffer.h"
#include "XTimer.h"

#include "DIOStream_XEvent.h"

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
* @fn         DIOSTREAM::DIOSTREAM()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM::DIOSTREAM()
{
  Clean();

  inbuffer  = new XBUFFER();
  outbuffer = new XBUFFER();

  GEN_XFACTORY_CREATE(xmutextimerout    , Create_Mutex())
  GEN_XFACTORY_CREATE(xtimerconnection  , CreateTimer())
  GEN_XFACTORY_CREATE(xtimernotactivity , CreateTimer())
  GEN_XFACTORY_CREATE(xtimerout         , CreateTimer())
  
  RegisterEvent(DIOSTREAM_XEVENT_TYPE_GETTINGCONNECTION);
  RegisterEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED);
  RegisterEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAM::~DIOSTREAM()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAM::~DIOSTREAM()
{
  if(inbuffer)
    {
      delete inbuffer;
      inbuffer = NULL;
    }

  if(outbuffer)
    {
      delete outbuffer;
      outbuffer = NULL;
    }

  if(xmutextimerout) xmutextimerout->Lock();

  if(xtimerout)
    {
      GEN_XFACTORY.DeleteTimer(xtimerout);
      xtimerout = NULL;
    }

  if(xmutextimerout) xmutextimerout->UnLock();

  if(xtimerconnection)
    {
      GEN_XFACTORY.DeleteTimer(xtimerconnection);
      xtimerconnection = NULL;
    }

  if(xtimernotactivity)
    {
      GEN_XFACTORY.DeleteTimer(xtimernotactivity);
      xtimernotactivity = NULL;
    }

  if(xmutextimerout)
    {
      GEN_XFACTORY.Delete_Mutex(xmutextimerout);
      xmutextimerout = NULL;
    }

  DeRegisterEvent(DIOSTREAM_XEVENT_TYPE_GETTINGCONNECTION);
  DeRegisterEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED);
  DeRegisterEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED);

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMSTATUS DIOSTREAM::GetStatus()
* @brief      Get status
* @ingroup    DATAIO
*
* @return     DIOSTREAMSTATUS :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMSTATUS DIOSTREAM::GetStatus()
{
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTREAM::SetStatus(DIOSTREAMSTATUS status)
* @brief      Set status
* @ingroup    DATAIO
* 
* @param[in]  status : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::SetStatus(DIOSTREAMSTATUS status)
{
  this->status = status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsConnected()
* @brief      Is connected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsConnected()
{
  if(GetStatus()==DIOSTREAMSTATUS_CONNECTED) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsDisconnected()
* @brief      Is disconnected
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsDisconnected()
{
  if(GetStatus()==DIOSTREAMSTATUS_DISCONNECTED) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WaitToConnected(int timeout)
* @brief      Wait to connected
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WaitToConnected(int timeout)
{
  if(!xtimerconnection) 
    {
      return false;
    }

  bool status = false;

  xtimerconnection->Reset();  

  while(1)
    {
      if(IsConnected())
        {
          status = true;
          break;
        }
      
      if(GetStatus() == DIOSTREAMSTATUS_DISCONNECTED)
        {
          break;
        }
      

      if((int)xtimerconnection->GetMeasureSeconds() >= timeout)
        {
          break;
        }

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WaitToDisconnected(int timeout)
* @brief      Wait to disconnected
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WaitToDisconnected(int timeout)
{
  if(!xtimerconnection) return false;

  bool status = false;

  xtimerconnection->Reset();

  while(1)
    {
      if(IsDisconnected())
        {
          status = true;
          break;
        }

      if((int)xtimerconnection->GetMeasureSeconds() >= timeout) break;

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::Read(XBYTE* buffer, XDWORD size)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::Read(XBYTE* buffer, XDWORD size)
{
  if(!inbuffer) return false;

  XDWORD esize = inbuffer->Extract(buffer,0,size);

  if(esize)
    {
      nbytesread+=size;
      if(xtimernotactivity) xtimernotactivity->Reset();
    }

  return esize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::Write(XBYTE* buffer, XDWORD size)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  buffer :
* @param[in]  size :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::Write(XBYTE* buffer, XDWORD size)
{
  if(!outbuffer)                    return 0;
  if(!outbuffer->Add(buffer,size))  return 0;

  nbyteswrite+=size;
  if(xtimernotactivity) xtimernotactivity->Reset();

  return size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::Read(XBUFFER& xbuffer)
* @brief      Read
* @ingroup    DATAIO
*
* @param[in]  xbuffer :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::Read(XBUFFER& xbuffer)
{
  if(inbuffer->IsEmpty()) return 0;

  XDWORD br = Read(xbuffer.Get(), xbuffer.GetSize());
  if(br)
    {
      if(br!=xbuffer.GetSize()) xbuffer.Resize(br);
    }
   else
    {
      xbuffer.Delete();
    }

  return xbuffer.GetSize();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::Write(XBUFFER& xbuffer)
* @brief      Write
* @ingroup    DATAIO
*
* @param[in]  xbuffer :
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::Write(XBUFFER& xbuffer)
{
  return Write(xbuffer.Get(),xbuffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WaitToFilledReadingBuffer(int filledto, int timeout)
* @brief      Wait to filled reading buffer
* @ingroup    DATAIO
*
* @param[in]  filledto :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WaitToFilledReadingBuffer(int filledto, int timeout)
{
  if(!xtimerout)  return false;

  bool status = true;

  xtimerout->Reset();

  if(xmutextimerout) xmutextimerout->Lock();

  while(1)
    {
      if(filledto == DIOSTREAM_SOMETHINGTOREAD)
        {
          if(GetInXBuffer()->GetSize()) break;
        }
       else
        {
          if((int)GetInXBuffer()->GetSize() >= filledto) break;
        }

      if(timeout!=XTIMER_INFINITE)
        {
          if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeout)
            {
              status = false;
              break;
            }
        }

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  if(xmutextimerout) xmutextimerout->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ReadStr(char* str)
* @brief      Read str
* @ingroup    DATAIO
*
* @param[in]  str :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ReadStr(char* str)
{
  if(!str) return false;

  XSTRING string;
  bool    status = ReadStr(string);

  XBUFFER charstr;
  
  string.ConvertToASCII(charstr);  
  memcpy(str, charstr.Get(), string.GetSize());
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ReadStr(XSTRING& string)
* @brief      Read str
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ReadStr(XSTRING& string)
{
  bool foundreturn = false;
  int  stringsize  = 0;

  inbuffer->SetBlocked(true);

  for(int c=0;c<(int)inbuffer->GetSize();c++)
    {
      if((inbuffer->GetByte(c) =='\n') || (inbuffer->GetByte(c) == '\r'))
        {
          stringsize++;

          if(c+1<(int)inbuffer->GetSize())
            {
              if((inbuffer->GetByte(c+1) == '\n') || (inbuffer->GetByte(c+1) =='\r')) stringsize++;
            }

          foundreturn = true;

          break;

        } else stringsize++;
    }

  inbuffer->SetBlocked(false);

  if(!foundreturn) return false;

  XBYTE* buffer = new XBYTE[stringsize+1];
  if(!buffer) return false;

  memset(buffer, 0, stringsize+1);

  int br = Read((XBYTE*)buffer, stringsize);

  if(br != stringsize) return false;

  int c=(int)strlen((const char*)buffer);
  while(c>=0)
    {
      if((buffer[c]=='\n')||(buffer[c]=='\r')) buffer[c]=0;
      c--;
    }

  string.Empty();
  string = (char*)buffer;

  delete [] buffer;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ReadStr(XSTRING& string, int timeout)
* @brief      Read str
* @ingroup    DATAIO
*
* @param[in]  string :
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ReadStr(XSTRING& string, int timeout)
{
  bool status = true;

  if(!xtimerout) return false;

  xtimerout->Reset();

  if(xmutextimerout) xmutextimerout->Lock();

  while(!ReadStr(string))
    {
      if((int)xtimerout->GetMeasureSeconds() >= timeout)
        {
          status = false;
          break;
        }
    }

  if(xmutextimerout) xmutextimerout->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WriteStr(const char* str)
* @brief      Write str
* @ingroup    DATAIO
*
* @param[in]  str :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WriteStr(const char* str)
{
  if(!str) return false;

  if(!Write((XBYTE*)str,(XDWORD)strlen(str))) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WriteStr(XCHAR* string)
* @brief      Write str
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WriteStr(XCHAR* string)
{
  XSTRING str(string);

  XBUFFER charstr;
  
  str.ConvertToASCII(charstr);
  
  return WriteStr(charstr.GetPtrChar());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WriteStr(XSTRING& string)
* @brief      Write str
* @ingroup    DATAIO
*
* @param[in]  string :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WriteStr(XSTRING& string)
{
  XBUFFER charstr;
  
  string.ConvertToASCII(charstr);
  
  return WriteStr(charstr.GetPtrChar());  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsBlockRead()
* @brief      Is block read
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsBlockRead()
{
  return isblockread;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::SetIsBlockRead(bool isblockread)
* @brief      Set is block read
* @ingroup    DATAIO
*
* @param[in]  isblockread :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::SetIsBlockRead(bool isblockread)
{
  this->isblockread = isblockread;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsBlockWrite()
* @brief      Is block write
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsBlockWrite()
{
  return isblockwrite;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::SetIsBlockWrite(bool isblockwrite)
* @brief      Set is block write
* @ingroup    DATAIO
*
* @param[in]  isblockwrite :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::SetIsBlockWrite(bool isblockwrite)
{
  this->isblockwrite = isblockwrite;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::Disconnect()
* @brief      Disconnect
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::Disconnect()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMTYPE DIOSTREAM::GetType()
* @brief      Get type
* @ingroup    DATAIO
*
* @return     DIOSTREAMTYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMTYPE DIOSTREAM::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::SetType(DIOSTREAMTYPE type)
* @brief      Set type
* @ingroup    DATAIO
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::SetType(DIOSTREAMTYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOSTREAM::GetInXBuffer()
* @brief      Get in X buffer
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOSTREAM::GetInXBuffer()
{
  return inbuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBUFFER* DIOSTREAM::GetOutXBuffer()
* @brief      Get out X buffer
* @ingroup    DATAIO
*
* @return     XBUFFER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* DIOSTREAM::GetOutXBuffer()
{
  return outbuffer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ResetXBuffers()
* @brief      Reset X buffers
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ResetXBuffers()
{
  if((!inbuffer) && (!outbuffer)) return false;

  inbuffer->Delete();
  outbuffer->Delete();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ResetInXBuffer()
* @brief      Reset in X buffer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ResetInXBuffer()
{
  if(!inbuffer) return false;

  inbuffer->Delete();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ResetOutXBuffer()
* @brief      Reset out X buffer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ResetOutXBuffer()
{
  if(!outbuffer) return false;

  outbuffer->Delete();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsFlushOutXBuffer()
* @brief      Is flush out X buffer
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsFlushOutXBuffer()
{
  if(!outbuffer) return false;

  if(outbuffer->GetSize()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::IsFlushXBuffers()
* @brief      Is flush X buffers
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::IsFlushXBuffers()
{
  if((!inbuffer) && (!outbuffer)) return false;

  if(inbuffer->GetSize())  return false;
  if(outbuffer->GetSize()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WaitToFlushOutXBuffer(int timeout)
* @brief      Wait to flush out X buffer
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WaitToFlushOutXBuffer(int timeout)
{
  if(!xtimerout) return false;

  bool status = true;

  xtimerout->Reset();

  if(xmutextimerout) xmutextimerout->Lock();

  while(!IsFlushOutXBuffer())
    {
      if(timeout != XTIMER_INFINITE)
        {
          if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeout)
            {
              ResetOutXBuffer();

              status = false;
              break;
            }
        }

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  if(xmutextimerout) xmutextimerout->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::WaitToFlushXBuffers(int timeout)
* @brief      Wait to flush X buffers
* @ingroup    DATAIO
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::WaitToFlushXBuffers(int timeout)
{
  if(!xtimerout) return false;

  bool status = true;

  xtimerout->Reset();

  if(xmutextimerout) xmutextimerout->Lock();

  while(!IsFlushXBuffers())
    {
      if(timeout!=XTIMER_INFINITE)
        {
          if(xtimerout->GetMeasureSeconds() >= (XDWORD)timeout)
            {
              ResetXBuffers();

              status = false;
              break;
            }
        }

      Wait(DIOSTREAM_TIMEINWAITFUNCTIONS);
    }

  if(xmutextimerout) xmutextimerout->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOSTREAM::GetXTimerConnection()
* @brief      Get X timer connection
* @ingroup    DATAIO
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOSTREAM::GetXTimerConnection()
{
  return xtimerconnection;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* DIOSTREAM::GetXTimerNotActivity()
* @brief      Get X timer not activity
* @ingroup    DATAIO
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* DIOSTREAM::GetXTimerNotActivity()
{
  return xtimernotactivity;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::GetNBytesRead()
* @brief      Get N bytes read
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::GetNBytesRead()
{
  return nbytesread;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTREAM::AddNBytesRead(XDWORD size)
* @brief      Add N bytes read
* @ingroup    DATAIO
* 
* @param[in]  size : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::AddNBytesRead(XDWORD size)
{
  nbytesread += size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DIOSTREAM::GetNBytesWrite()
* @brief      Get N bytes write
* @ingroup    DATAIO
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOSTREAM::GetNBytesWrite()
{
  return nbyteswrite;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSTREAM::AddNBytesWrite(XDWORD size)
* @brief      Add N bytes write
* @ingroup    DATAIO
* 
* @param[in]  size : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::AddNBytesWrite(XDWORD size)
{
  nbyteswrite += size;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSTREAMERROR DIOSTREAM::GetLastDIOError()
* @brief      Get last DIO error
* @ingroup    DATAIO
*
* @return     DIOSTREAMERROR :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMERROR DIOSTREAM::GetLastDIOError()
{
  DIOSTREAMERROR ret = error;

  error = DIOSTREAMERROR_NONE;
  return ret;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::SetLastDIOError(DIOSTREAMERROR error)
* @brief      Set last DIO error
* @ingroup    DATAIO
*
* @param[in]  error :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::SetLastDIOError(DIOSTREAMERROR error)
{
  this->error = error;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::Wait(int milliseconds)
* @brief      Wait
* @ingroup    DATAIO
*
* @param[in]  milliseconds :
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::Wait(int milliseconds)
{
  GEN_XSLEEP.MilliSeconds(milliseconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSTREAM::ResetConnectionStatistics()
* @brief      Reset connection statistics
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSTREAM::ResetConnectionStatistics()
{
  nbytesread  = 0;
  nbyteswrite = 0;

  if(xtimerconnection)   xtimerconnection->Reset();
  if(xtimernotactivity) xtimernotactivity->Reset();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSTREAM::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSTREAM::Clean()
{
  type                = DIOSTREAMTYPE_UNKNOWN;

  status              = DIOSTREAMSTATUS_GETTINGCONNECTION;
  error               = DIOSTREAMERROR_NONE;

  xtimerconnection    = NULL;
  xtimernotactivity   = NULL;
  xtimerout           = NULL;

  xmutextimerout      = NULL;

  inbuffer            = NULL;
  outbuffer           = NULL;

  isblockread         = false;
  isblockwrite        = false;

  nbytesread          = 0;
  nbyteswrite         = 0;
}


#pragma endregion

