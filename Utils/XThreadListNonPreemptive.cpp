/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XThreadListNonPreemptive.cpp
*
* @class      XTHREADLISTNONPREEMPTIVE
* @brief      eXtended Thread List Non Preemtive
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

#include "XThreadListNonPreemptive.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XTHREADLISTNONPREEMPTIVE* XTHREADLISTNONPREEMPTIVE::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADLISTNONPREEMPTIVE& XTHREADLISTNONPREEMPTIVE::GetInstance()
* @brief      GetInstance
* @ingroup    UTILS
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
* @brief      DelInstance
* @ingroup    UTILS
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
* @brief      AddThread
* @ingroup    UTILS
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
* @brief      DeleteThread
* @ingroup    UTILS
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
* @brief      DeleteAll
* @ingroup    UTILS
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
* @brief      ExecuteFunctions
* @ingroup    UTILS
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



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADLISTNONPREEMPTIVE::XTHREADLISTNONPREEMPTIVE()
* @brief      Constructor
* @ingroup    UTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADLISTNONPREEMPTIVE::XTHREADLISTNONPREEMPTIVE()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADLISTNONPREEMPTIVE::~XTHREADLISTNONPREEMPTIVE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @return     Does not return anything.
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
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREADLISTNONPREEMPTIVE::Clean()
{

}
