/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XPlatformINI.cpp
*
* @class      XPLATFORMINI
* @brief      eXtended Platform Initialization class
* @ingroup    UTILS
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

#include "XPlatformINI.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPLATFORMINI::XPLATFORMINI()
* @brief      Constructor
* @ingroup    MAIN
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPLATFORMINI::XPLATFORMINI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XPLATFORMINI::~XPLATFORMINI()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    MAIN
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XPLATFORMINI::~XPLATFORMINI()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPLATFORMINI::Ini()
* @brief      Ini
* @ingroup    MAIN
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPLATFORMINI::Ini()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XPLATFORMINI::End()
* @brief      End
* @ingroup    MAIN
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XPLATFORMINI::End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XPLATFORMINI::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    MAIN
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XPLATFORMINI::Clean()
{

}


