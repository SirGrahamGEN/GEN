/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUUID.cpp
*
* @class      XUUID
* @brief      eXtended UUID Universally Unique IDentifier 
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2005 - 2020 GEN Group.
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

#include "XFactory.h"
#include "XDateTime.h"
#include "XRand.h"
#include "HashCRC32.h"

#include "XUUID.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUUID::XUUID()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     Does not return anything. 
*
*---------------------------------------------------------------------------------------------------------------------*/
XUUID::XUUID()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUUID::~XUUID()
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
XUUID::~XUUID()
{
  Clean();
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XUUID::GetData1()
* @brief      GetData1
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XDWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XUUID::GetData1()
{
  return data1;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XUUID::GetData2()
* @brief      GetData2
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD XUUID::GetData2()
{
  return data2;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XWORD XUUID::GetData3()
* @brief      GetData3
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XWORD : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XWORD XUUID::GetData3()
{
  return data3;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE* XUUID::GetData4()
* @brief      GetData4
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     XBYTE* : 
*
*---------------------------------------------------------------------------------------------------------------------*/
XBYTE* XUUID::GetData4()
{
  return data4;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData1(XDWORD data)
* @brief      SetData1
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData1(XDWORD data)
{
  this->data1 = data;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData2(XWORD data)
* @brief      SetData2
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData2(XWORD data)
{
  this->data2 = data;

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData3(XWORD data)
* @brief      SetData3
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData3(XWORD data)
{
  this->data3 = data;

  return true;
}





/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::SetData4(XBYTE* data)
* @brief      SetData4
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  data : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetData4(XBYTE* data)
{
  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      this->data4[c] = data[c];
    }

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::Set(XDWORD data1, XWORD data2, XWORD data3, XBYTE* data4)
* @brief      Set
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  data1 : 
* @param[in]  data2 : 
* @param[in]  data3 : 
* @param[in]  data4 : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::Set(XDWORD data1, XWORD data2, XWORD data3, XBYTE* data4)
{
  SetData1(data1);
  SetData2(data2);
  SetData3(data3);
  SetData4(data4);

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::CopyFrom(XUUID& uuid)
* @brief      CopyFrom
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  uuid : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::CopyFrom(XUUID& uuid)
{
  return Set(uuid.GetData1(), uuid.GetData2(), uuid.GetData3(), uuid.GetData4());
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::CopyTo(XUUID& uuid)
* @brief      CopyTo
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @param[in]  uuid : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::CopyTo(XUUID& uuid)
{
  return uuid.Set(data1, data2, data3, data4);
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUUID::GenerateRandom()
* @brief      GenerateRandom
* @ingroup    UTILS
*
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::GenerateRandom()
{
  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(xrand) 
    { 
      xrand->Ini();

      XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
      if(datetime)
        {
          XSTRING     datetimestr;
          HASHCRC32   hashcrc32;

          datetime->Read();
          datetime->GetDateTimeToString((XDATETIME_FORMAT_YMD | XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS), datetimestr);

          hashcrc32.Do((XBYTE*)datetimestr.Get(), (datetimestr.GetSize() * sizeof(XCHAR)));

          data1 = hashcrc32.GetResultCRC32();
          
          for(int c=0; c<sizeof(XDWORD); c++)
            {
              data1 ^= (XBYTE)xrand->Max(255);
              if(c!=sizeof(XDWORD)-1) data1 <<= 8;
            }
  
          if(xrand->Between(0, 1)) data1 |= 0x80000000;
          

          data2 = (XWORD)xrand->Between(0, 65535);
          data3 = (XWORD)xrand->Between(0, 65535);

          for(int c=0; c<XUUIDMAXDATA4; c++)
            {
              data4[c] = (XBYTE)xrand->Max(255);
            }

          GEN_XFACTORY.DeleteDateTime(datetime);
        }

      GEN_XFACTORY.DeleteRand(xrand);
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::GetToString(XSTRING& string)
* @brief      GetToString
* @ingroup    UTILS
* 
* @author     Abraham J. Velez 
* @date       30/11/2021 10:44:41
* 
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::GetToString(XSTRING& string)
{
  string.Format(__L("%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X"), data1, data2, data3, data4[0]
                                                                                           , data4[1]
                                                                                           , data4[2]
                                                                                           , data4[3]
                                                                                           , data4[4]
                                                                                           , data4[5]
                                                                                           , data4[6]
                                                                                           , data4[7]);
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUUID::SetFromString(XSTRING& string)
* @brief      SetFromString
* @ingroup    UTILS
* 
* @author     Abraham J. Velez 
* @date       30/11/2021 10:46:20
* 
* @param[in]  string : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUUID::SetFromString(XSTRING& string)
{
  int _data[11];

  memset(_data, 0, sizeof(int)*11);

  string.UnFormat(__L("%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X"), &_data[0], &_data[1], &_data[2],  &_data[3]
                                                                                                          , &_data[4]
                                                                                                          , &_data[5]
                                                                                                          , &_data[6]
                                                                                                          , &_data[7]
                                                                                                          , &_data[8]
                                                                                                          , &_data[9]
                                                                                                          , &_data[10]);
  data1     = _data[0];
  data2     = (XWORD)_data[1];
  data3     = (XWORD)_data[2];
  
  data4[0]  = (XBYTE)_data[3];
  data4[1]  = (XBYTE)_data[4];
  data4[2]  = (XBYTE)_data[5];
  data4[3]  = (XBYTE)_data[6];
  data4[4]  = (XBYTE)_data[7];
  data4[5]  = (XBYTE)_data[8];
  data4[6]  = (XBYTE)_data[9];
  data4[7]  = (XBYTE)_data[10];

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XUUID::Clean()
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
void XUUID::Clean()
{
  data1 = 0;
  data2 = 0;
  data3 = 0;

  for(int c=0; c<XUUIDMAXDATA4; c++)
    {
      this->data4[c] = 0;
    }

}
