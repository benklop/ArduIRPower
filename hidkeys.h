/* this has been borrowed from:
 * keyPadHiduino Advanced Example Code
   by: Jim Lindblom
   date: January 5, 2012
   license: MIT license - feel free to use this code in any way
   you see fit. If you go on to use it in another project, please
   keep this license on there.
*/
#define RAW_KEY_A 0x04
#define RAW_KEY_B 0x05
#define RAW_KEY_C 0x06
#define RAW_KEY_D 0x07
#define RAW_KEY_E 0x08
#define RAW_KEY_F 0x09
#define RAW_KEY_G 0x0A
#define RAW_KEY_H 0x0B
#define RAW_KEY_I 0x0C
#define RAW_KEY_J 0x0D
#define RAW_KEY_K 0x0E
#define RAW_KEY_L 0x0F
#define RAW_KEY_M 0x10
#define RAW_KEY_N 0x11
#define RAW_KEY_O 0x12
#define RAW_KEY_P 0x13
#define RAW_KEY_Q 0x14
#define RAW_KEY_R 0x15
#define RAW_KEY_S 0x16
#define RAW_KEY_T 0x17
#define RAW_KEY_U 0x18
#define RAW_KEY_V 0x19
#define RAW_KEY_W 0x1A
#define RAW_KEY_X 0x1B
#define RAW_KEY_Y 0x1C
#define RAW_KEY_Z 0x1D
#define RAW_KEY_1 0x1E
#define RAW_KEY_2 0x1F
#define RAW_KEY_3 0x20
#define RAW_KEY_4 0x21
#define RAW_KEY_5 0x22
#define RAW_KEY_6 0x23
#define RAW_KEY_7 0x24
#define RAW_KEY_8 0x25
#define RAW_KEY_9 0x26
#define RAW_KEY_0 0x27
#define RAW_KEY_ENTER 0x28
#define RAW_KEY_ESCAPE 0x29
#define RAW_KEY_BACKSPACE 0x2A
#define RAW_KEY_TAB 0x2B
#define RAW_KEY_SPACE 0x2C
#define RAW_KEY_DASH 0x2D
#define RAW_KEY_EQUALS 0x2E
#define RAW_KEY_LEFT_BRACKET 0x2F
#define RAW_KEY_RIGHT_BRACKET 0x30
#define RAW_KEY_BACKSLASH 0x31
#define RAW_KEY_POUND 0x32
#define RAW_KEY_SEMICOLON 0x33
#define RAW_KEY_QUOTE 0x34
#define RAW_KEY_GRAVE 0x35
#define RAW_KEY_COMMA 0x36
#define RAW_KEY_PERIOD 0x37
#define RAW_KEY_SLASH 0x38
#define RAW_KEY_CAPS_LOCK 0x39
#define RAW_KEY_F1 0x3A
#define RAW_KEY_F2 0x3B
#define RAW_KEY_F3 0x3C
#define RAW_KEY_F4 0x3D
#define RAW_KEY_F5 0x3E
#define RAW_KEY_F6 0x3F
#define RAW_KEY_F7 0x40
#define RAW_KEY_F8 0x41
#define RAW_KEY_F9 0x42
#define RAW_KEY_F10 0x43
#define RAW_KEY_F11 0x44
#define RAW_KEY_F12 0x45
#define RAW_KEY_F13 0x68
#define RAW_KEY_F14 0x69
#define RAW_KEY_F15 0x6A
#define RAW_KEY_F16 0x6B
#define RAW_KEY_F17 0x6C
#define RAW_KEY_F18 0x6D
#define RAW_KEY_F19 0x6E
#define RAW_KEY_F20 0x6F
#define RAW_KEY_F21 0x70
#define RAW_KEY_F22 0x71
#define RAW_KEY_F23 0x72
#define RAW_KEY_F24 0x73
#define RAW_KEY_PRINTSCREEN 0x46
#define RAW_KEY_SCROLL_LOCK 0x47
#define RAW_KEY_PAUSE 0x48
#define RAW_KEY_INSERT 0x49
#define RAW_KEY_HOME 0x4A
#define RAW_KEY_PAGEUP 0x4B
#define RAW_KEY_DELETE 0x4C
#define RAW_KEY_END 0x4D
#define RAW_KEY_PAGEDOWN 0x4E
#define RAW_KEY_RIGHTARROW 0x4F
#define RAW_KEY_LEFTARROW 0x50
#define RAW_KEY_DOWNARROW 0x51
#define RAW_KEY_UPARROW 0x52
#define RAW_KEY_NUM_LOCK 0x53
#define RAW_KEY_KP_SLASH 0x54
#define RAW_KEY_KP_STAR 0x55
#define RAW_KEY_KP_MINUS 0x56
#define RAW_KEY_KP_PLUS 0x57
#define RAW_KEY_KP_ENTER 0x58
#define RAW_KEY_KP_1 0x59
#define RAW_KEY_KP_2 0x5A
#define RAW_KEY_KP_3 0x5B
#define RAW_KEY_KP_4 0x5C
#define RAW_KEY_KP_5 0x5D
#define RAW_KEY_KP_6 0x5E
#define RAW_KEY_KP_7 0x5F
#define RAW_KEY_KP_8 0x60
#define RAW_KEY_KP_9 0x61
#define RAW_KEY_KP_0 0x62
#define RAW_KEY_KP_PERIOD 0x63
#define RAW_KEY_KP_INTL_BACKSLASH 0x64
#define RAW_KEY_APPLICATION 0x65
#define RAW_KEY_POWER 0x66
#define RAW_KEY_KP_EQUAL 0x67


#define HID_VOLUP 0x00E9
#define HID_VOLDOWN 0x00EA
#define HID_MUTE 0x00E2
#define HID_PLAYPAUSE 0x00CD
#define HID_PLAYSKIP 0x00CE
#define HID_STOP 0x00B7
#define HID_FF 0x00B3
#define HID_REW 0x00B4
#define HID_CALC 0x0192
#define HID_MAIL 0x018A
#define HID_SCAN_NEXT_TRACK 0x00B5
#define HID_SCAN_PREV_TRACK 0x00B6
#define HID_WWW_SEARCH 0x0221
#define HID_MEDIA_PC 0x088

#define HID_BLUE 0x049
#define HID_YELLOW 0x04A
#define HID_GREEN 0x04B
#define HID_RED 0x04C

#define HID_EJECT 0x0B8
#define HID_AL_PRESENTATION 0x188
#define HID_AL_SPREADSHEET 0x186
#define HID_AL_WORD 0x184
#define HID_AL_MOVIE 0x1B8
#define HID_AL_IMAGE 0x1B6
#define HID_AL_CAPTURE 0x193
#define HID_AL_AUDIO 0x1B7
#define HID_MEDIA_TV 0x089
#define HID_MEDIA_TUNER 0x093
#define HID_MEDIA_DVD 0x08B

#define HID_HELP 0x95

enum HIDType {
  HIDMouse,
  HIDKeyboard,
  HIDConsumer,
  HIDGamepad
};

struct KeyCode {
  HIDType type;
  uint16_t code;
};

struct ConsumerData {
  uint16_t code;
  uint8_t data[5];
};

struct KeyboardData {
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
};

