/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XFSMachine.cpp
*
* @class      XFSMACHINE
* @brief      eXtended Finite state machine class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdarg.h>

#include "XFSMachine.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSMACHINESTATE::XFSMACHINESTATE(int stateID, int ntransitions)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  int :
* @param[in]   int ntransitions :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSMACHINESTATE::XFSMACHINESTATE(int stateID, int ntransitions)
{
  Clean();

  this->maxtransitions = ntransitions?ntransitions:1;
  this->stateID        = stateID;

  inputs               = NULL;
  outputstates         = NULL;

  inputs = new int[this->maxtransitions];
  if(!inputs) return;

  outputstates = new int[this->maxtransitions];
  if(!outputstates)
    {
      delete[] inputs;
      return;
    }

  for(int c=0; c<this->maxtransitions;c++)
    {
      inputs[c]       = 0;
      outputstates[c] = 0;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSMACHINESTATE::~XFSMACHINESTATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSMACHINESTATE::~XFSMACHINESTATE()
{
  delete[] inputs;
  delete[] outputstates;

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSMACHINESTATE::GetID()
* @brief      GetID
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSMACHINESTATE::GetID()
{
  return stateID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINESTATE::AddTransition(int input,int outputID)
* @brief      AddTransition
* @ingroup    XUTILS
*
* @param[in]  input :
* @param[in]  outputID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINESTATE::AddTransition(int input,int outputID)
{
  int c;

  for(c=0;c<maxtransitions;c++)
    {
      if(!outputstates[c]) break;
    }

  if(c<maxtransitions)
    {
      outputstates[c] = outputID;
      inputs[c]       = input;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSMACHINESTATE::GetOutput(int input)
* @brief      GetOutput
* @ingroup    XUTILS
*
* @param[in]  input :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSMACHINESTATE::GetOutput(int input)
{
  int outputID = stateID;

  for(int c=0;c<maxtransitions;c++)
    {
      if(!outputstates[c]) break;

      if(input==inputs[c])
        {
          outputID = outputstates[c];
          break;
        }
    }

  return(outputID);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINESTATE::DeleteTransition(int outputID)
* @brief      DeleteTransition
* @ingroup    XUTILS
*
* @param[in]  outputID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINESTATE::DeleteTransition(int outputID)
{
  int c;

  for(c=0;c<maxtransitions;c++)
    {
      if(outputstates[c]==outputID) break;
    }

  if(c>=maxtransitions) return false;

  inputs[c]       = 0;
  outputstates[c] = 0;

  for(;c<(maxtransitions-1);c++)
    {
      if(!outputstates[c]) break;

      inputs[c]       = inputs[c+1];
      outputstates[c] = outputstates[c+1];
    }

  inputs[c]       = 0;
  outputstates[c] = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSMACHINESTATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSMACHINESTATE::Clean()
{
  stateID        = 0;
  maxtransitions = 0;

  inputs         = NULL;
  outputstates   = NULL;
}



/* --------------------------------------------------------------------------------------------------------------------*/
/* XFSMACHINE                                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSMACHINE::XFSMACHINE(int stateID)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  int :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSMACHINE::XFSMACHINE(int stateID)
{
  Clean();

  SetCurrentState(stateID);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSMACHINE::~XFSMACHINE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSMACHINE::~XFSMACHINE()
{
  DeleteAllStates();

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSMACHINE::GetEvent()
* @brief      GetEvent
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSMACHINE::GetEvent()
{
  return fsmevent;
};



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::SetEvent(int event)
* @brief      SetEvent
* @ingroup    XUTILS
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::SetEvent(int event)
{
  fsmevent = event;

  return true;
};



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSMACHINE::GetCurrentState()
* @brief      GetCurrentState
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSMACHINE::GetCurrentState()
{
  return currentstate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSMACHINE::SetCurrentState(int stateID)
* @brief      SetCurrentState
* @ingroup    XUTILS
*
* @param[in]  stateID :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSMACHINE::SetCurrentState(int stateID)
{
  currentstate = stateID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XFSMACHINESTATE* XFSMACHINE::GetState(int stateID)
* @brief      GetState
* @ingroup    XUTILS
*
* @param[in]  stateID :
*
* @return     XFSMACHINESTATE* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XFSMACHINESTATE* XFSMACHINE::GetState(int stateID)
{
  XFSMACHINESTATE* state = NULL;
  if(map.IsEmpty()) return state;

  int index = map.Find(stateID);
  if(index==-1) return state;

  state = map.GetElement(index);

  return state;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::AddState(XFSMACHINESTATE* state)
* @brief      AddState
* @ingroup    XUTILS
*
* @param[in]  state :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::AddState(XFSMACHINESTATE* state)
{
  if(GetState(state->GetID())) return false;

  map.Add(state->GetID(), state);

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::AddState(int state, int event, int tostate,...)
* @brief      AddState
* @ingroup    XUTILS
*
* @param[in]  state :
* @param[in]  event :
* @param[in]  tostate :
* @param[in]  ... :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::AddState(int state, int event, int tostate,...)
{
  XFSMACHINESTATE* _state;
  int              narg = 0;
  va_list          arg;

  va_start(arg, tostate);
  while(va_arg(arg, int) != XFSMACHINESTATE_EVENTDEFEND)
   {
     narg++;
   }
  va_end(arg);

  if((narg)&&(narg%2)) return false;

  narg+=2;

  _state = new XFSMACHINESTATE(state,(narg/2));
  if(!_state) return false;

  _state->AddTransition(event,tostate);

  va_start(arg,tostate);

  int _event;
  int _tostate;

  do { _event   = va_arg(arg, int);
       if(_event != XFSMACHINESTATE_EVENTDEFEND)
        {
          _tostate = va_arg(arg, int);
          _state->AddTransition(_event,_tostate);
        }

     } while(_event != XFSMACHINESTATE_EVENTDEFEND);

  va_end(arg);

  if(!AddState(_state))
    {
      delete _state;
      return false;
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::AddSecuencialStates(int state,int maxsecuencialtransitions)
* @brief      AddSecuencialStates
* @ingroup    XUTILS
*
* @param[in]  state :
* @param[in]  maxsecuencialtransitions :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::AddSecuencialStates(int state, int maxsecuencialtransitions)
{
  XFSMACHINESTATE* _state;

  _state = new XFSMACHINESTATE(state,maxsecuencialtransitions);
  if(!_state) return false;

  for(int c=0;c<maxsecuencialtransitions;c++)
    {
      _state->AddTransition(c,c);
    }

  if(!AddState(_state))
    {
      delete _state;
      return false;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::DeleteState(int stateID)
* @brief      DeleteState
* @ingroup    XUTILS
*
* @param[in]  stateID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::DeleteState(int stateID)
{
  XFSMACHINESTATE* state = GetState(stateID);

  if(!state) return false;

  map.Delete(stateID);

  delete state;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::DeleteAllStates()
* @brief      DeleteAllStates
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::DeleteAllStates()
{
  if(map.IsEmpty()) return false;

  map.DeleteElementContents();
  map.DeleteAll();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XFSMACHINE::StateTransition(int input)
* @brief      StateTransition
* @ingroup    XUTILS
*
* @param[in]  input :
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XFSMACHINE::StateTransition(int input)
{
  XFSMACHINESTATE*  state = GetState(currentstate);

  if(!state)
    {
      currentstate = 0;
      return currentstate;
    }

  currentstate = state->GetOutput(input);

  return currentstate;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::CheckTransition(int& event)
* @brief      CheckTransition
* @ingroup    XUTILS
*
* @param[in]  event :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::CheckTransition(int& event)
{
  int state = GetCurrentState();

  int tevent = (int)GetEvent();

  StateTransition(GetEvent());

  SetEvent(0);

  if(GetCurrentState()==state) return false;

  event = tevent;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XFSMACHINE::CheckTransition()
* @brief      CheckTransition
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XFSMACHINE::CheckTransition()
{
  int state = GetCurrentState();

  StateTransition(GetEvent());

  SetEvent(0);

  if(GetCurrentState()==state) return false;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XFSMACHINE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XFSMACHINE::Clean()
{
  fsmevent     = 0;
  currentstate = 0;
}



