/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIONotificationsManager.cpp
*
* @class      DIONOTIFICATIONSMANAGER
* @brief      Data Input/Output Notifications manager class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONotificationsManager.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIONOTIFICATION                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONOTIFICATION::DIONOTIFICATION()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONOTIFICATION::DIONOTIFICATION()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONOTIFICATION::~DIONOTIFICATION()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONOTIFICATION::~DIONOTIFICATION()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIONOTIFICATION::Get_Title()
* @brief      GetTitle
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONOTIFICATION::Get_Title()
{
  return &title;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DIONOTIFICATION::Get_Message()
* @brief      GetMessage
* @ingroup    DATAIO
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* DIONOTIFICATION::Get_Message()
{
  return &message;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIONOTIFICATION::GetApplicationHandle()
* @brief      GetApplicationHandle
* @ingroup    DATAIO
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* DIONOTIFICATION::GetApplicationHandle()
{
  return applicationhandle;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONOTIFICATION::SetApplicationHandle(void* applicationhandle)
* @brief      SetApplicationHandle
* @ingroup    DATAIO
*
* @param[in]  applicationhandle :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONOTIFICATION::SetApplicationHandle(void* applicationhandle)
{
  this->applicationhandle = applicationhandle;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIONOTIFICATION::GetWindowHandle()
* @brief      GetWindowHandle
* @ingroup    DATAIO
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
void* DIONOTIFICATION::GetWindowHandle()
{
  return windowhandle;
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONOTIFICATION::SetWindowHandle(void* windowhandle)
* @brief      SetWindowHandle
* @ingroup    DATAIO
*
* @param[in]  windowhandle :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*
void DIONOTIFICATION::SetWindowHandle(void* windowhandle)
{
  this->windowhandle = windowhandle;
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* DIONOTIFICATION::GetApplicationIcon()
* @brief      GetApplicationIcon
* @ingroup    DATAIO
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* DIONOTIFICATION::GetApplicationIcon()
{
  return applicationicon;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONOTIFICATION::SetApplicationIcon(void* applicationicon)
* @brief      SetApplicationIcon
* @ingroup    DATAIO
*
* @param[in]  applicationicon :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONOTIFICATION::SetApplicationIcon(void* applicationicon)
{
  this->applicationicon = applicationicon;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONOTIFICATION::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONOTIFICATION::Clean()
{
  applicationhandle = NULL;
  //windowhandle      = NULL;
  applicationicon   = NULL;
}



/*--------------------------------------------------------------------------------------------------------------------*/
/*  DIONOTIFICATIONMANAGER                                                                                            */
/*--------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
*  @fn         DIONOTIFICATIONSMANAGER::DIONOTIFICATIONSMANAGER()
*  @brief      Constructor
*  @ingroup    DATAIO
*
*  ""
*  ""
*
*  @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONOTIFICATIONSMANAGER::DIONOTIFICATIONSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIONOTIFICATIONSMANAGER::~DIONOTIFICATIONSMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DIONOTIFICATIONSMANAGER::~DIONOTIFICATIONSMANAGER()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONOTIFICATIONSMANAGER::Ini(XCHAR* pathexec, XCHAR* generictitle)
* @brief      Ini
* @ingroup    DATAIO
*
* @param[in]  generictitle :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONOTIFICATIONSMANAGER::Ini(XCHAR* titleowner, XCHAR* genericapp)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONOTIFICATIONSMANAGER::Do(DIONOTIFICATION* notification)
* @brief      Do
* @ingroup    DATAIO
*
* @param[in]  notification :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONOTIFICATIONSMANAGER::Do(DIONOTIFICATION* notification)
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONOTIFICATIONSMANAGER::Do(DIONOTIFICATION& notification)
* @brief      Do
* @ingroup    DATAIO
*
* @param[in]  notification :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONOTIFICATIONSMANAGER::Do(DIONOTIFICATION& notification)
{
  return Do(&notification);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIONOTIFICATIONSMANAGER::End()
* @brief      End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DIONOTIFICATIONSMANAGER::End()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIONOTIFICATIONSMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    DATAIO
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DIONOTIFICATIONSMANAGER::Clean()
{

}