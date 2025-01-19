/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXIDRPi.cpp
* 
* @class      XLINUXIDRPI
* @brief      LINUX eXtended Utils IDentification Raspberry Pi class
* @ingroup    PLATFORM_LINUX
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


#ifdef HW_RASPBERRYPI


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XLINUXIDRPi.h"

#include "XTrace.h"
#include "XSleep.h"
#include "XFileTXT.h"
#include "XTrace.h"

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
* @fn         XLINUXIDRPI::XLINUXIDRPI()
* @brief      Constructor of class
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXIDRPI::XLINUXIDRPI()
{
  Clean();

  DetectBoard(model, megabytes, revision);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XLINUXIDRPI::~XLINUXIDRPI()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
XLINUXIDRPI::~XLINUXIDRPI()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         RPI_MODEL XLINUXIDRPI::GetModel()
* @brief      Get model
* @ingroup    PLATFORM_LINUX
* 
* @return     RPI_MODEL : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
RPI_MODEL XLINUXIDRPI::GetModel()
{
  return model;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int XLINUXIDRPI::GetRAMMegabytes()
* @brief      Get RAM megabytes
* @ingroup    PLATFORM_LINUX
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int XLINUXIDRPI::GetRAMMegabytes()
{
  return megabytes;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         float XLINUXIDRPI::GetRevision()
* @brief      Get revision
* @ingroup    PLATFORM_LINUX
* 
* @return     float : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
float XLINUXIDRPI::GetRevision()
{
  return revision;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XLINUXIDRPI::DetectBoard(RPI_MODEL& model, int& megabytes, float& revision)
* @brief      Detect board
* @ingroup    PLATFORM_LINUX
* 
* @param[in]  model : 
* @param[in]  megabytes : 
* @param[in]  revision : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXIDRPI::DetectBoard(RPI_MODEL& model, int& megabytes, float& revision)
{
  XPATH     xpath;
  XFILETXT* xfiletxt;
  bool      status = false;

  xpath = __L("/proc/cpuinfo");
  
  xfiletxt = new XFILETXT();
  if(!xfiletxt) return false;

  if(xfiletxt->Open(xpath))
    {
      xfiletxt->ReadAllFile();

      for(int c=0;c< xfiletxt->GetNLines(); c++)
        {
          XSTRING* line = xfiletxt->GetLine(c);
          if(line)
            {
              if(line->Find(__L("Revision"), false) != XSTRING_NOTFOUND)
                {
                  int position = line->Find(__L(":"), true);
                  if(position != XSTRING_NOTFOUND)
                    {
                      line->DeleteCharacters(0, position+1);
                      line->DeleteCharacter(0x20);

                      model = RPI_MODEL_UNKNOWN;

                      // https://www.raspberrypi.org/documentation/hardware/raspberrypi/revision-codes/README.md

                      if(!line->Compare(__L("0002")   , true))  { model = RPI_MODEL_B;                megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0003")   , true))  { model = RPI_MODEL_B;                megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0004")   , true))  { model = RPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0005")   , true))  { model = RPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0006")   , true))  { model = RPI_MODEL_B;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0007")   , true))  { model = RPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0008")   , true))  { model = RPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("0009")   , true))  { model = RPI_MODEL_A;                megabytes = 256;      revision = 2.0f; }
                      if(!line->Compare(__L("000d")   , true))  { model = RPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("000e")   , true))  { model = RPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("000f")   , true))  { model = RPI_MODEL_B;                megabytes = 512;      revision = 2.0f; }
                      if(!line->Compare(__L("0010")   , true))  { model = RPI_MODEL_B_PLUS;           megabytes = 512;      revision = 1.0f; }
                      if(!line->Compare(__L("0011")   , true))  { model = RPI_MODEL_COMPUTERMODULE;   megabytes = 512;      revision = 1.0f; }
                      if(!line->Compare(__L("0012")   , true))  { model = RPI_MODEL_A_PLUS;           megabytes = 256;      revision = 1.0f; }
                      if(!line->Compare(__L("0013")   , true))  { model = RPI_MODEL_B_PLUS;           megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("a01041") , true))  { model = RPI_MODEL_B_2;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("a21041") , true))  { model = RPI_MODEL_B_2;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("900092") , true))  { model = RPI_MODEL_ZERO;             megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("900093") , true))  { model = RPI_MODEL_ZERO;             megabytes = 512;      revision = 1.2f; }
                      if(!line->Compare(__L("a220a0") , true))  { model = RPI_MODEL_CM3;            	megabytes = 1024;     revision = 1.0f; }
                      if(!line->Compare(__L("a02082") , true))  { model = RPI_MODEL_B_3;              megabytes = 1024;     revision = 1.2f; }
                      if(!line->Compare(__L("a22082") , true))  { model = RPI_MODEL_B_3;              megabytes = 1024;     revision = 1.2f; }
                      if(!line->Compare(__L("a22083") , true))  { model = RPI_MODEL_B_3;              megabytes = 1024;     revision = 1.3f; }	
                      if(!line->Compare(__L("a02100") , true))  { model = RPI_MODEL_CM3P;            	megabytes = 1024;     revision = 1.0f; }
                      if(!line->Compare(__L("a020d3") , true))  { model = RPI_MODEL_B_3P;             megabytes = 1024;     revision = 1.2f; }                      
                      if(!line->Compare(__L("a03111") , true))  { model = RPI_MODEL_B_4;              megabytes = 1024;     revision = 1.1f; }
                      if(!line->Compare(__L("b03111") , true))  { model = RPI_MODEL_B_4;              megabytes = 2048;     revision = 1.1f; }
                      if(!line->Compare(__L("b03112") , true))  { model = RPI_MODEL_B_4;              megabytes = 2048;     revision = 1.2f; }
                      if(!line->Compare(__L("c03111") , true))  { model = RPI_MODEL_B_4;              megabytes = 4096;     revision = 1.1f; }
                      if(!line->Compare(__L("c03112") , true))  { model = RPI_MODEL_B_4;              megabytes = 4096;     revision = 1.2f; }
                      if(!line->Compare(__L("c04170") , true))  { model = RPI_MODEL_B_5;              megabytes = 4096;     revision = 1.0f; }
                      if(!line->Compare(__L("d04170") , true))  { model = RPI_MODEL_B_5;              megabytes = 8192;     revision = 1.0f; }                                                                        
                            
                      // XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L(" Rpi ID: %d"), model);
   
                      if(model != RPI_MODEL_UNKNOWN)
                        {
                          status = true;
                          break;
                        }
                    }
                }
            }
        }

      xfiletxt->Close();
    }

  delete xfiletxt;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XLINUXIDRPI::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_LINUX
*
* --------------------------------------------------------------------------------------------------------------------*/
void XLINUXIDRPI::Clean()
{
  model           = RPI_MODEL_UNKNOWN;
  megabytes       = 0;
  revision        = 0.0f;  
}


#pragma endregion


#endif

