#ifndef HIDTABLE_H
#define HIDTABLE_H

//http://www.freebsddiary.org/APC/usb_hid_usages

static const char hidTable[][3] =
{
"..", //0x00	Reserved (no event indicated)
"..", //0x01	Keyboard ErrorRollOver
"..", //0x02	Keyboard POSTFail
"..", //0x03	Keyboard ErrorUndefined
"aA", //0x04	Keyboard a and A
"bB", //0x05	Keyboard b and B
"cC", //0x06	Keyboard c and C
"dD", //0x07	Keyboard d and D
"eE", //0x08	Keyboard e and E
"fF", //0x09	Keyboard f and F
"gG", //0x0A	Keyboard g and G
"hH", //0x0B	Keyboard h and H
"iI", //0x0C	Keyboard i and I
"jJ", //0x0D	Keyboard j and J
"kK", //0x0E	Keyboard k and K
"lL", //0x0F	Keyboard l and L
"mM", //0x10	Keyboard m and M
"nN", //0x11	Keyboard n and N
"oO", //0x12	Keyboard o and O
"pP", //0x13	Keyboard p and P
"qQ", //0x14	Keyboard q and Q
"rR", //0x15	Keyboard r and R
"sS", //0x16	Keyboard s and S
"tT", //0x17	Keyboard t and T
"uU", //0x18	Keyboard u and U
"vV", //0x19	Keyboard v and V
"wW", //0x1A	Keyboard w and W
"xX", //0x1B	Keyboard x and X
"yY", //0x1C	Keyboard y and Y
"zZ", //0x1D	Keyboard z and Z
"1!", //0x1E	Keyboard 1 and !
"2@", //0x1F	Keyboard 2 and @
"3#", //0x20	Keyboard 3 and #
"4$", //0x21	Keyboard 4 and $
"5%", //0x22	Keyboard 5 and %
"6^", //0x23	Keyboard 6 and ^
"7&", //0x24	Keyboard 7 and &
"8*", //0x25	Keyboard 8 and *
"9(", //0x26	Keyboard 9 and (
"0)", //0x27	Keyboard 0 and )
"\r\r", //0x28	Keyboard Return (ENTER)
"..", //0x29	Keyboard ESCAPE
"\b\b", //0x2A	Keyboard DELETE (Backspace)
"\t\t", //0x2B	Keyboard Tab
"  ", //0x2C	Keyboard Spacebar
"-_", //0x2D	Keyboard - and (underscore)
"=+", //0x2E	Keyboard = and +
"[{", //0x2F	Keyboard [ and {
"]}", //0x30	Keyboard ] and }
"\\|", //0x31	Keyboard \ and |
"`~", //0x32	Keyboard Non-US # and ~
";:", //0x33	Keyboard ; and :
"'\"", //0x34	Keyboard ' and "
"..", //0x35	Keyboard Grave Accent and Tilde
",<", //0x36	Keyboard, and <
".>", //0x37	Keyboard . and >
"/?", //0x38	Keyboard / and ?
"..", //0x39	Keyboard Caps Lock
"..", //0x3A	Keyboard F1
"..", //0x3B	Keyboard F2
"..", //0x3C	Keyboard F3
"..", //0x3D	Keyboard F4
"..", //0x3E	Keyboard F5
"..", //0x3F	Keyboard F6
"..", //0x40	Keyboard F7
"..", //0x41	Keyboard F8
"..", //0x42	Keyboard F9
"..", //0x43	Keyboard F10
"..", //0x44	Keyboard F11
"..", //0x45	Keyboard F12
"..", //0x46	Keyboard PrintScreen
"..", //0x47	Keyboard Scroll Lock
"..", //0x48	Keyboard Pause
"..", //0x49	Keyboard Insert
"..", //0x4A	Keyboard Home
"..", //0x4B	Keyboard PageUp
"..", //0x4C	Keyboard Delete Forward
"..", //0x4D	Keyboard End
"..", //0x4E	Keyboard PageDown
"..", //0x4F	Keyboard RightArrow
"..", //0x50	Keyboard LeftArrow
"..", //0x51	Keyboard DownArrow
"..", //0x52	Keyboard UpArrow
"..", //0x53	Keypad Num Lock and Clear
"..", //0x54	Keypad /
"..", //0x55	Keypad *
"..", //0x56	Keypad -
"..", //0x57	Keypad +
"..", //0x58	Keypad ENTER
"..", //0x59	Keypad 1 and End
"..", //0x5A	Keypad 2 and Down Arrow
"..", //0x5B	Keypad 3 and PageDn
"..", //0x5C	Keypad 4 and Left Arrow
"..", //0x5D	Keypad 5
"..", //0x5E	Keypad 6 and Right Arrow
"..", //0x5F	Keypad 7 and Home
"..", //0x60	Keypad 8 and Up Arrow
"..", //0x61	Keypad 9 and PageUp
"..", //0x62	Keypad 0 and Insert
"..", //0x63	Keypad . and Delete
"..", //0x64	Keyboard Non-US \ and |
"..", //0x65	Keyboard Application
"..", //0x66	Keyboard Power
"..", //0x67	Keypad =
};

#endif // HIDTABLE_H

