#include <a_samp>
#include <discord-connector>

// You must add these line before including dcc
#define DCC_BOT_NAME         "Sumire"
#define DCC_PREFIX           "r!"

#include "../discord-command.inc"

new 
    DCC_Channel:g_MainChannel;

main() {
    DiscordSetup();
    print("dcc test, use your discord buddy!");
}

DiscordSetup() {
   g_MainChannel = DCC_FindChannelById("808614883897114664");
}

DC_CMD:help(DCC_User:author, params[], DCC_Channel:channel) {

    if (channel == g_MainChannel) {
        SendDiscordMessage(channel, "Hello boys and gals, i'm %s", DCC_BOT_NAME);
    } else {
        SendDiscordMessage(channel, "You are not in the right channel pal!");
    }
    printf("Success!");
    return 1;
}

DC_CMD:prefix(DCC_User:author, params[], DCC_Channel:channel) {
    if (isnull(params))
        return SendDiscordMessage(channel, "%sprefix <new prefix>", DCC_ShowPrefix());

    if (DCC_ChangePrefix(params) == -1)
        return SendDiscordMessage(channel, "Please change the max prefix length!");

    printf("Params: %s", params);

    SendDiscordMessage(channel, "Successfully changing the prefix to %s", DCC_ShowPrefix());
    return 1;
}

public DCC_OnCommandReceived(DCC_User:author, DCC_Channel:channel, const cmdtext[], success) {

    if (!success)
        SendDiscordMessage(channel, "Invalid command pal!");

    printf("%d", success);
    return 1;
}