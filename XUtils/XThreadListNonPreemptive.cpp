/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XThreadListNonPreemptive.cpp
* 
* @class      XTHREADLISTNONPREEMPTIVE
* @brief      eXtended Utils Thread List Non Preemtive class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XThreadListNonPreemptive.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

XTHREADLISTNONPREEMPTIVE* XTHREADLISTNONPREEMPTIVE::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/*---- XTHREADLISTNONPREEMPTIVE CLASS --------------------------------------------------------------------------------*/
#pragma region XTHREADLISTNONPREEMPTIVE_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTHREADLISTNONPREEMPTIVE& XTHREADLISTNONPREEMPTIVE::GetInstance()
* @brief      Get instance
* @ingroup    XUTILS
* 
* @return     XTHREADLISTNONPREEMPTIVE& : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADLISTNONPREEMPTIVE& XTHREADLISTNONPREEMPTIVE::GetInstance()
{
  if(!instance) instance = new XTHREADLISTNONPREEMPTIVE();

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XTHREADLISTNONPREEMPTIVE::DelInstance()
* @brief      Del instance
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREADLISTNONPREEMPTIVE::DelInstance()
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
* @fn         bool XTHREADLISTNONPREEMPTIVE::AddThread(XTHREAD* thread)
* @brief      Add thread
* @ingroup    XUTILS
* 
* @param[in]  thread : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREADLISTNONPREEMPTIVE::AddThread(XTHREAD* thread)
{
  if(!thread) return false;
  return xthreadsvector.Add(thread);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XTHREADLISTNONPREEMPTIVE::DeleteThread(XTHREAD* thread)
* @brief      Delete thread
* @ingroup    XUTILS
* 
* @param[in]  thread : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREADLISTNONPREEMPTIVE::DeleteThread(XTHREAD* thread)
{
  if(!thread) return false;
  return xthreadsvector.Delete(thread);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XTHREADLISTNONPREEMPTIVE::DeleteAll()
* @brief      Delete all
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREADLISTNONPREEMPTIVE::DeleteAll()
{
  xthreadsvector.DeleteContents();
  xthreadsvector.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XTHREADLISTNONPREEMPTIVE::ExecuteFunctions()
* @brief      Execute functions
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREADLISTNONPREEMPTIVE::ExecuteFunctions()
{
  if(!xthreadsvector.GetSize()) return false;

  for(XDWORD c=0; c<xthreadsvector.GetSize(); c++)
    {
      XTHREAD* xthread  = xthreadsvector.Get(c);
      if(xthread)
        {
          switch(xthread->GetStatusFunc())
            {
              case XTHREADSTATUS_RUN    : xthread->GetFunction()(xthread->GetParam());
                                          break;

              case XTHREADSTATUS_EXIT   : break;

                               default  : break;
            }
        }
    }

  return true;
}


#pragma endregion


/*---- XTHREADLISTNONPREEMPTIVE CLASS --------------------------------------------------------------------------------*/
#pragma region XTHREADLISTNONPREEMPTIVE_CLASS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTHREADLISTNONPREEMPTIVE::XTHREADLISTNONPREEMPTIVE()
* @brief      Constructor of class
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADLISTNONPREEMPTIVE::XTHREADLISTNONPREEMPTIVE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XTHREADLISTNONPREEMPTIVE::~XTHREADLISTNONPREEMPTIVE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADLISTNONPREEMPTIVE::~XTHREADLISTNONPREEMPTIVE()
{
  DeleteAll();

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XTHREADLISTNONPREEMPTIVE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    XUTILS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREADLISTNONPREEMPTIVE::Clean()
{

}


#pragma endregion


#pragma endregion

