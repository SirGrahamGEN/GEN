/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       INPANDROIDDeviceKeyboard.h
* 
* @class      INPANDROIDDEVICEKEYBOARD
* @brief      ANDROID Input device keyboard class
* @ingroup    PLATFORM_ANDROID
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

#ifndef _INPANDROIDDEVICEKEYBOARD_H_
#define _INPANDROIDDEVICEKEYBOARD_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XVector.h"

#include "INPButton.h"
#include "INPDevice.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

#define KEYCODE_A                       0x001d  // Keyboard a and A
#define KEYCODE_B                       0x001e  // Keyboard b and B
#define KEYCODE_C                       0x001f  // Keyboard c and C
#define KEYCODE_D                       0x0020  // Keyboard d and D
#define KEYCODE_E                       0x0021  // Keyboard e and E
#define KEYCODE_F                       0x0022  // Keyboard f and F
#define KEYCODE_G                       0x0023  // Keyboard g and G
#define KEYCODE_H                       0x0024  // Keyboard h and H
#define KEYCODE_I                       0x0025  // Keyboard i and I
#define KEYCODE_J                       0x0026  // Keyboard j and J
#define KEYCODE_K                       0x0027  // Keyboard k and K
#define KEYCODE_L                       0x0028  // Keyboard l and L
#define KEYCODE_M                       0x0029  // Keyboard m and M
#define KEYCODE_N                       0x002a  // Keyboard n and N
#define KEYCODE_O                       0x002b  // Keyboard o and O
#define KEYCODE_P                       0x002c  // Keyboard p and P
#define KEYCODE_Q                       0x002d  // Keyboard q and Q
#define KEYCODE_R                       0x002e  // Keyboard r and R
#define KEYCODE_S                       0x002f  // Keyboard s and S
#define KEYCODE_T                       0x0030  // Keyboard t and T
#define KEYCODE_U                       0x0031  // Keyboard u and U
#define KEYCODE_V                       0x0032  // Keyboard v and V
#define KEYCODE_W                       0x0033  // Keyboard w and W
#define KEYCODE_X                       0x0034  // Keyboard x and X
#define KEYCODE_Y                       0x0035  // Keyboard y and Y
#define KEYCODE_Z                       0x0036  // Keyboard z and Z
#define KEYCODE_1                       0x0008  // Keyboard 1 and !
#define KEYCODE_2                       0x0009  // Keyboard 2 and @
#define KEYCODE_3                       0x000a  // Keyboard 3 and #
#define KEYCODE_4                       0x000b  // Keyboard 4 and $
#define KEYCODE_5                       0x000c  // Keyboard 5 and %
#define KEYCODE_6                       0x000d  // Keyboard 6 and ^
#define KEYCODE_7                       0x000e  // Keyboard 7 and &
#define KEYCODE_8                       0x000f  // Keyboard 8 and *
#define KEYCODE_9                       0x0010  // Keyboard 9 and (
#define KEYCODE_0                       0x0007  // Keyboard 0 and )
#define KEYCODE_ENTER                   0x0042  // Keyboard Return (ENTER)
#define KEYCODE_ESCAPE                  0x006f  // Keyboard ESCAPE  0x0001  KEY_ESC 3.0 0x006f  ""  ""  ""  ""  2.3 0x0004  KEYCODE_BACK
#define KEYCODE_BACKSPACE               0x0043  // Keyboard DELETE (Backspace)  0x000e    1.6 0x0043
#define KEYCODE_TAB                     0x003d  // Keyboard Tab 0x000f  KEY_TAB 1.6 0x003d
#define KEYCODE_SPACE                   0x003e  // Keyboard Spacebar  0x0039  KEY_SPACE 1.6 0x003e
#define KEYCODE_MINUS                   0x0045  // Keyboard - and _ 0x000c  KEY_MINUS 1.6 0x0045
#define KEYCODE_EQUALS                  0x0046  // Keyboard = and + 0x000d  KEY_EQUAL 1.6 0x0046  1
#define KEYCODE_LEFT_BRACKET            0x0047  // Keyboard [ and { 0x001a  KEY_LEFTBRACE 1.6 0x0047  1
#define KEYCODE_RIGHT_BRACKET           0x0048  // Keyboard ] and } 0x001b  KEY_RIGHTBRACE  1.6 0x0048    1
#define KEYCODE_BACKSLASH               0x0049  // Keyboard \ and | 0x002b  KEY_BACKSLASH 1.6 0x0049    1
#define KEYCODE_BACKSLASH2              0x0049  // Keyboard Non-US # and ~  0x002b  KEY_BACKSLASH 1.6 0x0049    1
#define KEYCODE_SEMICOLON               0x004a  // Keyboard ; and : 0x0027  KEY_SEMICOLON 1.6 0x004a  1
#define KEYCODE_APOSTROPHE              0x004b  // Keyboard ' and " 0x0028  KEY_APOSTROPHE  1.6 0x004b    1
#define KEYCODE_GRAVE                   0x0044  // Keyboard ` and ~ 0x0029  KEY_GRAVE 3.0 0x0044  1
#define KEYCODE_COMMA                   0x0037  // Keyboard , and < 0x0033  KEY_COMMA 1.6 0x0037  1
#define KEYCODE_PERIOD                  0x0038  // Keyboard . and > 0x0034  KEY_DOT 1.6 0x0038  1
#define KEYCODE_SLASH                   0x004c  // Keyboard / and ? 0x0035  KEY_SLASH 1.6 0x004c  1
#define KEYCODE_CAPS_LOCK               0x0073  // Keyboard Caps Lock 0x003a  KEY_CAPSLOCK  3.0 0x0073
#define KEYCODE_F1                      0x0083  // Keyboard F1  0x003b  KEY_F1  3.0 0x0083    ""  ""  ""  ""  1.6 0x0052  KEYCODE_MENU
#define KEYCODE_F2                      0x0084  // Keyboard F2  0x003c  KEY_F2  3.0 0x0084    ""  ""  ""  ""  1.6 0x0002  KEYCODE_SOFT_RIGHT
#define KEYCODE_F3                      0x0085  // Keyboard F3  0x003d  KEY_F3  3.0 0x0085    ""  ""  ""  ""  1.6 0x0005  KEYCODE_CALL
#define KEYCODE_F4                      0x0086  // Keyboard F4  0x003e  KEY_F4  3.0 0x0086    ""  ""  ""  ""  1.6 0x0006  KEYCODE_ENDCALL
#define KEYCODE_F5                      0x0087  // Keyboard F5  0x003f  KEY_F5  3.0 0x0087
#define KEYCODE_F6                      0x0088  // Keyboard F6  0x0040  KEY_F6  3.0 0x0088
#define KEYCODE_F7                      0x0089  // Keyboard F7  0x0041  KEY_F7  3.0 0x0089
#define KEYCODE_F8                      0x008a  // Keyboard F8  0x0042  KEY_F8  3.0 0x008a
#define KEYCODE_F9                      0x008b  // Keyboard F9  0x0043  KEY_F9  3.0 0x008b
#define KEYCODE_F10                     0x008c  // Keyboard F10 0x0044  KEY_F10 3.0 0x008c  ""  ""  ""  ""  2.3 0x0052  KEYCODE_MENU
#define KEYCODE_F11                     0x008d  // Keyboard F11 0x0057  KEY_F11 3.0 0x008d
#define KEYCODE_F12                     0x008e  // Keyboard F12 0x0058  KEY_F12 3.0 0x008e
#define KEYCODE_SYSRQ                   0x0078  // Keyboard Print Screen  0x0063  KEY_SYSRQ 3.0 0x0078
#define KEYCODE_SCROLL_LOCK             0x0074  // Keyboard Scroll Lock 0x0046  KEY_SCROLLLOCK  3.0 0x0074
#define KEYCODE_BREAK                   0x0079  // Keyboard Pause 0x0077  KEY_PAUSE 3.0 0x0079
#define KEYCODE_INSERT                  0x007c  // Keyboard Insert  0x006e  KEY_INSERT  3.0 0x007c
#define KEYCODE_MOVE_HOME               0x007a  // Keyboard Home  0x0066  KEY_HOME  3.0 0x007a    ""  ""  ""  ""  1.6 0x0003  KEYCODE_HOME
#define KEYCODE_PAGE_UP                 0x005c  // Keyboard Page Up 0x0068  KEY_PAGEUP  3.0 0x005c
#define KEYCODE_FORWARD_DEL             0x0070  // Keyboard Delete Forward  0x006f  KEY_DELETE  3.0 0x0070
#define KEYCODE_MOVE_END                0x007b  // Keyboard End 0x006b  KEY_END 3.0 0x007b  ""  ""  ""  ""  1.6 0x0006  KEYCODE_ENDCALL
#define KEYCODE_PAGE_DOWN               0x005d  // Keyboard Page Down 0x006d  KEY_PAGEDOWN  3.0 0x005d
#define KEYCODE_DPAD_RIGHT              0x0016  // Keyboard Right Arrow 0x006a  KEY_RIGHT 1.6 0x0016
#define KEYCODE_DPAD_LEFT               0x0015  // Keyboard Left Arrow  0x0069  KEY_LEFT  1.6 0x0015
#define KEYCODE_DPAD_DOWN               0x0014  // Keyboard Down Arrow  0x006c  KEY_DOWN  1.6 0x0014
#define KEYCODE_DPAD_UP                 0x0013  // Keyboard Up Arrow  0x0067  KEY_UP  1.6 0x0013
#define KEYCODE_NUM_LOCK                0x008f  // Keyboard Num Lock and Clear  0x0045  KEY_NUMLOCK 3.0 0x008f
#define KEYCODE_NUMPAD_DIVIDE           0x009a  // Keypad / 0x0062  KEY_KPSLASH 3.0 0x009a
#define KEYCODE_NUMPAD_MULTIPLY         0x009b  // Keypad * 0x0037  KEY_KPASTERISK  3.0 0x009b
#define KEYCODE_NUMPAD_SUBTRACT         0x009c  // Keypad - 0x004a  KEY_KPMINUS 3.0 0x009c
#define KEYCODE_NUMPAD_ADD              0x009d  // Keypad + 0x004e  KEY_KPPLUS  3.0 0x009d
#define KEYCODE_NUMPAD_ENTER            0x00a0  // Keypad ENTER 0x0060  KEY_KPENTER 3.0 0x00a0
#define KEYCODE_NUMPAD_1                0x0091  // Keypad 1 and End 0x004f  KEY_KP1 3.0 0x0091
#define KEYCODE_NUMPAD_2                0x0092  // Keypad 2 and Down Arrow  0x0050  KEY_KP2 3.0 0x0092
#define KEYCODE_NUMPAD_3                0x0093  // Keypad 3 and PageDn  0x0051  KEY_KP3 3.0 0x0093
#define KEYCODE_NUMPAD_4                0x0094  // Keypad 4 and Left Arrow  0x004b  KEY_KP4 3.0 0x0094
#define KEYCODE_NUMPAD_5                0x0095  // Keypad 5 0x004c  KEY_KP5 3.0 0x0095
#define KEYCODE_NUMPAD_6                0x0096  // Keypad 6 and Right Arrow 0x004d  KEY_KP6 3.0 0x0096
#define KEYCODE_NUMPAD_7                0x0097  // Keypad 7 and Home  0x0047  KEY_KP7 3.0 0x0097
#define KEYCODE_NUMPAD_8                0x0098  // Keypad 8 and Up Arrow  0x0048  KEY_KP8 3.0 0x0098
#define KEYCODE_NUMPAD_9                0x0099  // Keypad 9 and Page Up 0x0049  KEY_KP9 3.0 0x0099
#define KEYCODE_NUMPAD_0                0x0090  // Keypad 0 and Insert  0x0052  KEY_KP0 3.0 0x0090
#define KEYCODE_NUMPAD_DOT              0x009e  // Keypad . and Delete  0x0053  KEY_KPDOT 3.0 0x009e
#define KEYCODE_BACKSLASH               0x0049  // Keyboard Non-US \ and |  0x0056  KEY_102ND 4.0 0x0049    1
#define KEYCODE_MENU                    0x0052  // Keyboard Application 0x007f  KEY_COMPOSE 3.0 0x0052    ""  ""  ""  ""  1.6 0x0054  KEYCODE_SEARCH
#define KEYCODE_POWER                   0x001a  // Keyboard Power 0x0074  KEY_POWER 1.6 0x001a
#define KEYCODE_NUMPAD_EQUALS           0x00a1  // Keypad = 0x0075  KEY_KPEQUAL 3.0 0x00a1
#define KEYCODE_MEDIA_STOP              0x0056  // Keyboard Stop  0x0080  KEY_STOP  3.0 0x0056
#define KEYCODE_VOLUME_MUTE             0x00a4  // Keyboard Mute  0x0071  KEY_MUTE  3.0 0x00a4
#define KEYCODE_VOLUME_UP               0x0018  // Keyboard Volume Up 0x0073  KEY_VOLUMEUP  1.6 0x0018
#define KEYCODE_VOLUME_DOWN             0x0019  // Keyboard Volume Down 0x0072  KEY_VOLUMEDOWN  1.6 0x0019
#define KEYCODE_NUMPAD_COMMA            0x009f  // Keypad Comma 0x0079  KEY_KPCOMMA 3.0 0x009f
#define KEYCODE_NUMPAD_LEFT_PAREN       0x00a2  // Keypad ( 0x00b3  KEY_KPLEFTPAREN 3.0 0x00a2
#define KEYCODE_NUMPAD_RIGHT_PAREN      0x00a3  // Keypad ) 0x00b4  KEY_KPRIGHTPAREN  3.0 0x00a3
#define KEYCODE_CTRL_LEFT               0x0071  // Keyboard Left Control  0x001d  KEY_LEFTCTRL  3.0 0x0071
#define KEYCODE_SHIFT_LEFT              0x003b  // Keyboard Left Shift  0x002a  KEY_LEFTSHIFT 1.6 0x003b
#define KEYCODE_ALT_LEFT                0x0039  // Keyboard Left Alt  0x0038  KEY_LEFTALT 1.6 0x0039
#define KEYCODE_META_LEFT               0x0075  // Keyboard Left GUI  0x007d  KEY_LEFTMETA  3.0 0x0075
#define KEYCODE_CTRL_RIGHT              0x0072  // Keyboard Right Control 0x0061  KEY_RIGHTCTRL 3.0 0x0072
#define KEYCODE_SHIFT_RIGHT             0x003c  // Keyboard Right Shift 0x0036  KEY_RIGHTSHIFT  1.6 0x003c
#define KEYCODE_ALT_RIGHT               0x003a  // Keyboard Right Alt 0x0064  KEY_RIGHTALT  1.6 0x003a
#define KEYCODE_META_RIGHT              0x0076  // Keyboard Right GUI 0x007e  KEY_RIGHTMETA 3.0 0x0076
#define KEYCODE_MEDIA_PLAY_PAUSE        0x0055  // KEY_PLAYPAUSE  3.0 0x0055
#define KEYCODE_MEDIA_STOP2             0x0056  // KEY_STOPCD 3.0 0x0056
#define KEYCODE_MEDIA_PREVIOUS          0x0058  // KEY_PREVIOUSSONG 3.0 0x0058
#define KEYCODE_MEDIA_NEXT              0x0057  // KEY_NEXTSONG 3.0 0x0057
#define KEYCODE_MEDIA_EJECT             0x0081  // KEY_EJECTCD  3.0 0x0081
#define KEYCODE_VOLUME_UP2              0x0018  // KEY_VOLUMEUP 1.6 0x0018
#define KEYCODE_VOLUME_DOWN2            0x0019  // KEY_VOLUMEDOWN 1.6 0x0019
#define KEYCODE_VOLUME_MUTE2            0x00a4  // KEY_MUTE 3.0 0x00a4
#define KEYCODE_EXPLORER                0x0040  // KEY_WWW  1.6 0x0040
#define KEYCODE_BACK                    0x0004  // KEY_BACK 1.6 0x0004
#define KEYCODE_FORWARD                 0x007d  // KEY_FORWARD  3.0 0x007d
#define KEYCODE_MEDIA_STOP              0x0056  // KEY_STOP 3.0 0x0056
#define KEYCODE_PAGE_UP                 0x005c  // KEY_SCROLLUP 3.0 0x005c
#define KEYCODE_PAGE_DOWN               0x005d  // KEY_SCROLLDOWN 3.0 0x005d
#define KEYCODE_POWER                   0x001a  // KEY_COFFEE 4.0 0x001a
#define KEYCODE_CALCULATOR              0x00d2  // KEY_CALC 4.0.3 0x00d2

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

class INPANDROIDDEVICEKEYBOARD : public INPDEVICE
{
  public:
                          INPANDROIDDEVICEKEYBOARD      ();
    virtual              ~INPANDROIDDEVICEKEYBOARD      ();

    bool                  Update                        ();

    bool                  SetScreen                     (void* screenpointer);

  private:
  
    bool                  CreateAllButtons              ();

    void                  Clean                         ();
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif








