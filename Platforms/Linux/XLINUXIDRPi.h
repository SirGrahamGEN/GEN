/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXIDRPi.h
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

#ifndef _XLINUXIDRPI_H_
#define _XLINUXIDRPI_H_


#ifdef HW_RASPBERRYPI


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum RPI_MODEL
{
  RPI_MODEL_UNKNOWN           =   0 ,
  RPI_MODEL_A                       ,
  RPI_MODEL_B                       ,
  RPI_MODEL_A_PLUS                  ,
  RPI_MODEL_B_PLUS                  ,
  RPI_MODEL_COMPUTERMODULE          ,
  RPI_MODEL_B_2                     ,
  RPI_MODEL_ZERO                    ,
  RPI_MODEL_CM3                     ,
  RPI_MODEL_CM3P                    ,
  RPI_MODEL_B_3                     ,
  RPI_MODEL_B_3P                    ,
  RPI_MODEL_B_4                     ,
  RPI_MODEL_B_5                     ,
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class XLINUXIDRPI 
{
  public:
                                        XLINUXIDRPI           ();
    virtual                            ~XLINUXIDRPI           ();
  
    RPI_MODEL                           GetModel              ();
    int                                 GetRAMMegabytes       ();
    float                               GetRevision           (); 

   
  private:

    bool                                DetectBoard           (RPI_MODEL& model, int& megabytes, float& revision);
    
    void                                Clean                 ();
    
    RPI_MODEL                           model;
    int                                 megabytes;
    float                               revision; 
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif

