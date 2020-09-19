#include <a_samp>
#include <sscanf2>

#include <discord-connector>

// You must add these line before including dcc
#define DC_BOT_NAME         "Rouletter"
#define DC_PREFIX           "r!"

#define DC_PREFIX_LENGTH    2

#include "../discord-command.inc"

new 
    DCC_Channel:g_MainChannel;

main() {
    DiscordSetup();
    print("dcc test, use your discord buddy!");
}

DiscordSetup() {
   g_MainChannel = DCC_FindChannelById("your_channel_id");
}

DISCORD:help(DCC_User:userid, params[], DCC_Message:message) {
    new 
        DCC_Channel:channel;
    
    DCC_GetMessageChannel(message, channel);

    if (channel == g_MainChannel) {
        SendDiscordMessage(channel, "Hello boys and gals, i'm %s", DC_BOT_NAME);
    } else {
        SendDiscordMessage(channel, "You are not in the right channel pal!");
    }
    return 1;
}

DC_CMD:kick(DCC_User:userid, params[], DCC_Message:message) {
    new 
        DCC_Channel:channel, targetid, plrName[MAX_PLAYER_NAME + 1];
    
    DCC_GetMessageChannel(message, channel);
    
    if (sscanf(params, "u", targetid))
        return SendDiscordMessage(channel, DC_PREFIX"kick <userid/name>");

    if (targetid == INVALID_PLAYER_ID)
        return SendDiscordMessage(channel, "Username/id you entered is not found on server");

    //get player name
    GetPlayerName(targetid, plrName, sizeof plrName);

    Kick(targetid);
    SendDiscordMessage(channel, "Successfully kicked %s", plrName);
    return 1;
}

public OnDiscordCommandPerformed(const params[], success, DCC_Message:message) {

    new 
        DCC_Channel:chid;

    DCC_GetMessageChannel(message, chid);

    if (!success)
        SendDiscordMessage(chid, "Invalid command pal!");

    return 1;
}