/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOScraperWebMACManufacturer.cpp
*
* @class      DIOSCRAPERWEBMACMANUFACTURER
* @brief      Data Input/Output Scraper Web MAC Manufacturer class
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
#include "DIOScraperWebMACManufacturer.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOMACMANUFACTURED_RESULT                                                                                         */
/*--------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMACMANUFACTURED_RESULT::DIOMACMANUFACTURED_RESULT()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOMACMANUFACTURED_RESULT::DIOMACMANUFACTURED_RESULT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMACMANUFACTURED_RESULT::~DIOMACMANUFACTURED_RESULT()
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
DIOMACMANUFACTURED_RESULT::~DIOMACMANUFACTURED_RESULT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOMACMANUFACTURED_RESULT::Get()
* @brief      Get
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOMACMANUFACTURED_RESULT::Get()
{
  return &manufactured;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOMACMANUFACTURED_RESULT::Clean()
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
void DIOMACMANUFACTURED_RESULT::Clean()
{

}


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIOSCRAPERWEBMACMANUFACTURER                                                                                      */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBMACMANUFACTURER::DIOSCRAPERWEBMACMANUFACTURER()
* @brief      Constructor
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBMACMANUFACTURER::DIOSCRAPERWEBMACMANUFACTURER(): DIOSCRAPERWEB()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBMACMANUFACTURER::~DIOSCRAPERWEBMACMANUFACTURER()
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
DIOSCRAPERWEBMACMANUFACTURER::~DIOSCRAPERWEBMACMANUFACTURER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBMACMANUFACTURER::ChangeURL(XCHAR* maskurl, DIOURL& url)
* @brief      ChangeURL
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  maskurl :
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBMACMANUFACTURER::ChangeURL(XCHAR* maskurl, DIOURL& url)
{
  XSTRING MACmanufactured;

  MACmanufactured.Format(__L("%02X%02X%02X"), MAC.Get()[0], MAC.Get()[1], MAC.Get()[2]);

  url.Format(maskurl, MACmanufactured.Get());

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBMACMANUFACTURER::Get(DIOMAC& MAC, XSTRING& manufactured, int timeoutforurl, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  MAC :
* @param[in]  manufactured :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBMACMANUFACTURER::Get(DIOMAC& MAC, XSTRING& manufactured, int timeoutforurl, XSTRING* localIP, bool usecache)
{
  XSTRING IPstring;
  bool    status = false;

  if(xmutexdo) xmutexdo->Lock();

  this->MAC.GetXString(IPstring);

  this->MAC.Set(MAC.Get());

  DIOMACMANUFACTURED_RESULT* macmanufacturedresult;

  if(usecache)
    {
      macmanufacturedresult = (DIOMACMANUFACTURED_RESULT*)cache->Get(IPstring);
      if(macmanufacturedresult)
        {
          manufactured = (*macmanufacturedresult->Get());

          if(xmutexdo) xmutexdo->UnLock();

          return true;
        }
    }

  if(Load(DIOSCRAPERWEBMACMANUFACTURER_NAMEFILE))
    {
      if(Do(DIOSCRAPERWEBMACMANUFACTURER_NAMESERVICE, timeoutforurl, localIP))
        {
          manufactured = GetValue(__L("MANUFACTURED"));

          if(!manufactured.IsEmpty())
            {
              if(usecache)
                {
                  macmanufacturedresult = new DIOMACMANUFACTURED_RESULT();
                  if(macmanufacturedresult)
                    {
                      macmanufacturedresult->Get()->Set(manufactured);
                      cache->Add(IPstring, macmanufacturedresult);
                    }
                }

              status = true;
            }

        }
    }

  if(xmutexdo) xmutexdo->UnLock();

  return status;
}




/*-------------------------------------------------------------------
//  DIOSCRAPERWEBMACMANUFACTURER::Clean
*/
/**
//
//
//  @author      Abraham J. Velez
//  @version      05/11/2007 16:28:12
//
//  @return       void :
//  */
/*-----------------------------------------------------------------*/
void DIOSCRAPERWEBMACMANUFACTURER::Clean()
{

}

