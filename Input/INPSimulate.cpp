/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPSimulate.cpp
* 
* @class      INPSIMULATE
* @brief      Input Simulate
* @ingroup    INPUT
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

#include "INPSimulate.h"

#include "XString.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

INPUTSIMULATE_KDB_PC  inputsimulare_KDB_PC[]						= { { 0x01	, __L("Left mouse")						     , ALTERNATIVE_KEY_NONE			  },					
																														{ 0x02	, __L("Right mouse")					     , ALTERNATIVE_KEY_NONE			  },					                                                           
			                                                      { 0x03	, __L("Control-break")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x04	, __L("Middle mouse")					     , ALTERNATIVE_KEY_NONE			  },					 
			                                                      { 0x05	, __L("X1 mouse")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x06	, __L("X2 mouse")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x08	, __L("BACKSPACE")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x09	, __L("TAB")							         , ALTERNATIVE_KEY_NONE			  },																															
			                                                      { 0x0C	, __L("CLEAR")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x0D	, __L("ENTER")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x10	, __L("SHIFT")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x11	, __L("CTRL")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x12	, __L("ALT")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x13	, __L("PAUSE")						         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x14	, __L("CAPS LOCK")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x15	, __L("IME Kana mode")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x15	, __L("IME Hanguel mode")				   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x15	, __L("IME Hangul mode")				   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x16	, __L("IME On")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x17	, __L("IME Junja mode")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x18	, __L("IME final mode")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x19	, __L("IME Hanja mode")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x19	, __L("IME Kanji mode")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1A	, __L("IME Off")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1B	, __L("ESC")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1C	, __L("IME convert")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1D	, __L("IME nonconvert")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1E	, __L("IME accept")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x1F	, __L("IME mode change request")	 , ALTERNATIVE_KEY_NONE			 	},					
			                                                      { 0x20	, __L("SPACEBAR")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x21	, __L("PAGE UP")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x22	, __L("PAGE DOWN")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x23	, __L("END")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x24	, __L("HOME")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x25	, __L("LEFT ARROW")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x26	, __L("UP ARROW")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x27	, __L("RIGHT ARROW")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x28	, __L("DOWN ARROW")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x29	, __L("SELECT")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2A	, __L("PRINT")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2B	, __L("EXECUTE")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2C	, __L("PRINT SCREEN")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2D	, __L("INS")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2E	, __L("DEL")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x2F	, __L("HELP")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x30	, __L("0")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x31	, __L("1")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x32	, __L("2")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x33	, __L("3")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x34	, __L("4")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x35	, __L("5")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x36	, __L("6")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x37	, __L("7")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x38	, __L("8")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x39	, __L("9")								         , ALTERNATIVE_KEY_NONE			  },																																	                                                      				
			                                                      { 0x41	, __L("A")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x42	, __L("B")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x43	, __L("C")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x44	, __L("D")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x45	, __L("E")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x46	, __L("F")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x47	, __L("G")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x48	, __L("H")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x49	, __L("I")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4A	, __L("J")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4B	, __L("K")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4C	, __L("L")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4D	, __L("M")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4E	, __L("N")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x4F	, __L("O")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x50	, __L("P")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x51	, __L("Q")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x52	, __L("R")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x53	, __L("S")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x54	, __L("T")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x55	, __L("U")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x56	, __L("V")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x57	, __L("W")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x58	, __L("X")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x59	, __L("Y")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x5A	, __L("Z")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x5B	, __L("Left Windows")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x5C	, __L("Right Windows")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x5D	, __L("Applications")					     , ALTERNATIVE_KEY_NONE			  },																																		                                                                          
			                                                      { 0x5F	, __L("Computer Sleep")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x61	, __L("Numericpad 1")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x60	, __L("Numericpad 0")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x62	, __L("Numericpad 2")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x63	, __L("Numericpad 3")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x64	, __L("Numericpad 4")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x65	, __L("Numericpad 5")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x66	, __L("Numericpad 6")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x67	, __L("Numericpad 7")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x68	, __L("Numericpad 8")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x69	, __L("Numericpad 9")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6A	, __L("Multiply")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6B	, __L("Add")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6C	, __L("Separator")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6D	, __L("Subtract")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6E	, __L("Decimal")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x6F	, __L("Divide")							       , ALTERNATIVE_KEY_NONE			  },	
																														{ 0x70	, __L("F1")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x71	, __L("F2")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x72	, __L("F3")								         , ALTERNATIVE_KEY_NONE			  },								                                                      
			                                                      { 0x73	, __L("F4")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x74	, __L("F5")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x75	, __L("F6")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x76	, __L("F7")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x77	, __L("F8")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x78	, __L("F9")								         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x79	, __L("F10")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7A	, __L("F11")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7B	, __L("F12")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7C	, __L("F13")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7D	, __L("F14")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7E	, __L("F15")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x7F	, __L("F16")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x80	, __L("F17")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x81	, __L("F18")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x82	, __L("F19")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x83	, __L("F20")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x84	, __L("F21")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x85	, __L("F22")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x86	, __L("F23")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x87	, __L("F24")							         , ALTERNATIVE_KEY_NONE			  },																												                                                                          
			                                                      { 0x90	, __L("NUM LOCK")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0x91	, __L("SCROLL LOCK")					     , ALTERNATIVE_KEY_NONE			  },					                                                                          
			                                                      { 0xA0	, __L("Left SHIFT")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA1	, __L("Right SHIFT")				 	     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA2	, __L("Left CONTROL")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA3	, __L("Right CONTROL")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA4	, __L("Left ALT")						       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA5	, __L("Right ALT")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA6	, __L("Browser Back")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA7	, __L("Browser Forward")				   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA8	, __L("Browser Refresh")				   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xA9	, __L("Browser Stop")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAA	, __L("Browser Search")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAB	, __L("Browser Favorites")				 , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAC	, __L("Browser Home")		      		 , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAD	, __L("Volume Mute")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAE	, __L("Volume Down")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xAF	, __L("Volume Up")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB0	, __L("Next Track")					       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB1	, __L("Previous Track")					   , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB2	, __L("Stop Media")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB3	, __L("Play/Pause Media")					 , ALTERNATIVE_KEY_NONE			  },
			                                                      { 0xB4	, __L("Start Mail")						     , ALTERNATIVE_KEY_NONE			  },					
 			                                                      { 0xB5	, __L("Select Media")					     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB6	, __L("Start Application 1")			 , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xB7	, __L("Start Application 2")			 , ALTERNATIVE_KEY_NONE			  },					                                                                          			                                                     			                                                       		
			                                                      { 0xE5	, __L("IME PROCESS")						   , ALTERNATIVE_KEY_NONE			  },					                                                                   
			                                                      { 0xF6	, __L("Attn")							         , ALTERNATIVE_KEY_NONE			  },						
			                                                      { 0xF7	, __L("CrSel")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xF8	, __L("ExSel")							       , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xF9	, __L("Erase EOF")						     , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xFA	, __L("Play")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xFB	, __L("Zoom")							         , ALTERNATIVE_KEY_NONE			  },	  				
			                                                      { 0xFD	, __L("PA1")							         , ALTERNATIVE_KEY_NONE			  },					
			                                                      { 0xFE	, __L("Clear")							       , ALTERNATIVE_KEY_NONE			  }
                                                          };	


INPUTSIMULATE_KDB_PC  inputsimulare_KDB_PC_Spanish[]		= { { 0xDC  , __L("\xBA")								  		 , ALTERNATIVE_KEY_NONE       },
																														{ 0xDC  , __L("\xAA")										   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0xDC  , __L("\\")											   , ALTERNATIVE_KEY_ALTGR      },
																														{ 0x31  , __L("!")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x31  , __L("|")											   , ALTERNATIVE_KEY_ALTGR      },
																														{ 0x32  , __L("\"")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x32  , __L("@")											   , ALTERNATIVE_KEY_ALTGR      },
																														{ 0x33  , __L("\x95")										   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x33  , __L("#")											   , ALTERNATIVE_KEY_ALTGR      },
																														{ 0x34  , __L("$")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x35  , __L("%")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x36  , __L("&")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x37  , __L("/")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x38  , __L("(")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x39  , __L(")")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0x30  , __L("=")											   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xDB  , __L("'")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xDB  , __L("?")											   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xDD  , __L("\xA1")										   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xDD  , __L("\xBF")										   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xBA  , __L("`")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBA  , __L("^")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0xBA  , __L("[")											   , ALTERNATIVE_KEY_ALTGR      },

																														{ 0xBB  , __L("+")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBB  , __L("*")											   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0xBB  , __L("]")											   , ALTERNATIVE_KEY_ALTGR      },

																														{ 0xC0  , __L("\xF1")											 , ALTERNATIVE_KEY_NONE	      },
																														{ 0xC0  , __L("\xD1")										   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xDE  , __L("\xB4")										   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xDE  , __L("\xA8")										   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0xDE  , __L("{")											   , ALTERNATIVE_KEY_ALTGR      },

																														{ 0xBF  , __L("\xE7")										   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBF  , __L("\xC7")										   , ALTERNATIVE_KEY_SHIFT      },
																														{ 0xBF  , __L("}")											   , ALTERNATIVE_KEY_ALTGR      },

																														{ 0xE2  , __L("<")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xE2  , __L(">")											   , ALTERNATIVE_KEY_SHIFT      },
																														
																														{ 0xBC  , __L(",")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBC  , __L(";")											   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xBE  , __L(".")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBE  , __L(":")											   , ALTERNATIVE_KEY_SHIFT      },

																														{ 0xBD  , __L("-")											   , ALTERNATIVE_KEY_NONE	      },
																														{ 0xBD  , __L("_")											   , ALTERNATIVE_KEY_SHIFT      },																														
																													};

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE::INPSIMULATE()
* @brief      Constructor of class
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE::INPSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE::~INPSIMULATE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE::~INPSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_Press(XBYTE code)
* @brief      Key press
* @ingroup    INPUT
* 
* @param[in]  code : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_Press(XBYTE code)
{
	return false;
}	


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_UnPress(XBYTE code)
* @brief      Key un press
* @ingroup    INPUT
* 
* @param[in]  code : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_UnPress(XBYTE code)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_Click(XBYTE code, int pressuretime)
* @brief      Key click
* @ingroup    INPUT
* 
* @param[in]  code : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_Click(XBYTE code, int pressuretime)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_PressByLiteral(XCHAR* literal)
* @brief      Key press by literal
* @ingroup    INPUT
* 
* @param[in]  literal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_PressByLiteral(XCHAR* literal)
{
	return false;
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_UnPressByLiteral(XCHAR* literal)
* @brief      Key un press by literal
* @ingroup    INPUT
* 
* @param[in]  literal : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_UnPressByLiteral(XCHAR* literal)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_ClickByLiteral(XCHAR* literal, int pressuretime)
* @brief      Key click by literal
* @ingroup    INPUT
* 
* @param[in]  literal : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_ClickByLiteral(XCHAR* literal, int pressuretime)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Key_ClickByText(XCHAR* text, int pressuretimeinterval)
* @brief      Key click by text
* @ingroup    INPUT
* 
* @param[in]  text : 
* @param[in]  pressuretimeinterval : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Key_ClickByText(XCHAR* text, int pressuretimeinterval)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::Mouse_SetPos(int x, int y)
* @brief      Mouse set pos
* @ingroup    INPUT
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Mouse_SetPos(int x, int y)
{ 
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPSIMULATE::Mouse_Click(int x, int y)
* @brief      Mouse click
* @ingroup    INPUT
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::Mouse_Click(int x, int y)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE INPSIMULATE::GetKDBCodeByLiteral(XCHAR* literal, ALTERNATIVE_KEY& altkey)
* @brief      Get KDB code by literal
* @ingroup    INPUT
* 
* @param[in]  literal : 
* @param[in]  altkey : 
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE INPSIMULATE::GetKDBCodeByLiteral(XCHAR* literal, ALTERNATIVE_KEY& altkey)
{
	XSTRING _literal = literal;

	if(_literal.IsEmpty())
		{
			return 0;
		}

	altkey = ALTERNATIVE_KEY_NONE;

	for(XDWORD c=0; c<(sizeof(inputsimulare_KDB_PC)/sizeof(INPUTSIMULATE_KDB_PC)); c++)
		{
			if(!_literal.Compare(inputsimulare_KDB_PC[c].literal, true))
				{
				  altkey = inputsimulare_KDB_PC[c].altkey;
					return inputsimulare_KDB_PC[c].code;
				}					
		}

	for(XDWORD c=0; c<(sizeof(inputsimulare_KDB_PC_Spanish)/sizeof(INPUTSIMULATE_KDB_PC)); c++)
		{
			if(!_literal.Compare(inputsimulare_KDB_PC_Spanish[c].literal, true))
				{
					altkey = inputsimulare_KDB_PC_Spanish[c].altkey;
					return inputsimulare_KDB_PC_Spanish[c].code;
				}					
		}

	return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPSIMULATE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    INPUT
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPSIMULATE::Clean()
{

}


#pragma endregion


