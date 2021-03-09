#include <a_samp>
#include <discord-connector>

// You must add these line before including dcc
#define DC_BOT_NAME         "Rouletter"
#define DC_PREFIX           "r!"

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

DC_CMD:help(DCC_User:userid, params[], DCC_Message:message) {
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

public DCC_OnCommandReceived(DCC_User:author, DCC_Channel:channel, const cmdtext[], success) {

    if (!success)
        SendDiscordMessage(channel, "Invalid command pal!");

    return 1;
}