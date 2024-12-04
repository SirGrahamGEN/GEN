/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUUID.cpp
* 
* @class      XUUID
* @brief      eXtended Utils UUID (Universally Unique IDentifier)
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

#include "XUUID.h"

#include "XFactory.h"
#include "XDateTime.h"
#include "XRand.h"
#include "HashCRC32.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUUID::XUUID()
* @brief      Constructor
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XUUID::XUUID()
{
  Clean();

  xrand = GEN_XFACTORY.CreateRand();
  if(xrand)
    {
      xrand->Ini();
    }    
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUUID::~XUUID()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
XUUID::~XUUID()
{
  if(xrand)
    {
      GEN_XFACTORY.DeleteRand(xrand);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XUUID::GetData1()
* @brief      GetData1
* @ingroup    XUTILS
*
* @return     XDWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XUUID::GetData1()
{
  return data1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XUUID::GetData2()
* @brief      GetData2
* @ingroup    XUTILS
*
* @return     XWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XUUID::GetData2()
{
  return data2;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XUUID::GetData3()
* @brief      GetData3
* @ingroup    XUTILS
*
* @return     XWORD : 
*
* --------------------------------------------------------------------------------------------------------------------*/
XWORD XUUID::GetData3()
{
  return data3;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE XUUID::GetData4()
* @brief      GetData4
* @ingroup    XUTILS
*
* @return     XBYTE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE XUUID::GetData4()
{
  return data4;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE XUUID::GetData4()
* @brief      GetData4
* @ingroup    XUTILS
*
* @return     XBYTE : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE XUUID::GetData5()
{
  return data5;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* XUUID::GetData6()
* @brief      GetData6
* @ingroup    XUTILS
*
* @return     XBYTE* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XUUID::GetData6()
{
  return data6;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData1(XDWORD data)
* @brief      SetData1
* @ingroup    XUTILS
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData1(XDWORD data)
{
  this->data1 = data;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData2(XWORD data)
* @brief      SetData2
* @ingroup    XUTILS
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData2(XWORD data)
{
  this->data2 = data;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData3(XWORD data)
* @brief      SetData3
* @ingroup    XUTILS
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData3(XWORD data)
{
  this->data3 = data;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::SetData4(XBYTE data)
* @brief      SetData4
* @ingroup    XUTILS
*
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData4(XBYTE data)
{
  this->data4 = data;
   
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::SetData5(XBYTE data)
* @brief      SetData5
* @ingroup    XUTILS
*
* @param[in]  data : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData5(XBYTE data)
{
  this->data5 = data;
   
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData6(XBYTE* data)
* @brief      SetData6
* @ingroup    XUTILS
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData6(XBYTE* data)
{
  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      this->data6[c] = data[c];
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::Empty()
* @brief      Empty
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::Empty()
{
  data1 = 0;
  data2 = 0;
  data3 = 0;
  data4 = 0;
  data5 = 0;

  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      this->data6[c] = 0;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::Set(XDWORD data1, XWORD data2, XWORD data3, XBYTE data4, XBYTE data5, XBYTE* data6)
* @brief      Set
* @ingroup    XUTILS
*
* @param[in]  data1 : 
* @param[in]  data2 : 
* @param[in]  data3 : 
* @param[in]  data4 : 
* @param[in]  data5 : 
* @param[in]  data6 : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::Set(XDWORD data1, XWORD data2, XWORD data3, XBYTE data4, XBYTE data5, XBYTE* data6)
{
  SetData1(data1);
  SetData2(data2);
  SetData3(data3);
  SetData4(data4);
  SetData5(data5);
  SetData6(data6);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::CopyFrom(XUUID& uuid)
* @brief      CopyFrom
* @ingroup    XUTILS
*
* @param[in]  uuid : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::CopyFrom(XUUID& uuid)
{
  return Set(uuid.GetData1(), uuid.GetData2(), uuid.GetData3(), uuid.GetData4(), uuid.GetData5(), uuid.GetData6());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::CopyTo(XUUID& uuid)
* @brief      CopyTo
* @ingroup    XUTILS
*
* @param[in]  uuid : 
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::CopyTo(XUUID& uuid)
{
  return uuid.Set(data1, data2, data3, data4, data5, data6);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::GenerateRandom()
* @brief      GenerateRandom
* @ingroup    XUTILS
*
* @return     bool : true if is succesful. 
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::GenerateRandom()
{
  
  if(!xrand) 
    { 
      return false;
    }
      
  XDATETIME* GEN_XFACTORY_CREATE(datetime, CreateDateTime())
  if(!datetime)
    {
      return false;
    }

  XSTRING     datetimestr;
  HASHCRC32   hashcrc32;

  datetime->Read();
  datetime->GetDateTimeToString((XDATETIME_FORMAT_YMD | XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS | XDATETIME_FORMAT_TIMEWITHMILLISECONDS), datetimestr);

  hashcrc32.Do((XBYTE*)datetimestr.Get(), (datetimestr.GetSize() * sizeof(XCHAR)));

  data1 = hashcrc32.GetResultCRC32();
             
  if(xrand->Between(0, 1)) 
    {
      data1 |= 0x80000000;
    }
   else
    {
      data1 &= 0x7FFFFFFF;
    }
          
  data2 = (XWORD)xrand->Between(0, 65535);
  data3 = (XWORD)xrand->Between(0, 65535);

  data4 = (XBYTE)xrand->Between(0, 255);
  data5 = (XBYTE)xrand->Between(0, 255);

  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      data6[c] = (XBYTE)xrand->Max(255);
    }

  GEN_XFACTORY.DeleteDateTime(datetime);
       
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::Compare(XUUID& uuid)
* @brief      Compare
* @ingroup    XUTILS
* 
* @param[in]  uuid : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XUUID::Compare(XUUID& uuid)
{  
  if(data1 != uuid.GetData1()) 
    {
      return false;
    }

  if(data2 != uuid.GetData2()) 
    {
      return false;
    }

  if(data3 != uuid.GetData3()) 
    {
      return false;
    }

  if(data4 != uuid.GetData4()) 
    {
      return false;
    }

  if(data5 != uuid.GetData5()) 
    {
      return false;
    }

  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      if(data6[c] != uuid.GetData6()[c]) 
        {
          return false;
        }      
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::GetToString(XSTRING& string)
* @brief      GetToString
* @ingroup    XUTILS
*
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::GetToString(XSTRING& string)
{
  string.Format(__L("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"), data1
                                                                       , data2
                                                                       , data3
                                                                       , data4, data5
                                                                       , data6[0], data6[1], data6[2], data6[3], data6[4], data6[5]);
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::SetFromString(XSTRING& string)
* @brief      SetFromString
* @ingroup    XUTILS
*
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetFromString(XSTRING& string)
{
  XSTRING string2;  
  XDWORD  _data[6] = { 0, 0, 0, 0, 0, 0 };

  string2 = string;

  if(string2.IsEmpty())
    {
      return false;
    }

  string2.Insert(__L("-"), 28);

  string2.UnFormat(__L("%08X-%04X-%04X-%04X-%04X-%08X")  , &_data[0]
                                                         , &_data[1]
                                                         , &_data[2] 
                                                         , &_data[3]
                                                         , &_data[4]
                                                         , &_data[5]);
  data1     = (XDWORD)_data[0];
  data2     = (XWORD)_data[1];
  data3     = (XWORD)_data[2];  

  data4     = (XBYTE)(_data[3] >> 8);
  data5     = (XBYTE)(_data[3] & 0x00FF);

  data6[0]  = (XBYTE)(_data[4] >> 8);
  data6[1]  = (XBYTE)(_data[4] & 0x00FF);
  
  data6[2]  = (XBYTE)((_data[5] >> 24) & 0x000000FF);
  data6[3]  = (XBYTE)((_data[5] >> 16) & 0x000000FF);
  data6[4]  = (XBYTE)((_data[5] >>  8) & 0x000000FF);
  data6[5]  = (XBYTE)(_data[5] & 0x000000FF);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XUUID::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* --------------------------------------------------------------------------------------------------------------------*/
void XUUID::Clean()
{
  xrand     = NULL;

  Empty();
}


#pragma endregion

