/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOSNMP.cpp
* 
* @class      DIOSNMP
* @brief      Data Input/Output SNMP (Simple Network Management Protocol)
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

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DIOSNMP.h"

#include "XFactory.h"
#include "XRand.h"
#include "XBuffer.h"
#include "XTrace.h"

#include "DIOFactory.h"
#include "DIOStreamUDPConfig.h"
#include "DIOStreamUDP.h"

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


#pragma region CLASS_DIOSNMP_XBER


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_XBER::DIOSNMP_XBER(): XBER()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_XBER::DIOSNMP_XBER(): XBER()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_XBER::~DIOSNMP_XBER()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_XBER::~DIOSNMP_XBER()
{

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_XBER::SetIPADDRESS(XCHAR* IPstring)
* @brief      Set IPADDRESS
* @ingroup    DATAIO
*
* @param[in]  IPstring : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_XBER::SetIPADDRESS(XCHAR* IPstring)
{
  if(!IPstring)     return false;
  if(!IPstring[0])  return false;

  /*
  if(!data)         return false;

  data->Delete();

  XSTRING       string;
  XVECTOR<int>  numbers;
  int           start = 0;
  int           end   = 0;

  string = IPstring;

  while(1)
    {
      XSTRING numberstring;
      int     indexstring = string.Find(__L("."),true,start);

      if(indexstring != XSTRING_NOTFOUND)
        {
          end = indexstring;
          string.Copy(start,end,numberstring);
          numbers.Add(numberstring.ConvertToInt());
          start = end+1;
        }
       else
        {
          string.Copy(end+1,numberstring);
          numbers.Add(numberstring.ConvertToInt());

          break;
        }
    }

  if(!numbers.GetSize()) return false;

  for(XDWORD c=0;c<numbers.GetSize();c++)
    {
      size_t _number = (size_t)(numbers.Get(c));
      int number = (int)(_number);
      data->Add((XBYTE)(number));
    }

  this->type = (XBYTE)(DIOSNMPBERTYPE_IPADDRESS | XBER_TAGTYPE_ISAPPLICATION);
  this->size = data->GetSize();
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_XBER::SetTIMETICKS(XDWORD ticks)
* @brief      Set TIMETICKS
* @ingroup    DATAIO
*
* @param[in]  ticks : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_XBER::SetTIMETICKS(XDWORD ticks)
{
  bool status = SetINTEGER(ticks);

  this->tagtype = (XBYTE)(DIOSNMPBERTYPE_TIMETICKS | XBER_TAGCLASS_APPLICATION);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_XBER::Sequence_AddTo(XBER& xber)
* @brief      Sequence add to
* @ingroup    DATAIO
*
* @param[in]  xber : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_XBER::Sequence_AddTo(XBER& xber)
{
  bool status = XBER::Sequence_AddTo(xber);

  this->tagtype |= (XBYTE)(XBER_TAG_MASKISCONSTRUCTED);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_XBER::TrapData_AddTo(XBER& xber)
* @brief      Trap data add to
* @ingroup    DATAIO
*
* @param[in]  xber : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_XBER::TrapData_AddTo(XBER& xber)
{
  bool status = XBER::Sequence_AddTo(xber);

  this->tagtype = (XBYTE)(DIOSNMPBERTYPE_TRAPPDU | XBER_TAGTYPE_CONTEXT_SPECIFIC | XBER_TAG_MASKISCONSTRUCTED);

  return status;
}


#pragma endregion


#pragma region CLASS_DIOSNMP_BASE


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_BASE::DIOSNMP_BASE()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_BASE::DIOSNMP_BASE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_BASE::~DIOSNMP_BASE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_BASE::~DIOSNMP_BASE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMUDPCONFIG* DIOSNMP_BASE::GetDIOStreamUDPCFG()
* @brief      Get DIO stream UDPCFG
* @ingroup    DATAIO
*
* @return     DIOSTREAMUDPCONFIG* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDPCONFIG* DIOSNMP_BASE::GetDIOStreamUDPCFG()
{
  return diostreamudpcfg;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSTREAMUDP* DIOSNMP_BASE::GetDIOStreamUDP()
* @brief      Get DIO stream UDP
* @ingroup    DATAIO
*
* @return     DIOSTREAMUDP* : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSTREAMUDP* DIOSNMP_BASE::GetDIOStreamUDP()
{
  return diostreamudp;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_VERSION DIOSNMP_BASE::GetVersion()
* @brief      Get version
* @ingroup    DATAIO
*
* @return     DIOSNMP_VERSION : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_VERSION DIOSNMP_BASE::GetVersion()
{
  return version;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSNMP_BASE::SetVersion(DIOSNMP_VERSION version)
* @brief      Set version
* @ingroup    DATAIO
*
* @param[in]  version : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOSNMP_BASE::SetVersion(DIOSNMP_VERSION version)
{
  this->version = version;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_BASE::Open(XCHAR* IPtarget, int port, bool checkavailableNMS, XCHAR* localIP)
* @brief      Open
* @ingroup    DATAIO
* 
* @param[in]  IPtarget : 
* @param[in]  port : 
* @param[in]  checkavailableNMS : 
* @param[in]  localIP : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_BASE::Open(XCHAR* IPtarget, int port, bool checkavailableNMS, XCHAR* localIP)
{
  if(!IPtarget)     return false;
  if(!IPtarget[0])  return false;

  diostreamudpcfg = new DIOSTREAMUDPCONFIG();
  if(!diostreamudpcfg)  return false;

  diostreamudpcfg->SetMode(DIOSTREAMMODE_CLIENT);

  if(localIP) diostreamudpcfg->GetLocalIP()->Set(localIP);

  diostreamudpcfg->GetRemoteURL()->Set(IPtarget);
  diostreamudpcfg->SetRemotePort(port);

  bool status = false;

  diostreamudp = (DIOSTREAMUDP*)GEN_DIOFACTORY.CreateStreamIO(diostreamudpcfg);
  if(diostreamudp)
    {
      if(diostreamudp->Open())
        {
          if(checkavailableNMS)
            {
              //--------------------------------------------
              // Write something to received a ICMP result.
              // and check if something is the other side.

              status = diostreamudp->WaitToConnected(3);
              if(status)
                {
                  XBYTE data[] = { 0xAA,0x55 };
                  diostreamudp ->Write(data,sizeof(data));

                  status = diostreamudp->WaitToDisconnected(3);
                }

            } else status = true;
        }
    }

  if(!status) Close();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_BASE::Close()
* @brief      Close
* @ingroup    DATAIO
*
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_BASE::Close()
{
  diostreamudp->WaitToFlushXBuffers();

  if(diostreamudp)
    {
      diostreamudp->Close();
      GEN_DIOFACTORY.DeleteStreamIO(diostreamudp);
      diostreamudp = NULL;
    }

  if(diostreamudpcfg)
    {
      delete diostreamudpcfg;
      diostreamudpcfg = NULL;
    }

  return true;
}

     
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSNMP_BASE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOSNMP_BASE::Clean()
{
  diostreamudpcfg = NULL;
  diostreamudp    = NULL;

  version         = DIOSNMP_VERSION_V1;
}


#pragma endregion


#pragma region CLASS_DIOSNMP_TRAP


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_TRAP::DIOSNMP_TRAP()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_TRAP::DIOSNMP_TRAP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP_TRAP::~DIOSNMP_TRAP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP_TRAP::~DIOSNMP_TRAP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP_TRAP::Send(XCHAR* community,XCHAR* enterprise,XCHAR* agentip,int generictrap,int specifictrap,XDWORD timestamp,int nvar,...)
* @brief      Send
* @ingroup    DATAIO
* 
* @param[in]  community : 
* @param[in]  enterprise : 
* @param[in]  agentip : 
* @param[in]  generictrap : 
* @param[in]  specifictrap : 
* @param[in]  timestamp : 
* @param[in]  nvar : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP_TRAP::Send(XCHAR* community,XCHAR* enterprise,XCHAR* agentip,int generictrap,int specifictrap,XDWORD timestamp,int nvar,...)
{
  if(!diostreamudpcfg)  return false;
  if(!diostreamudp)     return false;

  XBUFFER      xbuffer;
  DIOSNMP_XBER  trap;
  DIOSNMP_XBER  trapdata;
  DIOSNMP_XBER  trapvars;
  DIOSNMP_XBER  trapvar;
  DIOSNMP_XBER  xber;

  // ----------------------------------------------------------------
  // Trap
  xber.SetINTEGER(version);         trap.Sequence_AddTo(xber);        // Version SNMPv1
  xber.SetOCTETSTRING(community);   trap.Sequence_AddTo(xber);        // Community

  // ----------------------------------------------------------------
  // Trap Data

  xber.SetOID(enterprise);          trapdata.TrapData_AddTo(xber);    // Enterprise
  xber.SetIPADDRESS(agentip);       trapdata.TrapData_AddTo(xber);    // IP Address
  xber.SetINTEGER(generictrap);     trapdata.TrapData_AddTo(xber);    // Generic-trap
  xber.SetINTEGER(specifictrap);    trapdata.TrapData_AddTo(xber);    // Specific-trap
  xber.SetTIMETICKS(timestamp);     trapdata.TrapData_AddTo(xber);    // timestamp

  // ----------------------------------------------------------------
  // Trap Data Variable
  // (only available, for the moment, the next types: INTEGER, STRING and OIDs
  //
  if(nvar)
    {
      if(!(nvar%2))
        {
          va_list arg;

          va_start(arg,nvar);

          for(int c=0;c<(nvar/2);c++)
            {
              trapvar.Sequence_DeleteAll();

             for(int d=0;d<2;d++)
                {
                  int type = (int)va_arg(arg, int);

                  switch(type)
                    {
                      case XBER_TAGTYPE_INTEGER       : { int integer = (int)va_arg(arg, int);
                                                          xber.SetINTEGER(integer);
                                                          trapvar.Sequence_AddTo(xber);
                                                        }
                                                        break;

                      case XBER_TAGTYPE_OCTET_STRING  : { XCHAR* OCTETstring = (XCHAR*)va_arg(arg, XCHAR*);
                                                          if(OCTETstring)
                                                            {
                                                              xber.SetOCTETSTRING(OCTETstring);
                                                              trapvar.Sequence_AddTo(xber);
                                                            }
                                                        }
                                                        break;

                      case XBER_TAGTYPE_OID_IRI       : { XCHAR* OIDstring = (XCHAR*)va_arg(arg, XCHAR*);
                                                          if(OIDstring)
                                                            {
                                                              xber.SetOID(OIDstring);
                                                              trapvar.Sequence_AddTo(xber);
                                                            }
                                                        }
                                                        break;

                                    default           : break;
                    }
                }

              trapvars.Sequence_AddTo(trapvar);
            }

          va_end(arg);

          trapdata.TrapData_AddTo(trapvars);
       }
    }

  trap.Sequence_AddTo(trapdata);

  trap.GetDump(xbuffer);

  //DEBUG_PRINTDATABLOCK(xbuffer.Get(),xbuffer.GetSize(),2);

  XDWORD bw = diostreamudp->Write(xbuffer.Get(),xbuffer.GetSize());
  if(bw!= xbuffer.GetSize()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSNMP_TRAP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOSNMP_TRAP::Clean()
{

}


#pragma endregion


#pragma region CLASS_DIOSNMP


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP::DIOSNMP()
* @brief      Constructor of class
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP::DIOSNMP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DIOSNMP::~DIOSNMP()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
DIOSNMP::~DIOSNMP()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP::Get(DIOSNMP_OPERATION operation, XCHAR* community, XCHAR* OIDstr, DIOSNMP_XBER& xberout)
* @brief      Get
* @ingroup    DATAIO
*
* @param[in]  operation : 
* @param[in]  community : 
* @param[in]  OIDstr : 
* @param[in]  xberout : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP::Get(DIOSNMP_OPERATION operation, XCHAR* community, XCHAR* OIDstr, DIOSNMP_XBER& xberout)
{
  #define MAX_READBUFFER  2048

  if(!diostreamudpcfg)  return false;
  if(!diostreamudp)     return false;
  
  XBUFFER       xbuffer;
  XBUFFER       xbufferdata;  
  XDWORD        number = 0;
  DIOSNMP_XBER  xber;
  DIOSNMP_XBER  value;
  DIOSNMP_XBER  bindings;
  DIOSNMP_XBER  request;
  DIOSNMP_XBER  data_next_request;
  DIOSNMP_XBER  header;  

  // ----------------------------------------------------------------
  // Get-Next 

  xber.SetOID(OIDstr);                                        value.Sequence_AddTo(xber);          // OID
  xber.SetNULL();                                             value.Sequence_AddTo(xber);          // NULL  

  XRAND* GEN_XFACTORY_CREATE(xrand, CreateRand())
  if(xrand)
    {
      number = xrand->Max(65000);
      GEN_XFACTORY.DeleteRand(xrand);
    }

  xber.SetINTEGER(number);                                    bindings.Sequence_AddTo(xber);        // Request-ID 
  xber.SetINTEGER(0);                                         bindings.Sequence_AddTo(xber);        // Error-status 
  xber.SetINTEGER(0);                                         bindings.Sequence_AddTo(xber);        // Error-index

  request.Sequence_AddTo(value);
  bindings.Sequence_AddTo(request);  
  
  data_next_request.Sequence_AddCommandTo(DIOSNMP_OPERATION_GETNEXTREQUEST, bindings); 

  xber.SetINTEGER(version);                                   header.Sequence_AddTo(xber);        // Version 
  xber.SetOCTETSTRING(community);                             header.Sequence_AddTo(xber);        // Community   
  
  header.Sequence_AddTo(data_next_request);     

  header.GetDump(xbuffer);

  XDWORD bw = diostreamudp->Write(xbuffer.Get(), xbuffer.GetSize());
  if(bw!= xbuffer.GetSize()) return false;

  xbuffer.Empty();
  xbuffer.Resize(MAX_READBUFFER);

  XTIMER* GEN_XFACTORY_CREATE(timeout, CreateTimer())
  if(!timeout) return false;

  do{ XDWORD sizeread  = diostreamudp->GetInXBuffer()->GetSize();
      if(sizeread)
        {
          XDWORD br = diostreamudp->Read(xbuffer.Get(), sizeread);
          if(br)
            {
              timeout->Reset();
              xbufferdata.Add(xbuffer.Get(), br);  
            }      
        }
      
      if(timeout->GetMeasureSeconds() > 2) break; 

    } while(1);

  GEN_XFACTORY.DeleteTimer(timeout);

  if(xbufferdata.GetSize())
    {
      xberout.SetTagType(xbufferdata.Get()[0]);
      xberout.SetSize(xbufferdata.Get()[1]);  
      xberout.GetData()->Add(&xbufferdata.Get()[2], xbufferdata.GetSize());
    }
  
  return xbufferdata.GetSize()?true:false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DIOSNMP::Send(XCHAR* community,XCHAR* enterprise,XCHAR* agentip,int generictrap,int specifictrap,XDWORD timestamp,int nvar,...)
* @brief      Send
* @ingroup    DATAIO
*
* @param[in]  community : 
* @param[in]  enterprise : 
* @param[in]  agentip : 
* @param[in]  generictrap : 
* @param[in]  specifictrap : 
* @param[in]  timestamp : 
* @param[in]  nvar : 
* @param[in]  ... : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DIOSNMP::Send(XCHAR* community,XCHAR* enterprise,XCHAR* agentip,int generictrap,int specifictrap,XDWORD timestamp,int nvar,...)
{
  if(!diostreamudpcfg)  return false;
  if(!diostreamudp)     return false;

  XBUFFER       xbuffer;
  DIOSNMP_XBER  trap;
  DIOSNMP_XBER  trapdata;
  DIOSNMP_XBER  trapvars;
  DIOSNMP_XBER  trapvar;
  DIOSNMP_XBER  xber;

  // ----------------------------------------------------------------
  // Trap
  xber.SetINTEGER(0);               trap.Sequence_AddTo(xber);        // Version SNMPv1
  xber.SetOCTETSTRING(community);   trap.Sequence_AddTo(xber);        // Community

  // ----------------------------------------------------------------
  // Trap Data

  xber.SetOID(enterprise);          trapdata.TrapData_AddTo(xber);    // Enterprise
  xber.SetIPADDRESS(agentip);       trapdata.TrapData_AddTo(xber);    // IP Address
  xber.SetINTEGER(generictrap);     trapdata.TrapData_AddTo(xber);    // Generic-trap
  xber.SetINTEGER(specifictrap);    trapdata.TrapData_AddTo(xber);    // Specific-trap
  xber.SetTIMETICKS(timestamp);     trapdata.TrapData_AddTo(xber);    // timestamp

  // ----------------------------------------------------------------
  // Trap Data Variable
  // (only available, for the moment, the next types: INTEGER, STRING and OIDs
  //
  if(nvar)
    {
      if(!(nvar%2))
        {
          va_list arg;

          va_start(arg,nvar);

          for(int c=0;c<(nvar/2);c++)
            {
              trapvar.Sequence_DeleteAll();

             for(int d=0;d<2;d++)
                {
                  int type = (int)va_arg(arg, int);

                  switch(type)
                    {
                      case XBER_TAGTYPE_INTEGER       : { int integer = (int)va_arg(arg, int);
                                                          xber.SetINTEGER(integer);
                                                          trapvar.Sequence_AddTo(xber);
                                                        }
                                                        break;

                      case XBER_TAGTYPE_OCTET_STRING  : { XCHAR* OCTETstring = (XCHAR*)va_arg(arg, XCHAR*);
                                                          if(OCTETstring)
                                                            {
                                                              xber.SetOCTETSTRING(OCTETstring);
                                                              trapvar.Sequence_AddTo(xber);
                                                            }
                                                        }
                                                        break;

                      case XBER_TAGTYPE_OID_IRI       : { XCHAR* OIDstring = (XCHAR*)va_arg(arg, XCHAR*);
                                                          if(OIDstring)
                                                            {
                                                              xber.SetOID(OIDstring);
                                                              trapvar.Sequence_AddTo(xber);
                                                            }
                                                        }
                                                        break;

                                    default           : break;
                    }
                }

              trapvars.Sequence_AddTo(trapvar);
            }

          va_end(arg);

          trapdata.TrapData_AddTo(trapvars);
       }
    }

  trap.Sequence_AddTo(trapdata);

  trap.GetDump(xbuffer);

  //DEBUG_PRINTDATABLOCK(xbuffer.Get(),xbuffer.GetSize(),2);

  XDWORD bw = diostreamudp->Write(xbuffer.Get(),xbuffer.GetSize());
  if(bw!= xbuffer.GetSize()) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DIOSNMP::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    DATAIO
*
* ---------------------------------------------------------------------------------------------------------------------*/
void DIOSNMP::Clean()
{

}
  

#pragma endregion


#pragma endregion



