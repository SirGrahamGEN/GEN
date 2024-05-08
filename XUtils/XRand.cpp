/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XRand.cpp
* 
* @class      XRAND
* @brief      eXtended Utils Random class
* @ingroup    XUTILS
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
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XRand.h"

#include <time.h>

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XRAND* XRAND::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND::XRAND()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XRAND::XRAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND::~XRAND()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XRAND::~XRAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XRAND::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XRAND::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND& XRAND::GetInstance()
* @brief      Get Instance of XRAND
* @note       STATIC
* @ingroup    XUTILS
*
* @return     XRAND& :
*
* --------------------------------------------------------------------------------------------------------------------*/
XRAND& XRAND::GetInstance()
{
  if(!instance) instance = new XRAND();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XRAND::SetInstance(XRAND* _instance)
* @brief      Set Instance of XRAND
* @note       STATIC
* @ingroup    XUTILS
*
* @param[in]  _instance : new instance
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XRAND::SetInstance(XRAND* _instance)
{
  if(!_instance) return false;

  instance = _instance;

  return (instance)?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XRAND::DelInstance()
* @brief      Delete Instance of XRAND
* @note       STATIC
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XRAND::DelInstance()
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
* @fn         bool XRAND::Ini()
* @brief      Ini
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XRAND::Ini()
{
  static int counter  = 0;
  const int prime1    = counter + 42;
  const int prime2    = counter + 89;

  counter++;
  
  initialvalue = (unsigned)time(NULL);
  initialvalue += (initialvalue * prime1) + prime2;

  srand(initialvalue);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::MaxElements(int max)
* @brief      MaxElements
* @ingroup    XUTILS
*
* @param[in]  max :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XRAND::MaxElements(int max)
{
  return GETRANDOM(0, max-1);;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::Max(int max)
* @brief      Max
* @ingroup    XUTILS
*
* @param[in]  max :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XRAND::Max(int max)
{
  return GETRANDOM(0, max);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::Between(int min, int max)
* @brief      Between
* @ingroup    XUTILS
*
* @param[in]  min :
* @param[in]  max :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XRAND::Between(int min, int max)
{
  return GETRANDOM(min, max);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XRAND::Between(float min, float max)
* @brief      Between
* @ingroup    XUTILS
*
* @param[in]  min :
* @param[in]  max :
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XRAND::Between(float min, float max)
{
  int   randomvalue = rand();
  float delta       = ((float)randomvalue)/(float)RAND_MAX;
  return ((max-min)*delta)+min;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XRAND::Percent(int percent)
* @brief      Percent
* @ingroup    XUTILS
*
* @param[in]  percent :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XRAND::Percent(int percent)
{
  int random = Between(1,100);
  if(random <= percent) return true;

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XRAND::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XRAND::Clean()
{
  initialvalue = 0;
}


#pragma endregion

