/*
	discord-command.inc
	By: Kirima

	Credits:
		- Yashas for processor logic
		- J0sh and Maddinat0r for discord-connector

	https://saweria.co/Eiikirin

*/

#if !defined dcconnector_included
	#error You must include discord-connector first.
#endif

#if !defined DCC_PREFIX
	#define DCC_PREFIX "!"
	#if !defined DCC_PREFIX_LENGTH
		#define DCC_PREFIX_LENGTH 5
	#endif
#endif

#if !defined DCC_MAX_MESSAGE
	#define DCC_MAX_MESSAGE 144
#endif 

#define DC_CMD:%0(%1) forward dcc_%0(%1); public dcc_%0(%1)
#define DCC_COMMAND:%0(%1) DC_CMD:%0(%1)
#define DISCORD_CMD:%0(%1) DC_CMD:%0(%1)  
#define DCC_Command(%0,%1,%2,%3) DC_CMD:%0(%1,%2,%3)

#if defined DCC_OnCommandReceived
	forward DCC_OnCommandReceived(DCC_User:author, DCC_Channel:channel, const cmdtext[], success);
#endif

#if defined DCC_OnCommandPerformed
	forward DCC_OnCommandPerformed(DCC_User:author, DCC_Channel:channel, const cmdtext[], success);
#endif

static 
	DCC_GlobalPrefix[DCC_PREFIX_LENGTH];

public DCC_OnMessageCreate(DCC_Message:message) {
	new
		msg[DCC_MAX_MESSAGE];

	DCC_GetMessageContent(message, msg);

	if (strfind(msg, DCC_GlobalPrefix, true) == -1) return 0;

	new 
		DCC_User:author, DCC_Channel:channel;

	DCC_GetMessageAuthor(message, author);
	DCC_GetMessageChannel(message, channel);

	new 
		iPos = (DCC_GlobalPrefix[0] == EOS) ? strlen(DCC_PREFIX) : strlen(DCC_GlobalPrefix), 
		tmp, func[33] = "dcc_";

	while((tmp = msg[iPos]) > ' ') {
		if ('A' <= tmp <= 'Z') {
			func[iPos++ + 3] = tmp | 0x20;
		}
		else {
			func[iPos++ + 3] = tmp;
		}
	}

	#if defined DCC_OnCommandReceived
		new ret = (funcidx(func) != -1) ? 1 : 0;
		if (!DCC_OnCommandReceived(author, channel, func[4], ret)) return 1;
	#endif

	if (DCC_IsBot(author)) {
		while (msg[iPos] == ' ') iPos++;

		if(msg[iPos])
		{
			#if defined DCC_OnCommandPerformed
				return DCC_OnCommandPerformed(author, channel, func[4], CallLocalFunction(func, "iis", _:author, _:channel, msg[iPos]));
			#else
				return CallLocalFunction(func, "iis", _:author, _:channel, msg[iPos]);
			#endif 
		}
		else {
			#if defined DCC_OnCommandPerformed
				return DCC_OnCommandPerformed(author, channel, func[4], CallLocalFunction(func, "iis", _:author, _:channel, "\1"));
			#else
				return CallLocalFunction(func, "iis", _:author, _:channel, "\1");
			#endif 
		}
	}
	return 0;
}

static DCC_IsBot(DCC_User:user) {
	new bool:ret;
	DCC_IsUserBot(user, ret);
	return ret;
}

// Originally by Emmet_
stock SendDiscordMessage(DCC_Channel:channel, const text[], {Float, _}:...)
{
	static
	    args,
	    str[DCC_MAX_MESSAGE],
		len = DCC_MAX_MESSAGE;

	/*
     *  Custom function that uses #emit to format variables into a string.
     *  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 2)
	{
	    DCC_SendChannelMessage(channel, text);
	}
	else
	{
		while (--args >= 2)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2 
			#emit ADD.C 12 
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C len
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

	    DCC_SendChannelMessage(channel, str);

		#emit RETN
	}
	return 1;
}

stock DCC_ChangePrefix(const prefix[]) {
	if (strlen(prefix) >= DCC_PREFIX_LENGTH) 
		return -1;

	format(DCC_GlobalPrefix, sizeof DCC_GlobalPrefix, prefix);
	return 1;
}

#if !defined FILTERSCRIPT
	public OnGameModeInit() {
		DCC_ChangePrefix(DCC_PREFIX);

		#if defined ___OnGameModeInit
			___OnGameModeInit();
		#endif 

		return 1;
	}

	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif

	#define OnGameModeInit ___OnGameModeInit

	#if defined ___OnGameModeInit
		forward ___OnGameModeInit(playerid);
	#endif
#else
	public OnFilterScriptInit() {
		DCC_ChangePrefix(DCC_PREFIX);

		#if defined ___OnFilterScriptInit
			___OnFilterScriptInit();
		#endif 

		return 1;
	}

	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif

	#define OnFilterScriptInit ___OnFilterScriptInit

	#if defined ___OnFilterScriptInit
		forward ___OnFilterScriptInit(playerid);
	#endif
#endif