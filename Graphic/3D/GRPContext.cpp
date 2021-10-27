/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPContext.cpp
*
* @class      GRPCONTEXT
* @brief      Graphics Context class
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
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

#include "GRPContext.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCONTEXT::GRPCONTEXT()
* @brief      Constructor
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCONTEXT::GRPCONTEXT()
{
  Clean();

  mustrebuild = true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCONTEXT::~GRPCONTEXT()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCONTEXT::~GRPCONTEXT()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPCONTEXT::GetScreen()
* @brief      Get Screen Handle
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     GRPSCREEN* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRPCONTEXT::GetScreen()
{
  return screen;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCONTEXT::SetScreen(GRPSCREEN* screen)
* @brief      Set Screen Handle
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  screen : new screen class (handle)
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCONTEXT::SetScreen(GRPSCREEN* screen)
{
  this->screen = screen;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCONTEXT::Create(void* handle)
* @brief      Create context
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  handle : generic handle
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCONTEXT::Create(void* handle)
{
  return false;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCONTEXT::IsLost()
* @brief      Is Lost context
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCONTEXT::IsLost()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCONTEXT::Update()
* @brief      Update Context
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCONTEXT::Update()
{
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCONTEXT::Destroy()
* @brief      Destroy context
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCONTEXT::Destroy()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPCONTEXT::IsMustRebuild()
* @brief      Is Must Rebuild context
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPCONTEXT::IsMustRebuild()
{
  return this->mustrebuild;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCONTEXT::SetMustRebuild(bool mustrebuild)
* @brief      Set Must Rebuild
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  mustrebuild : true if Must Rebuild context
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCONTEXT::SetMustRebuild(bool mustrebuild)
{
  this->mustrebuild = mustrebuild;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRPCONTEXT::GetMultisampling()
* @brief      Get Multi sampling
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD GRPCONTEXT::GetMultisampling()
{
  return multisampling;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCONTEXT::SetMultiSampling(XDWORD multisampling)
* @brief      Set Multi Sampling
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @param[in]  multisampling : multisamplig factor
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCONTEXT::SetMultiSampling(XDWORD multisampling)
{
  this->multisampling = multisampling;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRPCONTEXT::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* @author     Imanol Celaya Ruiz de Alegria
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void GRPCONTEXT::Clean()
{
  screen          = NULL;
  mustrebuild     = false;
  multisampling   = 0;
}

