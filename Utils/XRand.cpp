/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XRand.cpp
*
* @class      XRAND
* @brief      Random class
* @ingroup    UTILS
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

#include "time.h"

#include "XRand.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND::XRAND()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XRAND::XRAND()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XRAND::~XRAND()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XRAND::~XRAND()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XRAND::Ini()
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XRAND::Ini()
{
  const int prime1 = 42;
  const int prime2 = 89;
  
  initialvalue = (unsigned)time(NULL);

  initialvalue += (initialvalue * prime1) + prime2;

  srand(initialvalue);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::MaxElements(int max)
* @brief      MaxElements
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XRAND::MaxElements(int max)
{
  return GETRANDOM(0, max-1);;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::Max(int max)
* @brief      Max
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XRAND::Max(int max)
{
  return GETRANDOM(0, max);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XRAND::Between(int min, int max)
* @brief      Between
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  min :
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XRAND::Between(int min, int max)
{
  return GETRANDOM(min, max);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XRAND::Between(float min, float max)
* @brief      Between
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  min :
* @param[in]  max :
*
* @return     float :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  percent :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XRAND::Clean()
{
  initialvalue = 0;
}

