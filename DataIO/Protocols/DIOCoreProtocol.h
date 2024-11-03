/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOCoreProtocol.h
* 
* @class      DIOCOREPROTOCOL
* @brief      Data Input/Output Core Protocol class
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

#ifndef _DIOCOREPROTOCOL_H_
#define _DIOCOREPROTOCOL_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XFileJSON.h"

#include "DIOStream.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define DIOCOREPROTOCOL_DEBUG_BUFFER

#pragma endregion


/*---- CLASS ---------------------------------------------------------c------------------------------------------------*/
#pragma region CLASS


class COMPRESSMANAGER;
class COMPRESSBASE;    	
class DIOCOREPROTOCOL_HEADER;
class DIOCOREPROTOCOL_CFG;


class DIOCOREPROTOCOL
{
  public:
                                              
                                              DIOCOREPROTOCOL               (DIOCOREPROTOCOL_CFG* protocolCFG, DIOSTREAM* diostream, XUUID* IDmachine);
    virtual                                  ~DIOCOREPROTOCOL               ();

    bool                                      Ini                           ();
    bool                                      End                           ();
    
    bool                                      SendMsg                       (XBUFFER& content);
    bool                                      SendMsg                       (XSTRING& content);
    bool                                      SendMsg                       (XFILEJSON& content);
    
    bool                                      ReceivedMsg                   (DIOCOREPROTOCOL_HEADER& header, XBUFFER& content);

  protected:

    DIOCOREPROTOCOL_CFG*                      protocolCFG;
    DIOSTREAM*                                diostream; 
    bool                                      initialization; 
    
  private:

    DIOCOREPROTOCOL_HEADER*                   CreateHeader                  (XBUFFER& content, XBUFFER& contentresult);
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                  (XSTRING& content, XBUFFER& contentresult);
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                  (XFILEJSON& content, XBUFFER& contentresult);

    bool                                      GenerateHeaderToSend          (DIOCOREPROTOCOL_HEADER* header, XBUFFER& headerdatasend, XWORD* headersize = NULL);
    DIOCOREPROTOCOL_HEADER*                   CreateHeader                  ();
 
    bool                                      SendMsg                       (DIOCOREPROTOCOL_HEADER* header, XBUFFER& contentresult);

    bool                                      SendData                      (XBUFFER& senddata);
    bool                                      CompressContent               (DIOCOREPROTOCOL_HEADER* header, XBUFFER& content, XBUFFER& contentresult);

    void                                      Clean                         ();   
   
    XUUID*                                    ID_machine;
    
    COMPRESSMANAGER*	                        compressmanager;
    COMPRESSBASE*			                        compressor;    	   

    #ifdef DIOCOREPROTOCOL_DEBUG_BUFFER
    XBUFFER                                   debug_senddata;  
    #endif
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


