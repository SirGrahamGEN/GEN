/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOPing.cpp
* 
* @class      DIOPING
* @brief      Data Input/Output Ping protocol class
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

#include "DIOPing.h"

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XTimer.h"
#include "XTrace.h"
#include "XRand.h"

#include "DIOStreamICMPConfig.h"
#include "DIOStreamICMP.h"
#include "DIOFactory.h"
#include "HashCRC32.h"

#include "DIOPing_XEvent.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

DIOPING* DIOPING::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_DIOPINGREPLY


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPINGREPLY::DIOPINGREPLY()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPINGREPLY::DIOPINGREPLY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPINGREPLY::~DIOPINGREPLY()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPINGREPLY::~DIOPINGREPLY()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPINGREPLY::GetSequence()
* @brief      Get sequence
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPINGREPLY::GetSequence()
{
  return sequence;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPINGREPLY::SetSequence(XDWORD sequence)
* @brief      Set sequence
* @ingroup    DATAIO
* 
* @param[in]  sequence : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPINGREPLY::SetSequence(XDWORD sequence)
{
  this->sequence  = sequence;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSTRING* DIOPINGREPLY::GetFromIP()
* @brief      Get from IP
* @ingroup    DATAIO
* 
* @return     XSTRING* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOPINGREPLY::GetFromIP()
{
  return &fromIP;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPINGREPLY::GetSizeRequest()
* @brief      Get size request
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPINGREPLY::GetSizeRequest()
{
  return sizerequest;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPINGREPLY::SetSizeRequest(XDWORD sizerequest)
* @brief      Set size request
* @ingroup    DATAIO
* 
* @param[in]  sizerequest : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPINGREPLY::SetSizeRequest(XDWORD sizerequest)
{
  this->sizerequest = sizerequest;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPINGREPLY::GetTimeElapsed()
* @brief      Get time elapsed
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPINGREPLY::GetTimeElapsed()
{
  return timeelapsed;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPINGREPLY::SetTimeElapsed(XDWORD timeelapsed)
* @brief      Set time elapsed
* @ingroup    DATAIO
* 
* @param[in]  timeelapsed : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPINGREPLY::SetTimeElapsed(XDWORD timeelapsed)
{
  this->timeelapsed = timeelapsed;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE DIOPINGREPLY::GetTTL()
* @brief      Get TTL
* @ingroup    DATAIO
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE DIOPINGREPLY::GetTTL()
{
  return TTL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPINGREPLY::SetTTL(XBYTE TTL)
* @brief      Set TTL
* @ingroup    DATAIO
* 
* @param[in]  TTL : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPINGREPLY::SetTTL(XBYTE TTL)
{
  this->TTL = TTL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPINGREPLY::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPINGREPLY::Clean()
{
  sequence      = 0;

  fromIP.Empty();

  sizerequest   = 0;
  timeelapsed   = 0;
  TTL           = 0;
}


#pragma endregion


#pragma region CLASS_DIOPING


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPING::DIOPING()
* @brief      Constructor of class
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPING::DIOPING()
{
  Clean();

  RegisterEvent(DIOPING_XEVENT_TYPE_DOPING);

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())
  GEN_XFACTORY_CREATE(xmutexreplys, Create_Mutex())

  urltarget = new DIOURL();

  HASHCRC32 crc32;  
  XBUFFER   xbuffer;
  
  XRAND* GEN_XFACTORY_CREATE(xrand, CreateRand())
  if(xrand)
    {
      for(int c=0; c<128; c++)
        {
          xbuffer.Add((XBYTE)xrand->Max(255));
        }

      crc32.ResetResult();
      crc32.Do(xbuffer);
      applicationID = crc32.GetResultCRC32();

      GEN_XFACTORY.DeleteRand(xrand);
    }

  GEN_XFACTORY_CREATE(xmutexping, Create_Mutex());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPING::~DIOPING()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPING::~DIOPING()
{
  DeRegisterEvent(DIOPING_XEVENT_TYPE_DOPING);

  DeleteAllReplys();

  if(xtimer) 
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
    }

  if(urltarget) 
    {
      delete urltarget;
    }

  if(xmutexreplys) 
    {
      GEN_XFACTORY.Delete_Mutex(xmutexreplys);
    }  

  if(xmutexping) 
    {
      GEN_XFACTORY.Delete_Mutex(xmutexping);
    }  

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::GetIsInstanced()
* @brief      Get is instanced
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOPING& DIOPING::GetInstance()
* @brief      Get instance
* @ingroup    DATAIO
* 
* @return     DIOPING& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOPING& DIOPING::GetInstance()
{
  if(!instance) instance = new DIOPING();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::SetInstance(DIOPING* _instance)
* @brief      Set instance
* @ingroup    DATAIO
* 
* @param[in]  _instance : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::SetInstance(DIOPING* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::DelInstance()
* @brief      Del instance
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOURL* DIOPING::GetTarget()
* @brief      Get target
* @ingroup    DATAIO
* 
* @return     DIOURL* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DIOURL* DIOPING::GetTarget()
{
  return urltarget;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::Set(XCHAR* urltarget , XCHAR* IPLocal)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  urltarget : 
* @param[in]  IPLocal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::Set(XCHAR* urltarget , XCHAR* IPLocal)
{
  if(this->urltarget) (*this->urltarget) = urltarget;

  if(IPLocal) this->IPLocal = IPLocal;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::Set(DIOURL& urltarget, XCHAR* IPLocal)
* @brief      Set
* @ingroup    DATAIO
* 
* @param[in]  urltarget : 
* @param[in]  IPLocal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::Set(DIOURL& urltarget, XCHAR* IPLocal)
{
  return Set(urltarget.Get(), IPLocal);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::Do(XDWORD nretries, XDWORD timebetweenchecks, bool exitfirstgoodreply)
* @brief      Do
* @ingroup    DATAIO
* 
* @param[in]  nretries : 
* @param[in]  timebetweenchecks : 
* @param[in]  exitfirstgoodreply : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::Do(XDWORD nretries, XDWORD timebetweenchecks, bool exitfirstgoodreply)
{
  if(!urltarget)         return false;
  if(!xtimer)            return false;

  if(xmutexping)
    {
      xmutexping->Lock();
    }

  DIOSTREAMICMPCONFIG   diostreamICMPconfig;
  XSTRING               targetIP;

  DeleteAllReplys();

  urltarget->ResolveURL(targetIP);

  diostreamICMPconfig.GetRemoteURL()->Set(urltarget->Get());
  
  diostreamICMPconfig.SetMode(DIOSTREAMMODE_CLIENT);

  DIOSTREAMICMP* diostreamICMP  = (DIOSTREAMICMP*)GEN_DIOFACTORY.CreateStreamIO(&diostreamICMPconfig);
  if(!diostreamICMP) 
    {
      if(xmutexping)
        {
          xmutexping->UnLock();
        }

      return false;
    }

  if(!diostreamICMP->Open())
    {
      GEN_DIOFACTORY.DeleteStreamIO(diostreamICMP);

      if(xmutexping)
        {
          xmutexping->UnLock();
        }

      return false;
    }

  if(!diostreamICMP->WaitToConnected(5))
    {
      diostreamICMP->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamICMP);

      if(xmutexping)
        {
          xmutexping->UnLock();
        }

      return false;
    }

  DIOPING_ECHOREQUEST echorequest;
  int                 ID    = 0xCAFE;
  int                 nseq  = 2;
  int                 nloop = nretries;

  while(nloop)
    {
      HASHCRC32 crc32;     
      XDWORD    crc32result;
      XSTRING   address;
      XBUFFER   xbuffer;
      bool      status       = false;
      
      XRAND* GEN_XFACTORY_CREATE(xrand, CreateRand())
      if(!xrand) 
        {
          break;
        }

      memset((XBYTE*)&echorequest, 0, sizeof(DIOPING_ECHOREQUEST));

      // Fill in echo request
      echorequest.icmphdr.type      = DIOPING_ICMP_ECHOREQ;
      echorequest.icmphdr.code      = 0;
      echorequest.icmphdr.ID        = ID;
      echorequest.icmphdr.seq       = nseq++;

      //Fill in some data to send
      for(int nret=0; nret<DIOPING_REQ_TICKETSIZE; nret++)
        {
          echorequest.cdata[nret] = xrand->Max(255);
        }

      GEN_XFACTORY.DeleteRand(xrand);

      crc32.ResetResult();
      crc32.Do((XBYTE*)echorequest.cdata, DIOPING_REQ_TICKETSIZE);
      crc32result = crc32.GetResultCRC32();

      echorequest.applicationID     = applicationID;
      echorequest.time              = (XDWORD)xtimer->GetMicroSecondsTickCounter();                           // Save tick count when sent
      echorequest.icmphdr.checksum  = CalculeCheckSum((XWORD *)&echorequest, sizeof(DIOPING_ECHOREQUEST));    // Put data in packet and compute checksum

      if(echorequest.icmphdr.checksum)
        {
          diostreamICMP->GetInXBuffer()->Delete();
          diostreamICMP->GetOutXBuffer()->Delete();
          diostreamICMP->DeleteAllDatagrams();

          status = diostreamICMP->WriteDatagram(targetIP, (XBYTE*)&echorequest, sizeof(DIOPING_ECHOREQUEST));
          if(status) 
            {
              status = diostreamICMP->WaitToFlushOutXBuffer(3);
            }
        }

      if(!status)
        {
          //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] not write packet! %s"), targetIP.Get());
          break;
        }

      while(1)
        {
          status = diostreamICMP->WaitToFilledReadingBuffer(sizeof(DIOPING_ECHOREPLY), 1);
          if(!status)
            {
              //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] not ready packet! %s"), targetIP.Get());
              if(exitfirstgoodreply)  nloop = 0;  else nloop--;
              break;
            }

          status = diostreamICMP->ReadDatagram(address, xbuffer);
          if(!status)
            {
              //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] not read packet! %s"), targetIP.Get());
              if(exitfirstgoodreply)  nloop = 0;  else nloop--;
              break;
            }

          if(xbuffer.GetSize() < sizeof(DIOPING_ECHOREPLY))
            {
              //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] invalid size packet! %s, "), targetIP.Get());
              continue;
            }

          DIOPING_ECHOREPLY echoreply;

          memcpy((XBYTE*)&echoreply.iphdr, xbuffer.Get(), sizeof(DIOPING_ECHOREPLY));

          if(echoreply.echorequest.icmphdr.type == DIOPING_ICMP_ECHOREPLY)
            {
              crc32.ResetResult();
              crc32.Do((XBYTE*)echoreply.echorequest.cdata, DIOPING_REQ_TICKETSIZE);

              if(crc32result == crc32.GetResultCRC32())
                {
                  XWORD checksum = CalculeCheckSum((XWORD *)&echoreply.echorequest, sizeof(DIOPING_ECHOREQUEST));
                  if(!checksum)
                    {
                      DIOIP    ip;
                      XSTRING  fromIP;

                      //  Calculate elapsed time

                      ip.Set(echoreply.iphdr.iasource.INADDR_UNION.addrbyte.s_b1,
                             echoreply.iphdr.iasource.INADDR_UNION.addrbyte.s_b2,
                             echoreply.iphdr.iasource.INADDR_UNION.addrbyte.s_b3,
                             echoreply.iphdr.iasource.INADDR_UNION.addrbyte.s_b4);

                      ip.GetXString(fromIP);

                      if(!fromIP.Compare(targetIP))
                        {
                          if(echoreply.echorequest.applicationID == applicationID)
                            {
                              XDWORD   elapsed;

                              elapsed = ((XDWORD)xtimer->GetMicroSecondsTickCounter() - echoreply.echorequest.time);

                              AddReply(nloop+1, fromIP.Get(), DIOPING_REQ_TICKETSIZE, (elapsed/1000), echoreply.iphdr.TTL);

                              DIOPING_XEVENT xevent(this, DIOPING_XEVENT_TYPE_DOPING);
                              xevent.SetPingReply((DIOPINGREPLY*)replys.Get(replys.GetSize()-1));
                              PostEvent(&xevent);

                              //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Ping] received! %s %s (elapsed time %d)"), fromIP.Get(), targetIP.Get(), elapsed);

                              if(exitfirstgoodreply)
                                {
                                  nloop = 0;
                                  break;
                                }

                              GEN_XSLEEP.MilliSeconds(timebetweenchecks);

                              nloop--;
                              break;
                            }
                           else
                            {
                              //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] application ID not equal! %s %s"), fromIP.Get(), targetIP.Get());
                            }
                        }
                       else
                        {
                          //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] not IP equal! %s %s"), fromIP.Get(), targetIP.Get());
                        }

                    }
                   else
                    {
                      //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] error Checksum! %s "), targetIP.Get());
                    }
                }               
               else
                {
                  //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] error CRC! %s "), targetIP.Get());
                }               
            }
           else
            {
              //XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Ping] Is not reply packet! %s "), targetIP.Get());
            }
        }
   }

  diostreamICMP->Close();
  GEN_DIOFACTORY.DeleteStreamIO(diostreamICMP);

  bool status = WasConnected();
  if(!status)
    {
     //XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[Ping] to [%s]: %s"), targetIP.Get(), (status?__L("[Ok.]"):__L("[Error!]")));
    }

  if(xmutexping)
    {
      xmutexping->UnLock();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::WasConnected()
* @brief      Was connected
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::WasConnected()
{
  if(!xmutexreplys) return false;

  bool status = false;

  xmutexreplys->Lock();
  if(!replys.IsEmpty()) status = true;
  xmutexreplys->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XVECTOR<DIOPINGREPLY*>* DIOPING::GetReplys()
* @brief      Get replys
* @ingroup    DATAIO
* 
* @return     XVECTOR<DIOPINGREPLY*>* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XVECTOR<DIOPINGREPLY*>* DIOPING::GetReplys()
{
  return &replys;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD DIOPING::CalculateMeanTime()
* @brief      Calculate mean time
* @ingroup    DATAIO
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD DIOPING::CalculateMeanTime()
{
  if(!xmutexreplys) return 0;

  XDWORD meantime = 0;

  xmutexreplys->Lock();

  if(!replys.IsEmpty())
    {
      for(XDWORD c=0;c<replys.GetSize();c++)
        {
          DIOPINGREPLY* pinganswer = (DIOPINGREPLY*)replys.Get(c);
          if(pinganswer)
            {
              meantime += pinganswer->GetTimeElapsed();
            }
        }

      meantime /= replys.GetSize();
    }

  xmutexreplys->UnLock();

  return meantime;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::DeleteAllReplys()
* @brief      Delete all replys
* @ingroup    DATAIO
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::DeleteAllReplys()
{
  if(!xmutexreplys) return false;

  bool status = false;

  xmutexreplys->Lock();

  if(!replys.IsEmpty())
    {
      replys.DeleteContents();
      replys.DeleteAll();

      status = true;
    }

  xmutexreplys->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOPING::AddReply(XWORD sequence, XCHAR* fromIP, XDWORD sizerequest, XDWORD timeelapsed, XBYTE TTL)
* @brief      Add reply
* @ingroup    DATAIO
* 
* @param[in]  sequence : 
* @param[in]  fromIP : 
* @param[in]  sizerequest : 
* @param[in]  timeelapsed : 
* @param[in]  TTL : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOPING::AddReply(XWORD sequence, XCHAR* fromIP, XDWORD sizerequest, XDWORD timeelapsed, XBYTE TTL)
{
  if(!xmutexreplys) return false;

  bool status = false;

  xmutexreplys->Lock();

  DIOPINGREPLY* pinganswer = new DIOPINGREPLY();
  if(pinganswer)
    {
      pinganswer->SetSequence(sequence);
      pinganswer->GetFromIP()->Set(fromIP);
      pinganswer->SetSizeRequest(sizerequest);
      pinganswer->SetTimeElapsed(timeelapsed);
      pinganswer->SetTTL(TTL);

      replys.Add(pinganswer);

      status = true;
    }

  xmutexreplys->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XWORD DIOPING::CalculeCheckSum(XWORD* addr, int len)
* @brief      Calcule check sum
* @ingroup    DATAIO
* 
* @param[in]  addr : 
* @param[in]  len : 
* 
* @return     XWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XWORD DIOPING::CalculeCheckSum(XWORD* addr, int len)
{
  int     nleft   = len;
  XWORD*  w       = addr;
  XWORD   answer;
  int     sum     = 0;

  // Our algorithm is simple, using a 32 bit accumulator (sum),
  // we add sequential 16 bit words to it, and at the end, fold
  // back all the carry bits from the top 16 bits into the lower
  // 16 bits.

  while(nleft>1)
    {
      sum   += *w++;
      nleft -= 2;
    }

  // mop up an odd byte, if necessary

  if( nleft == 1 )
    {
      XWORD u = 0;

      *(XBYTE*)(&u) = *(XBYTE*)w ;
      sum += u;
    }


  // add back carry outs from top 16 bits to low 16 bits

  sum     = (sum >> 16) + (sum & 0xffff);   // add hi 16 to low 16
  sum    += (sum >> 16);                    // add carry
  answer  = ~sum;                           // truncate to 16 bits

  return answer;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOPING::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOPING::Clean()
{
  xtimer              = NULL;

  urltarget           = NULL;

  xmutexping          = NULL;

  applicationID       = 0;

  IPLocal.Empty();

  xmutexreplys        = NULL;

  nretries            = 0;
  timebetweenchecks   = 0;
}


#pragma endregion


#pragma endregion
