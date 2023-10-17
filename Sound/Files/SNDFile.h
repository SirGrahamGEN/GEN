/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       SNDFile.h
* 
* @class      SNDFILE
* @brief      Sound File class
* @ingroup    SOUND
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

#ifndef _SNDFILE_H_
#define _SNDFILE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XFile.h"
#include "XPath.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class SNDFILE 
{
  public:

                                    SNDFILE                               ();    
    virtual                        ~SNDFILE                               ();
    
    XSTRING*                        GetID                                 ();

    XBUFFER*                        GetData                               ();
    XWORD                           GetChannels                           ();
    XDWORD                          GetNSamples                           ();
    XDWORD                          GetSampleRate                         ();    
    float                           GetDuration                           ();

    virtual bool                    LoadFile                              (XCHAR* path , XCHAR* ID, bool instream);
    bool                            LoadFile                              (XPATH& xpath, XCHAR* ID, bool instream);

    bool                            WriteRaw                              (XCHAR* path, XCHAR* ID);
    bool                            WriteRaw                              (XPATH& xpath, XCHAR* ID);
    
    virtual bool                    Reset                                 ();

  protected:
      
    XSTRING                         ID;
    bool                            isstream;
   
    XWORD                           channels;
    XDWORD                          nsamples;
    XDWORD                          samplerate;
    float                           duration;   

    XBUFFER*                        xbuffer;
    XBUFFER*                        xbufferdecodeddata;    

  private:

    void                            Clean                                 ();                                 
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
