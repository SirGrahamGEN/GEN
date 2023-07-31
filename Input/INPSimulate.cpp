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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#include "INPSimulate.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XString.h"

#include "XMemory_Control.h"


#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

INPUTSIMULATE_KDB_PC  inputsimulare_KDB_PC[]						= { { 0x02	, __L("Right mouse")					      },					
                                                            { 0x01	, __L("Left mouse")						      },					
			                                                      { 0x03	, __L("Control-break")					    },					
			                                                      { 0x04	, __L("Middle mouse")					      },					 
			                                                      { 0x05	, __L("X1 mouse")						        },					
			                                                      { 0x06	, __L("X2 mouse")						        },					
			                                                      { 0x07	, __L("Undefined")						      },					
			                                                      { 0x08	, __L("BACKSPACE")						      },					
			                                                      { 0x09	, __L("TAB")							          },					
			                                                      { 0x0C	, __L("CLEAR")							        },					
			                                                      { 0x0D	, __L("ENTER")							        },					
			                                                      { 0x10	, __L("SHIFT")							        },					
			                                                      { 0x11	, __L("CTRL")							          },					
			                                                      { 0x12	, __L("ALT")							          },					
			                                                      { 0x13	, __L("PAUSE")						        	},					
			                                                      { 0x14	, __L("CAPS LOCK")						      },					
			                                                      { 0x15	, __L("IME Kana mode")					    },					
			                                                      { 0x15	, __L("IME Hanguel mode")				    },					
			                                                      { 0x15	, __L("IME Hangul mode")				    },					
			                                                      { 0x16	, __L("IME On")							        },					
			                                                      { 0x17	, __L("IME Junja mode")					    },					
			                                                      { 0x18	, __L("IME final mode")					    },					
			                                                      { 0x19	, __L("IME Hanja mode")					    },					
			                                                      { 0x19	, __L("IME Kanji mode")					    },					
			                                                      { 0x1A	, __L("IME Off")						        },					
			                                                      { 0x1B	, __L("ESC")							          },					
			                                                      { 0x1C	, __L("IME convert")					      },					
			                                                      { 0x1D	, __L("IME nonconvert")					    },					
			                                                      { 0x1E	, __L("IME accept")						      },					
			                                                      { 0x1F	, __L("IME mode change request")		},					
			                                                      { 0x20	, __L("SPACEBAR")						        },					
			                                                      { 0x21	, __L("PAGE UP")						        },					
			                                                      { 0x22	, __L("PAGE DOWN")						      },					
			                                                      { 0x23	, __L("END")							          },					
			                                                      { 0x24	, __L("HOME")							          },					
			                                                      { 0x25	, __L("LEFT ARROW")						      },					
			                                                      { 0x26	, __L("UP ARROW")						        },					
			                                                      { 0x27	, __L("RIGHT ARROW")					      },					
			                                                      { 0x28	, __L("DOWN ARROW")						      },					
			                                                      { 0x29	, __L("SELECT")							        },					
			                                                      { 0x2A	, __L("PRINT")							        },					
			                                                      { 0x2B	, __L("EXECUTE")						        },					
			                                                      { 0x2C	, __L("PRINT SCREEN")					      },					
			                                                      { 0x2D	, __L("INS")							          },					
			                                                      { 0x2E	, __L("DEL")							          },					
			                                                      { 0x2F	, __L("HELP")							          },					
			                                                      { 0x30	, __L("0")								          },					
			                                                      { 0x31	, __L("1")								          },					
			                                                      { 0x32	, __L("2")								          },					
			                                                      { 0x33	, __L("3")								          },					
			                                                      { 0x34	, __L("4")								          },					
			                                                      { 0x35	, __L("5")								          },					
			                                                      { 0x36	, __L("6")								          },					
			                                                      { 0x37	, __L("7")								          },					
			                                                      { 0x38	, __L("8")								          },					
			                                                      { 0x39	, __L("9")								          },					
			                                                      				
			                                                      { 0x41	, __L("A")								          },					
			                                                      { 0x42	, __L("B")								          },					
			                                                      { 0x43	, __L("C")								          },					
			                                                      { 0x44	, __L("D")								          },					
			                                                      { 0x45	, __L("E")								          },					
			                                                      { 0x46	, __L("F")								          },					
			                                                      { 0x47	, __L("G")								          },					
			                                                      { 0x48	, __L("H")								          },					
			                                                      { 0x49	, __L("I")								          },					
			                                                      { 0x4A	, __L("J")								          },					
			                                                      { 0x4B	, __L("K")								          },					
			                                                      { 0x4C	, __L("L")								          },					
			                                                      { 0x4D	, __L("M")								          },					
			                                                      { 0x4E	, __L("N")								          },					
			                                                      { 0x4F	, __L("O")								          },					
			                                                      { 0x50	, __L("P")								          },					
			                                                      { 0x51	, __L("Q")								          },					
			                                                      { 0x52	, __L("R")								          },					
			                                                      { 0x53	, __L("S")								          },					
			                                                      { 0x54	, __L("T")								          },					
			                                                      { 0x55	, __L("U")								          },					
			                                                      { 0x56	, __L("V")								          },					
			                                                      { 0x57	, __L("W")								          },					
			                                                      { 0x58	, __L("X")								          },					
			                                                      { 0x59	, __L("Y")								          },					
			                                                      { 0x5A	, __L("Z")								          },					
			                                                      { 0x5B	, __L("Left Windows")					      },					
			                                                      { 0x5C	, __L("Right Windows")					    },					
			                                                      { 0x5D	, __L("Applications")					      },					
                                                                          
			                                                      { 0x5F	, __L("Computer Sleep")					    },					
			                                                      { 0x61	, __L("Numericpad 1")					      },					
			                                                      { 0x60	, __L("Numericpad 0")					      },					
			                                                      { 0x62	, __L("Numericpad 2")					      },					
			                                                      { 0x63	, __L("Numericpad 3")					      },					
			                                                      { 0x64	, __L("Numericpad 4")					      },					
			                                                      { 0x65	, __L("Numericpad 5")					      },					
			                                                      { 0x66	, __L("Numericpad 6")					      },					
			                                                      { 0x67	, __L("Numericpad 7")					      },					
			                                                      { 0x68	, __L("Numericpad 8")					      },					
			                                                      { 0x69	, __L("Numericpad 9")					      },					
			                                                      { 0x6A	, __L("Multiply")						        },					
			                                                      { 0x6B	, __L("Add")							          },					
			                                                      { 0x6C	, __L("Separator")						      },					
			                                                      { 0x6D	, __L("Subtract")						        },					
			                                                      { 0x6E	, __L("Decimal")						        },					
			                                                      { 0x6F	, __L("Divide")							        },					
			                                                      { 0x71	, __L("F2")								          },					
			                                                      { 0x72	, __L("F3")								          },					
			                                                      { 0x70	, __L("F1")								          },					
			                                                      { 0x73	, __L("F4")								          },					
			                                                      { 0x74	, __L("F5")								          },					
			                                                      { 0x75	, __L("F6")								          },					
			                                                      { 0x76	, __L("F7")								          },					
			                                                      { 0x77	, __L("F8")								          },					
			                                                      { 0x78	, __L("F9")								          },					
			                                                      { 0x79	, __L("F10")							          },					
			                                                      { 0x7A	, __L("F11")							          },					
			                                                      { 0x7B	, __L("F12")							          },					
			                                                      { 0x7C	, __L("F13")							          },					
			                                                      { 0x7D	, __L("F14")							          },					
			                                                      { 0x7E	, __L("F15")							          },					
			                                                      { 0x7F	, __L("F16")							          },					
			                                                      { 0x80	, __L("F17")							          },					
			                                                      { 0x81	, __L("F18")							          },					
			                                                      { 0x82	, __L("F19")							          },					
			                                                      { 0x83	, __L("F20")							          },					
			                                                      { 0x84	, __L("F21")							          },					
			                                                      { 0x85	, __L("F22")							          },					
			                                                      { 0x86	, __L("F23")							          },					
			                                                      { 0x87	, __L("F24")							          },					
                                                                          
			                                                      { 0x90	, __L("NUM LOCK")						        },					
			                                                      { 0x91	, __L("SCROLL LOCK")					      },					
                                                                          
			                                                      { 0xA0	, __L("Left SHIFT")						      },					
			                                                      { 0xA1	, __L("Right SHIFT")				 	      },					
			                                                      { 0xA2	, __L("Left CONTROL")					      },					
			                                                      { 0xA3	, __L("Right CONTROL")					    },					
			                                                      { 0xA4	, __L("Left ALT")						        },					
			                                                      { 0xA5	, __L("Right ALT")						      },					
			                                                      { 0xA6	, __L("Browser Back")					      },					
			                                                      { 0xA7	, __L("Browser Forward")				    },					
			                                                      { 0xA8	, __L("Browser Refresh")				    },					
			                                                      { 0xA9	, __L("Browser Stop")					      },					
			                                                      { 0xAA	, __L("Browser Search")					    },					
			                                                      { 0xAB	, __L("Browser Favorites")				  },					
			                                                      { 0xAC	, __L("Browser Home")		      			},					
			                                                      { 0xAD	, __L("Volume Mute")					      },					
			                                                      { 0xAE	, __L("Volume Down")					      },					
			                                                      { 0xAF	, __L("Volume Up")						      },					
			                                                      { 0xB0	, __L("Next Track")					      	},					
			                                                      { 0xB1	, __L("Previous Track")					    },					
			                                                      { 0xB2	, __L("Stop Media")						      },					
			                                                      { 0xB3	, __L("Play/Pause Media")						},
			                                                      { 0xB4	, __L("Start Mail")						      },					
 			                                                      { 0xB5	, __L("Select Media")					      },					
			                                                      { 0xB6	, __L("Start Application 1")			  },					
			                                                      { 0xB7	, __L("Start Application 2")			  },					
                                                                          
			                                                      { 0xBA	, __L(";:")								          },					
			                                                      { 0xBB	, __L("+")								          },					
			                                                      { 0xBC	, __L(",")								          },					
			                                                      { 0xBD	, __L("-")								          },					
			                                                      { 0xBE	, __L(".")								          },					
			                                                      { 0xBF	, __L("?")								          },					
			                                                      { 0xC0	, __L("~")								          },					
                                                                          
			                                                      { 0xDB	, __L("[{")								          },					
			                                                      { 0xDC	, __L("|")								          },					
			                                                      { 0xDD	, __L("]}")								          },					
			                                                      { 0xDE	, __L("\"")								          },					
			                                                       		
			                                                      { 0xE5	, __L("TIME PROCESS")						    },					
                                                                   
			                                                      { 0xF6	, __L("Attn")							          },						
			                                                      { 0xF7	, __L("CrSel")							        },					
			                                                      { 0xF8	, __L("ExSel")							        },					
			                                                      { 0xF9	, __L("Erase EOF")						      },					
			                                                      { 0xFA	, __L("Play")							          },					
			                                                      { 0xFB	, __L("Zoom")							          },	  				
			                                                      { 0xFD	, __L("PA1")							          },					
			                                                      { 0xFE	, __L("Clear")							        }
                                                          };		

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE::INPSIMULATE()
* @brief      Constructor
* @ingroup    INPUT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE::INPSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         INPSIMULATE::~INPSIMULATE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    INPUT
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
INPSIMULATE::~INPSIMULATE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::PressKey(XBYTE code, int pressuretime)
* @brief      PressKey
* @ingroup    INPUT
* 
* @param[in]  code : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::PressKey(XBYTE code, int pressuretime)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::PressKeyByLiteral(XCHAR* literal, int pressuretime)
* @brief      PressKeyByLiteral
* @ingroup    INPUT
* 
* @param[in]  literal : 
* @param[in]  pressuretime : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::PressKeyByLiteral(XCHAR* literal, int pressuretime)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::PressKeyByText(XCHAR* text, int pressuretimeinterval)
* @brief      PressKeyByText
* @ingroup    INPUT
* 
* @param[in]  text : 
* @param[in]  pressuretimeinterval : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::PressKeyByText(XCHAR* text, int pressuretimeinterval)
{
	return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool INPSIMULATE::SetMoudePos(int x, int y)
* @brief      SetMousePos
* @ingroup    INPUT
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::SetMousePos(int x, int y)
{ 
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPSIMULATE::SetMouseClick(int x, int y)
* @brief      SetMouseClick
* @ingroup    INPUT
* 
* @param[in]  x : 
* @param[in]  y : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool INPSIMULATE::SetMouseClick(int x, int y)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE INPSIMULATE::GetKDBCodeByLiteral(XCHAR* literal)
* @brief      GetKDBCodeByLiteral
* @ingroup    INPUT
* 
* @param[in]  literal : 
* 
* @return     XBYTE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE INPSIMULATE::GetKDBCodeByLiteral(XCHAR* literal)
{
	XSTRING _literal = literal;

	if(_literal.IsEmpty())
		{
			return 0;
		}

	for(XDWORD c=0; c<(sizeof(inputsimulare_KDB_PC)/sizeof(INPUTSIMULATE_KDB_PC)); c++)
		{
			if(!_literal.Compare(inputsimulare_KDB_PC[c].literal, true))
				{
					return inputsimulare_KDB_PC[c].code;
				}					
		}

	return 0;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void INPSIMULATE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    INPUT
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void INPSIMULATE::Clean()
{

}


#pragma endregion


