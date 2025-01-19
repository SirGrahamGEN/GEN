/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOScraperWebMACManufacturer.cpp
* 
* @class      DIOSCRAPERWEBMACMANUFACTURER
* @brief      Data Input/Output Scraper Web MAC Manufacturer class
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

#include "DIOScraperWebMACManufacturer.h"

#include "XThread.h"

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


#pragma region CLASS_DIOMACMANUFACTURED_RESULT


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMACMANUFACTURED_RESULT::DIOMACMANUFACTURED_RESULT()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOMACMANUFACTURED_RESULT::DIOMACMANUFACTURED_RESULT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOMACMANUFACTURED_RESULT::~DIOMACMANUFACTURED_RESULT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOMACMANUFACTURED_RESULT::Get()
{
  return &manufactured;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOMACMANUFACTURED_RESULT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOMACMANUFACTURED_RESULT::Clean()
{

}


#pragma endregion


#pragma region CLASS_DIOSCRAPERWEBMACMANUFACTURER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBMACMANUFACTURER::DIOSCRAPERWEBMACMANUFACTURER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBMACMANUFACTURER::DIOSCRAPERWEBMACMANUFACTURER(): DIOSCRAPERWEB()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBMACMANUFACTURER::~DIOSCRAPERWEBMACMANUFACTURER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBMACMANUFACTURER::~DIOSCRAPERWEBMACMANUFACTURER()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBMACMANUFACTURER::ChangeURL(XCHAR* maskurl, DIOURL& url)
* @brief      Change URL
* @ingroup    DATAIO
*
* @param[in]  maskurl :
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @param[in]  MAC :
* @param[in]  manufactured :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSCRAPERWEBMACMANUFACTURER::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEBMACMANUFACTURER::Clean()
{

}


#pragma endregion


#pragma endregion

