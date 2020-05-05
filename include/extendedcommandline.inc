#if defined _ExtendedCommandLine_Included
 #endinput
#endif
#define _ExtendedCommandLine_Included

native int  ExtendedCommandLine_Check (char[] param, char[] buf, int bufSize);
native void ExtendedCommandLine_Remove(char[] param                         );
native void ExtendedCommandLine_Append(char[] param, char[] value           );
native int  ExtendedCommandLine_Count (                                     );
native int  ExtendedCommandLine_Find  (char[] param                         );
native void ExtendedCommandLine_Get   (int index, char[] buf, int bufSize   );

public Extension:__ext_ExtendedCommandLine = 
{
	name = "ExtendedCommandLine",
	file = "extendedcommandline.ext",
#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
#else
	autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
	required = 1,
#else
	required = 0,
#endif
};

#if !defined REQUIRE_EXTENSIONS
public __ext_ExtendedCommandLine_SetNTVOptional()
{
	MarkNativeAsOptional("ExtendedCommandLine_Check");
	MarkNativeAsOptional("ExtendedCommandLine_Remove");
	MarkNativeAsOptional("ExtendedCommandLine_Append");
	MarkNativeAsOptional("ExtendedCommandLine_Count");
	MarkNativeAsOptional("ExtendedCommandLine_Find");
	MarkNativeAsOptional("ExtendedCommandLine_Get");
}
#endif
