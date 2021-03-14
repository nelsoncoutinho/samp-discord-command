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
#endif

#if !defined DCC_PREFIX_LENGTH
	#define DCC_PREFIX_LENGTH 4
#endif

#if !defined DCC_MAX_MESSAGE
	#define DCC_MAX_MESSAGE 255
#endif 

#if DCC_PREFIX_LENGTH > 4
	#error Maximum length size is 4, you can't go above that (for now)
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

#if !defined isnull
        #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

new 
	DCC_GlobalPrefix[DCC_PREFIX_LENGTH + 1];

stock DCC_IsBot(DCC_User:user) {
	new bool:ret;
	DCC_IsUserBot(user, ret);
	printf("Bot: %d", ret);
	return ret;
}

public DCC_OnMessageCreate(DCC_Message:message) {
	new
		msg[DCC_MAX_MESSAGE];

	DCC_GetMessageContent(message, msg);

	if (strfind(msg, DCC_GlobalPrefix, true) == -1) return 0;

	new 
		DCC_User:author, DCC_Channel:channel;

	DCC_GetMessageAuthor(message, author);
	DCC_GetMessageChannel(message, channel);

	printf(msg);

	if (DCC_IsBot(author)) return 0;

	new 
		iPos = strlen(DCC_GlobalPrefix),
        ___l = ___dc@limit(),
		tmp;

	new 
		func[DCC_MAX_MESSAGE] = "dcc_";

	while((tmp = msg[iPos]) > ' ') {

		if('A' <= tmp <= 'Z' && iPos) func[iPos++ + ___l] = tmp | 0x20;
		else func[iPos++ + ___l] = tmp;
    }



	#if defined DCC_OnCommandReceived
		if (!DCC_OnCommandReceived(author, channel, func[4], (funcidx(func) != -1 ? 1 : 0))) return 1;
	#endif


	while (msg[iPos] == ' ') 
		iPos++;

	printf("Is this even printed?");
	printf(msg[iPos]);

	if(msg[iPos])
	{
		printf("this?");
		#if defined DCC_OnCommandPerformed
			return DCC_OnCommandPerformed(author, channel, func[4], CallLocalFunction(func, "isi", _:author, msg[iPos], _:channel));
		#else
			return CallLocalFunction(func, "isi", _:author, msg[iPos], _:channel);
		#endif 
	}
	else {
		printf("or this?"); 
		#if defined DCC_OnCommandPerformed
			return DCC_OnCommandPerformed(author, channel, func[4], CallLocalFunction(func, "isi", _:author, "\1", _:channel));
		#else
			return CallLocalFunction(func, "isi", _:author, "\1", _:channel);
		#endif
	}
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
	printf("%d", strlen(DCC_GlobalPrefix));
	return 1;
}

stock DCC_ShowPrefix() {
	return (DCC_GlobalPrefix);
}

// please don't change this magic number
// i know this so stupid, but this is only temp
// i'll figure it out how to solve this later
static ___dc@limit() {
    new limit = strlen(DCC_GlobalPrefix);

    switch (limit) {
        case 1: return 3;
        case 2: return 2;
        case 3: return 2;
        case 4: return 0;
    }
	return -1;
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