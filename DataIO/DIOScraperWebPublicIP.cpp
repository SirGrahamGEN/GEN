/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOScraperWebPublicIP.cpp
*
* @class      DIOSCRAPERWEBPUBLICIP
* @brief      Data Input/Output Scraper Web Public IP class
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XThread.h"
#include "DIOURL.h"

#include "DIOScraperWebPublicIP.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOPUBLICIP                                                                                                       */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPUBLICIP_RESULT::DIOPUBLICIP_RESULT()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPUBLICIP_RESULT::DIOPUBLICIP_RESULT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOPUBLICIP_RESULT::~DIOPUBLICIP_RESULT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOPUBLICIP_RESULT::~DIOPUBLICIP_RESULT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOIP* DIOPUBLICIP_RESULT::Get()
* @brief      Get
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     DIOIP* :
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOIP* DIOPUBLICIP_RESULT::Get()
{
  return &IP;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOPUBLICIP_RESULT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOPUBLICIP_RESULT::Clean()
{

}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSCRAPERWEBPUBLICIP                                                                                             */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBPUBLICIP::DIOSCRAPERWEBPUBLICIP() : DIOSCRAPERWEB()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBPUBLICIP::DIOSCRAPERWEBPUBLICIP() : DIOSCRAPERWEB()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBPUBLICIP::~DIOSCRAPERWEBPUBLICIP()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBPUBLICIP::~DIOSCRAPERWEBPUBLICIP()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBPUBLICIP::Get(DIOIP& IP, int timeoutforurl, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  IP :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBPUBLICIP::Get(DIOIP& IP, int timeoutforurl,  XSTRING* localIP, bool usecache)
{
  XSTRING publicIPID;
  bool    status = false;

  if(xmutexdo) xmutexdo->Lock();

  publicIPID = __L("public IP ID");

  if(usecache && cache)
    {
      DIOPUBLICIP_RESULT* publicIPresult = (DIOPUBLICIP_RESULT*)cache->Get(publicIPID);
      if(publicIPresult)
        {
          XSTRING IPstring;

          publicIPresult->Get()->GetXString(IPstring);

          IP.Set(IPstring.Get());

          if(xmutexdo) xmutexdo->UnLock();

          return true;
        }
    }

  if(Load(DIOSCRAPERWEBPUBLICIP_NAMEFILE))
    {
      if(Do(DIOSCRAPERWEBPUBLICIP_NAMESERVICE, timeoutforurl,  localIP))
        {
          XSTRING stringIP;

          stringIP = GetValue(__L("IP"));

          if(!stringIP.IsEmpty())
            {
              stringIP.DeleteCharacter(0x20);
              if(!stringIP.IsEmpty())
                {
                  IP.Set(stringIP);

                  if(usecache)
                    {
                      DIOPUBLICIP_RESULT* publicIPresult = new DIOPUBLICIP_RESULT();
                      if(publicIPresult)
                        {
                          publicIPresult->Get()->Set(stringIP.Get());
                          cache->Add(publicIPID, publicIPresult);
                        }
                    }

                  status = true;
                }
            }
        }
    }

  if(xmutexdo) xmutexdo->UnLock();

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSCRAPERWEBPUBLICIP::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEBPUBLICIP::Clean()
{

}

