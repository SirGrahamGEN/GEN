/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol_CFG.h
* 
* @class      DIOCOREPROTOCOL_CFG
* @brief      Data Input/Output Core Protocol CFG class
* @ingroup    DATAIO
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

#ifndef _DIOCOREPROTOCOL_CFG_H_
#define _DIOCOREPROTOCOL_CFG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include "XFileJSON.h"

#include "DIOStreamConfig.h"
#include "DIOStream.h"


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOCOREPROTOCOL_CFG_DEFAULT_MINSIZECOMPRESS                         150 

#define DIOCOREPROTOCOL_CFG_DEFAULT_TIMEOUTNORESPONSE                       5 

#define DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOELIMINATECONNECTIONDISCONNECT     60 
#define DIOCOREPROTOCOL_CFG_DEFAULT_TIMETOHEARDBETINCONNECTION              5 


#pragma endregion


/*---- CLASS ---------------------------------------------------------c------------------------------------------------*/
#pragma region CLASS


class DIOCOREPROTOCOL_CFG
{
  public:

                                              DIOCOREPROTOCOL_CFG                       ();                                              
    virtual                                  ~DIOCOREPROTOCOL_CFG                       ();

    bool                                      GetIsServer                               ();
    void                                      SetIsServer                               (bool isserver);

    bool                                      GetCompressHeader                         ();
    void                                      SetCompressHeader                         (bool compressheader);

    bool                                      GetCompressContent                        ();
    void                                      SetCompressContent                        (bool compresscontent);

    XDWORD                                    GetMinSizeCompressContent                 ();
    void                                      SetMinSizeCompressContent                 (XDWORD minsizecompresscontent);

    XDWORD                                    GetTimeOutNoResponse                      ();
    void                                      SetTimeOutNoResponse                      (XDWORD timeoutnoresponse);
      
    XDWORD                                    GetTimeToEliminateConnectionDisconnect    ();
    void                                      SetTimeToEliminateConnectionDisconnect    (XDWORD timetoeliminateconnectiondisconnect);
      
    XDWORD                                    GetTimeToHeardbetInConnection             ();
    void                                      SetTimeToHeardbetInConnection             (XDWORD timetoheardbetinconnection);
    
  private:

    void                                      Clean                                     ();

    bool                                      isserver;

    bool                                      compressheader;

    bool                                      compresscontent;
    XDWORD                                    minsizecompresscontent;

    XDWORD                                    timeoutnoresponse;

    XDWORD                                    timetoeliminateconnectiondisconnect;
    XDWORD                                    timetoheardbetinconnection;    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


