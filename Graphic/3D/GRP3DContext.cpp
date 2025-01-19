/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRP3DContext.cpp
* 
* @class      GRP3DCONTEXT
* @brief      Graphics 3D Context class
* @ingroup    GRAPHIC
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

#include "GRP3DContext.h"

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
* @fn         GRP3DCONTEXT::GRP3DCONTEXT()
* @brief      Constructor of class
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRP3DCONTEXT::GRP3DCONTEXT()
{
  Clean();

  mustrebuild = true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRP3DCONTEXT::~GRP3DCONTEXT()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
GRP3DCONTEXT::~GRP3DCONTEXT()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRP3DCONTEXT::GetScreen()
* @brief      Get screen
* @ingroup    GRAPHIC
*
* @return     GRPSCREEN* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRP3DCONTEXT::GetScreen()
{
  return screen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP3DCONTEXT::SetScreen(GRPSCREEN* screen)
* @brief      Set screen
* @ingroup    GRAPHIC
*
* @param[in]  screen : new screen class (handle)
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRP3DCONTEXT::SetScreen(GRPSCREEN* screen)
{
  this->screen = screen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP3DCONTEXT::Create(void* handle)
* @brief      Create
* @ingroup    GRAPHIC
*
* @param[in]  handle : generic handle
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRP3DCONTEXT::Create(void* handle)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP3DCONTEXT::IsLost()
* @brief      Is lost
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRP3DCONTEXT::IsLost()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP3DCONTEXT::Update()
* @brief      Update
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRP3DCONTEXT::Update()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP3DCONTEXT::Destroy()
* @brief      Destroy
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRP3DCONTEXT::Destroy()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRP3DCONTEXT::IsMustRebuild()
* @brief      Is must rebuild
* @ingroup    GRAPHIC
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRP3DCONTEXT::IsMustRebuild()
{
  return this->mustrebuild;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP3DCONTEXT::SetMustRebuild(bool mustrebuild)
* @brief      Set must rebuild
* @ingroup    GRAPHIC
*
* @param[in]  mustrebuild : true if Must Rebuild context
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRP3DCONTEXT::SetMustRebuild(bool mustrebuild)
{
  this->mustrebuild = mustrebuild;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD GRP3DCONTEXT::GetMultisampling()
* @brief      Get multisampling
* @ingroup    GRAPHIC
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD GRP3DCONTEXT::GetMultisampling()
{
  return multisampling;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP3DCONTEXT::SetMultiSampling(XDWORD multisampling)
* @brief      Set multi sampling
* @ingroup    GRAPHIC
*
* @param[in]  multisampling : multisamplig factor
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRP3DCONTEXT::SetMultiSampling(XDWORD multisampling)
{
  this->multisampling = multisampling;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void GRP3DCONTEXT::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    GRAPHIC
*
* --------------------------------------------------------------------------------------------------------------------*/
void GRP3DCONTEXT::Clean()
{
  screen          = NULL;
  mustrebuild     = false;
  multisampling   = 0;
}


#pragma endregion


