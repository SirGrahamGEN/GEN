/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XInterpolator.cpp
* 
* @class      XINTERPOLATOR
* @brief      eXtended Utils Interpolator class
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XInterpolator.h"

#include "XTrace.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR::XINTERPOLATOR(XINTERPOLATOR_TYPE type)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR::XINTERPOLATOR(XINTERPOLATOR_TYPE type)
{
  Clean();

  this->type = type;
  carry      = 0.0f;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR::~XINTERPOLATOR()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR::~XINTERPOLATOR()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR_TYPE XINTERPOLATOR::GetType()
* @brief      GetType
* @ingroup    XUTILS
*
* @return     XINTERPOLATOR_TYPE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR_TYPE XINTERPOLATOR::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetType(XINTERPOLATOR_TYPE type)
* @brief      SetType
* @ingroup    XUTILS
*
* @param[in]  type :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetType(XINTERPOLATOR_TYPE type)
{
  this->type = type;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR_LIMITMODE XINTERPOLATOR::GetMode()
* @brief      GetMode
* @ingroup    XUTILS
*
* @return     XINTERPOLATOR_LIMITMODE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR_LIMITMODE XINTERPOLATOR::GetMode()
{
  return mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetMode(XINTERPOLATOR_LIMITMODE mode)
* @brief      SetMode
* @ingroup    XUTILS
*
* @param[in]  mode :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetMode(XINTERPOLATOR_LIMITMODE mode)
{
  this->mode = mode;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::Get(XDWORD& current, XDWORD& target, float& speed)
* @brief      Get
* @ingroup    XUTILS
*
* @param[in]  current :
* @param[in]  target :
* @param[in]  speed :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::Get(XDWORD& current, XDWORD& target, float& speed)
{
  current = this->current;
  target  = this->target;
  speed   = this->speed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::Set(XDWORD current, XDWORD target, float speed)
* @brief      Set
* @ingroup    XUTILS
*
* @param[in]  current :
* @param[in]  target :
* @param[in]  speed :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::Set(XDWORD current,  XDWORD target, float speed)
{
  this->current = current;
  this->target  = target;
  this->speed   = speed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetCurrent()
* @brief      GetCurrent
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetCurrent()
{
  return current;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetCurrent(XDWORD current)
* @brief      SetCurrent
* @ingroup    XUTILS
*
* @param[in]  current :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetCurrent(XDWORD current)
{
  this->current = current;

  if(limits & XINTERPOLATOR_LIMITS_MAXIMUN)
    {
      if(current>(XDWORD)(GetMaximun() * GetMultiplicator()))
        {
          this->current =(XDWORD)(GetMaximun() * GetMultiplicator());
        }
    }

  if(limits & XINTERPOLATOR_LIMITS_MINIMUN)
    {
      if(this->current<(XDWORD)(GetMinimun() * GetMultiplicator()))
        {
          this->current =(XDWORD)(GetMinimun() * GetMultiplicator());
        }
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetTarget()
* @brief      GetTarget
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetTarget()
{
  return target;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XINTERPOLATOR::GetSpeed()
* @brief      GetSpeed
* @ingroup    XUTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XINTERPOLATOR::GetSpeed()
{
  return speed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetSpeed(float speed)
* @brief      SetSpeed
* @ingroup    XUTILS
*
* @param[in]  speed :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetSpeed(float speed)
{
  this->speed = speed;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetMaximun()
* @brief      GetMaximun
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetMaximun()
{
  return max;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetMaximun(XDWORD max)
* @brief      SetMaximun
* @ingroup    XUTILS
*
* @param[in]  max :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetMaximun(XDWORD max)
{
  this->max = max;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetMinimun()
* @brief      GetMinimun
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetMinimun()
{
  return min;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetMinimun(XDWORD min)
* @brief      SetMinimun
* @ingroup    XUTILS
*
* @param[in]  min :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetMinimun(XDWORD min)
{
  this->min = min;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetMultiplicator()
* @brief      GetMultiplicator
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetMultiplicator()
{
  return multiplier;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void XINTERPOLATOR::SetMultiplicator(XDWORD multiplier)
* @brief      SetMultiplicator
* @ingroup    XUTILS
* 
* @param[in]  multiplier : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetMultiplicator(XDWORD multiplier)
{
  this->multiplier = multiplier;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetFactorType(XINTERPOLATOR_FACTOR factortype)
* @brief      SetFactorType
* @ingroup    XUTILS
*
* @param[in]  factortype :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetFactorType(XINTERPOLATOR_FACTOR factortype)
{
  this->factortype = factortype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR_FACTOR XINTERPOLATOR::GetFactorType()
* @brief      GetFactorType
* @ingroup    XUTILS
*
* @return     XINTERPOLATOR_FACTOR :
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR_FACTOR XINTERPOLATOR::GetFactorType()
{
  return factortype;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetLimitFlags(XINTERPOLATOR_LIMITS limits)
* @brief      SetLimitFlags
* @ingroup    XUTILS
*
* @param[in]  limits :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetLimitFlags(XINTERPOLATOR_LIMITS limits)
{
  this->limits = limits;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XINTERPOLATOR_LIMITS XINTERPOLATOR::GetLimitFlags()
* @brief      GetLimitFlags
* @ingroup    XUTILS
*
* @return     XINTERPOLATOR_LIMITS :
*
* --------------------------------------------------------------------------------------------------------------------*/
XINTERPOLATOR_LIMITS  XINTERPOLATOR::GetLimitFlags()
{
  return limits;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::CopyFrom (XINTERPOLATOR& interpolator)
* @brief      CopyFrom
* @ingroup    XUTILS
*
* @param[in]  interpolator :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::CopyFrom(XINTERPOLATOR& interpolator)
{
  type          = interpolator.type;
  mode          = interpolator.mode;

  current       = interpolator.current;
  target        = interpolator.target;
  speed         = interpolator.speed;
  max           = interpolator.max;
  min           = interpolator.min;
  limits        = interpolator.limits;

  factortype    = interpolator.factortype;

  Update(0);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::CopyFrom(XINTERPOLATOR* interpolator)
* @brief      CopyFrom
* @ingroup    XUTILS
*
* @param[in]  interpolator :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::CopyFrom(XINTERPOLATOR* interpolator)
{
  if(!interpolator) return false;

  return CopyFrom((*interpolator));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::CopyTo(XINTERPOLATOR& interpolator)
* @brief      CopyTo
* @ingroup    XUTILS
*
* @param[in]  interpolator :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::CopyTo(XINTERPOLATOR& interpolator)
{
  interpolator.type     = type;
  interpolator.mode     = mode;

  interpolator.current  = current;
  interpolator.target   = target;
  interpolator.speed    = speed;
  interpolator.max      = max;
  interpolator.min      = min;
  interpolator.limits   = limits;

  factortype            = interpolator.factortype;

  Update(0);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::CopyTo(XINTERPOLATOR* interpolator)
* @brief      CopyTo
* @ingroup    XUTILS
*
* @param[in]  interpolator :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::CopyTo(XINTERPOLATOR* interpolator)
{
  if(!interpolator) return false;

  return CopyTo((*interpolator));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         const XINTERPOLATOR XINTERPOLATOR::operator = (XINTERPOLATOR& interpolator)
* @brief      operator =
* @ingroup    XUTILS
*
* @param[in]  interpolator :
*
* @return     const :
*
* --------------------------------------------------------------------------------------------------------------------*/
const XINTERPOLATOR XINTERPOLATOR::operator = (XINTERPOLATOR& interpolator)
{
  CopyFrom(interpolator);
  return (*this);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetTarget(XDWORD target)
* @brief      SetTarget
* @ingroup    XUTILS
*
* @param[in]  target :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetTarget(XDWORD target)
{
  //XTRACE_PRINTCOLOR(3,__L("XINTERPOLATOR::SetTarget(%d)"),target);

  if(limits & XINTERPOLATOR_LIMITS_MAXIMUN)
    {
      if(target>max)
        {
          //XTRACE_PRINTCOLOR(4,__L("Assigned over maximun: %d/%d"),target,max);

          this->target  = max;

          return;
        }
    }

  if(limits & XINTERPOLATOR_LIMITS_MINIMUN)
    {
      if(target < min)
        {
          //XTRACE_PRINTCOLOR(4,__L("Assigned under minimun: %d/%d"),target,max);

          this->target = min;

          return;
        }
    }

  this->target = target;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::Update(XQWORD delta)
* @brief      Update
* @ingroup    XUTILS
*
* @param[in]  delta :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::Update(XQWORD delta)
{
  switch(type)
    {
      case XINTERPOLATOR_TYPE_LIMIT     : Interpolate(delta);

                                          if(mode == XINTERPOLATOR_LIMITMODE_INCREMENTAL)
                                            {
                                              if(target<=current) current=target;
                                            }
                                           else
                                            {
                                              if(mode == XINTERPOLATOR_LIMITMODE_DECREMENTAL)
                                              if(target>=current) current = target;
                                            }

                                          break;

      case XINTERPOLATOR_TYPE_RELATIVE  :
      case XINTERPOLATOR_TYPE_ABSOLUTE  : if(current > target) current = target;
                                          if(current < 0)      current = 0;
                                          break;

      case XINTERPOLATOR_TYPE_NONE      : break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::Interpolate(XQWORD delta)
* @brief      Interpolate
* @ingroup    XUTILS
*
* @param[in]  delta :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::Interpolate(XQWORD delta)
{
  switch(factortype)
    {
      case XINTERPOLATOR_FACTOR_RELATIVE  : return InterpolateRelative(delta);
      case XINTERPOLATOR_FACTOR_LINEAR    : return InterpolateLinear  (delta);
      case XINTERPOLATOR_FACTOR_NONE      :
                                default   : break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XINTERPOLATOR::InterpolateLinear(XQWORD delta)
* @brief      InterpolateLinear
* @ingroup    XUTILS
* 
* @param[in]  delta : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::InterpolateLinear(XQWORD delta)
{
  float   fdelta    = (float)(delta/100.0f);
  int     itarget   = (int)(target);
  float   result    = (float)current;
  int     margin    = 0;

  if(result ==  target) return false;

  if(result < itarget)
    {
      if (delta!=0)
        {
          if (carry<0.0000001f)  carry=0.0f;

          float inc = (speed*fdelta) + carry;
          carry = inc - float((int)inc);

          result += (int)inc;
        }

      if(result >= itarget)
        {
          result  = (float)itarget;
          carry   = 0.0f;
        }

    }
   else
    {
      if(delta!=0)
        {
          if(carry<0.0000001f) carry=0.0f;

          float inc=(speed*fdelta)+carry;
          carry=inc-float((int)inc);

          result -= (int)inc;
        }

      if(result <= float(itarget))
        {
          result = (float)itarget;
          carry  = 0.0f;
        }
    }

  current = (XDWORD)result;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::InterpolateRelative(XQWORD delta)
* @brief      InterpolateRelative
* @ingroup    XUTILS
*
* @param[in]  delta :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::InterpolateRelative(XQWORD delta)
{
  float   fdelta    = (float) (delta/100.0f);
  int     itarget   = (int)   (target);
  float   result    = (float) (current);
  int     margin    = 0;

  if(result ==  target) return false;

  if(result < itarget)
    {
      if(delta!=0)
        {
          if(carry<0.0000001f) carry=0.0f;

          float dif = (float)(itarget - result);
          float inc = ((speed/100.0f)*fdelta*dif)+carry;

          carry   = inc - float((int)inc);
          result += (int)inc;
        }

      if(result > (itarget-margin))
        {
          result  = (float)itarget;
          carry   = 0.0f;
        }
    }
   else
    {
      if(delta!=0)
        {
          if (carry<0.0000001f) carry=0.0f;

          float dif = (float)(result-itarget);
          float inc = ((speed/100.0f)*fdelta*dif)+carry;

          carry   = inc - float((int)inc);
          result -= (int)inc;
        }

      if(result < float(itarget+margin))
        {
          result = (float)itarget;
          carry  = 0.0f;
        }
    }

  current = (XDWORD)result;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::DeSerialize(XBUFFER* xbuffer) const
* @brief      DeSerialize
* @ingroup    XUTILS
*
* @param[in]  xbuffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::DeSerialize(XBUFFER* xbuffer) const
{
  xbuffer->Resize(9*sizeof(XDWORD) + 1*sizeof(float));

  xbuffer->SetPosition(0);
  xbuffer->Set((XDWORD)mask);
  xbuffer->Set((XDWORD)type);
  xbuffer->Set((XDWORD)mode);
  xbuffer->Set((XDWORD)current);
  xbuffer->Set((XDWORD)target);
  xbuffer->Set((float)speed);
  xbuffer->Set((XDWORD)max);
  xbuffer->Set((XDWORD)min);
  xbuffer->Set((XDWORD)multiplier);
  xbuffer->Set((XDWORD)factortype);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::Serialize(XBUFFER* buffer)
* @brief      Serialize
* @ingroup    XUTILS
*
* @param[in]  buffer :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::Serialize(XBUFFER* buffer)
{
  XDWORD buffer_type,    buffer_target, buffer_mode,   buffer_factortype,buffer_max,      buffer_min,buffer_current,buffer_multiplier;
  float  buffer_speed;

  buffer->SetPosition(0);

  buffer->Get((XDWORD&)mask);
  buffer->Get((XDWORD&)buffer_type);
  buffer->Get((XDWORD&)buffer_mode);
  buffer->Get((XDWORD&)buffer_current);
  buffer->Get((XDWORD&)buffer_target);
  buffer->Get((float&)buffer_speed);
  buffer->Get((XDWORD&)buffer_max);
  buffer->Get((XDWORD&)buffer_min);
  buffer->Get((XDWORD&)buffer_multiplier);
  buffer->Get((XDWORD&)buffer_factortype);

  if(mask & XINTERPOLATOR_MASK_SPEED)      speed       = buffer_speed;
  if(mask & XINTERPOLATOR_MASK_MAXIMUN)    max         = buffer_max;
  if(mask & XINTERPOLATOR_MASK_MINIMUN)    min         = buffer_min;
  if(mask & XINTERPOLATOR_MASK_MULTIPLIER) multiplier  = buffer_multiplier;
  if(mask & XINTERPOLATOR_MASK_TYPE)       type        = (XINTERPOLATOR_TYPE)buffer_type;
  if(mask & XINTERPOLATOR_MASK_FACTOR)     factortype  = (XINTERPOLATOR_FACTOR)buffer_factortype;
  if(mask & XINTERPOLATOR_MASK_TARGET)     SetTarget(buffer_target);
  if(mask & XINTERPOLATOR_MASK_CURRENT)    SetCurrent(buffer_current);

  Update(0);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XINTERPOLATOR::SetMask(XDWORD mask)
* @brief      SetMask
* @ingroup    XUTILS
*
* @param[in]  mask :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XINTERPOLATOR::SetMask(XDWORD mask)
{
  this->mask = mask;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XINTERPOLATOR::GetMask()
* @brief      GetMask
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XINTERPOLATOR::GetMask()
{
  return mask;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         float XINTERPOLATOR::GetCarry()
* @brief      GetCarry
* @ingroup    XUTILS
*
* @return     float :
*
* --------------------------------------------------------------------------------------------------------------------*/
float XINTERPOLATOR::GetCarry()
{
  return carry;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::SetCarry(float carry)
* @brief      SetCarry
* @ingroup    XUTILS
*
* @param[in]  carry :
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::SetCarry(float carry)
{
  this->carry = carry;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XINTERPOLATOR::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XINTERPOLATOR::Clean()
{
  mask        = XINTERPOLATOR_MASK_ALL;
  type        = XINTERPOLATOR_TYPE_ABSOLUTE;
  mode        = XINTERPOLATOR_LIMITMODE_NONE;

  max         = 0;
  min         = 0;
  current     = 0;
  target      = 0;
  speed       = 0.0f;
  factortype  = XINTERPOLATOR_FACTOR_LINEAR;
  limits      = XINTERPOLATOR_LIMITS_NONE;
  carry       = 0.0f;
  multiplier  = 1;
}


#pragma endregion

