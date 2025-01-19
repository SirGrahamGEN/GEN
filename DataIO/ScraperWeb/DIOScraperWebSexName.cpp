/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOScraperWebSexName.cpp
* 
* @class      DIOSCRAPERWEBSEXNAME
* @brief      Data Input/Output Scraper Web Sex Name class
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

#include "DIOScraperWebSexName.h"

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


#pragma region CLASS_DIOSEXNAME_RESULT


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSEXNAME_RESULT::DIOSEXNAME_RESULT()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSEXNAME_RESULT::DIOSEXNAME_RESULT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSEXNAME_RESULT::~DIOSEXNAME_RESULT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSEXNAME_RESULT::~DIOSEXNAME_RESULT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBSEXNAMETYPE DIOSEXNAME_RESULT::Get()
* @brief      Get
* @ingroup    DATAIO
*
* @return     DIOSCRAPERWEBSEXNAMETYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBSEXNAMETYPE DIOSEXNAME_RESULT::Get()
{
  return sex;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSEXNAME_RESULT::Set(DIOSCRAPERWEBSEXNAMETYPE sex)
* @brief      Set
* @ingroup    DATAIO
*
* @param[in]  sex :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSEXNAME_RESULT::Set(DIOSCRAPERWEBSEXNAMETYPE sex)
{
  this->sex = sex;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIOSEXNAME_RESULT::GetNameClear()
* @brief      Get name clear
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIOSEXNAME_RESULT::GetNameClear()
{
  return &nameclear;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSEXNAME_RESULT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSEXNAME_RESULT::Clean()
{
  sex = DIOSCRAPERWEBSEXNAMETYPE_NOTOBTAINED;
}


#pragma endregion


#pragma region CLASS_DIOSCRAPERWEBSEXNAME


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBSEXNAME::DIOSCRAPERWEBSEXNAME()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBSEXNAME::DIOSCRAPERWEBSEXNAME(): DIOSCRAPERWEB()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOSCRAPERWEBSEXNAME::~DIOSCRAPERWEBSEXNAME()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
DIOSCRAPERWEBSEXNAME::~DIOSCRAPERWEBSEXNAME()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBSEXNAME::ChangeURL(XCHAR* maskurl, DIOURL& url)
* @brief      Change URL
* @ingroup    DATAIO
*
* @param[in]  maskurl :
* @param[in]  url :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBSEXNAME::ChangeURL(XCHAR* maskurl, DIOURL& url)
{
  url.Format(maskurl, name.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOSCRAPERWEBSEXNAME::Get(XCHAR* name, DIOSCRAPERWEBSEXNAMETYPE& sexnametype, XSTRING* nameclear, int timeoutforurl, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  sexnametype :
* @param[in]  nameclear :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBSEXNAME::Get(XCHAR* name, DIOSCRAPERWEBSEXNAMETYPE& sexnametype, XSTRING* nameclear, int timeoutforurl, XSTRING* localIP, bool usecache)
{
  bool status = false;

  if(xmutexdo) xmutexdo->Lock();

  this->name = name;

  DIOSEXNAME_RESULT* sexnameresult;
  if(usecache)
    {
      sexnameresult = (DIOSEXNAME_RESULT*)cache->Get(this->name);
      if(sexnameresult)
        {
          sexnametype = sexnameresult->Get();
          if(nameclear) nameclear->Set(sexnameresult->GetNameClear()->Get());

          if(xmutexdo) xmutexdo->UnLock();

          return true;
        }
    }

  sexnametype = DIOSCRAPERWEBSEXNAMETYPE_NOTOBTAINED;
  if(this->name.IsEmpty())
    {
      if(Load(DIOSCRAPERWEBSEXNAME_NAMEFILE))
        {
          if(Do(DIOSCRAPERWEBSEXNAME_NAMESERVICE, timeoutforurl, localIP))
            {
              sexnametype = DIOSCRAPERWEBSEXNAMETYPE_NONAME;

              XSTRING sexnamestr;

              sexnamestr = GetValue(__L("SEX"));
              if(!sexnamestr.Compare(__L("male")))    sexnametype = DIOSCRAPERWEBSEXNAMETYPE_MALE;
              if(!sexnamestr.Compare(__L("female")))  sexnametype = DIOSCRAPERWEBSEXNAMETYPE_FEMALE;

              if(nameclear)
                {
                  if((sexnametype == DIOSCRAPERWEBSEXNAMETYPE_MALE) || (sexnametype == DIOSCRAPERWEBSEXNAMETYPE_FEMALE))
                        (*nameclear) = GetValue(__L("NAME"));
                   else (*nameclear) = this->name.Get();
                }

              if(usecache)
                {
                  sexnameresult = new DIOSEXNAME_RESULT();
                  if(sexnameresult)
                    {
                      if(nameclear) sexnameresult->GetNameClear()->Set(nameclear->Get());
                      sexnameresult->Set(sexnametype);

                      cache->Add(this->name, sexnameresult);
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
* @fn         bool DIOSCRAPERWEBSEXNAME::Get(XSTRING& name, DIOSCRAPERWEBSEXNAMETYPE& sexnametype, XSTRING* nameclear, int timeoutforurl, XSTRING* localIP, bool usecache)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  name :
* @param[in]  sexnametype :
* @param[in]  nameclear :
* @param[in]  timeoutforurl :
* @param[in]  localIP :
* @param[in]  usecache :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSCRAPERWEBSEXNAME::Get(XSTRING& name, DIOSCRAPERWEBSEXNAMETYPE& sexnametype, XSTRING* nameclear, int timeoutforurl, XSTRING* localIP, bool usecache)
{
  return Get(name.Get(), sexnametype, nameclear, timeoutforurl, localIP, usecache);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOSCRAPERWEBSEXNAME::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIOSCRAPERWEBSEXNAME::Clean()
{

}


#pragma endregion


#pragma endregion

