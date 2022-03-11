/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       FactoryBase.h
* 
* @class      FACTORYBASE
* @brief      Factory Base class
* @ingroup    PLATFORM_COMMON
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2022 GEN Group.
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
* *---------------------------------------------------------------------------------------------------------------------*/

#ifndef _FACTORYBASE_H_
#define _FACTORYBASE_H_

#ifdef XMEMORY_CONTROL_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define FACTORY_MODULE(variable)    variable->SetModule(__FILE__);

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class FACTORYBASE
{
  public:
                              FACTORYBASE         ()    
                              { 
                                Clean();                            
                              }

    virtual                  ~FACTORYBASE         ()    
                              { 
                                Clean();                            
                              }

    void                      SetModule           (const char* _pathmodule)
                              {
                                memcpy(pathmodule, _pathmodule, strlen(_pathmodule));
                              }  


  private:

    char*                     pathmodule[256];

    void                      Clean               ()
                              {
                                memset(pathmodule, 0, 256);
                              }
};

#else

class FACTORYBASE
{

};

#define FACTORY_MODULE(variable)   

#endif

#endif


