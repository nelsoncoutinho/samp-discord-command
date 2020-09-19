# samp-discord-command

[![sampctl](https://img.shields.io/badge/sampctl-samp--discord--command-2f2f2f.svg?style=for-the-badge)](https://github.com/Se8870/samp-discord-command)


## Installation

Simply install to your project:

```bash
sampctl package install Se8870/samp-discord-command
```

Include in your code and begin using the library:

```pawn
#include <discord-command>
```

Edit your pawn.json and add these lines:

```json
{
  "extra": {
    "discord_token": "your_discord_token"
  }
}
```

And finally, add these code to preventing your server from crashing

```pawn
public OnDiscordCommandPerformed(const params[], success, DCC_Message:message) {
    return 1;
}
```

## Usage

You can see on samp-discord-command wiki for more information about this include.

Example script:
```pawn
#include <a_samp>
#include <scanf2>
#include <discord-connector>

// configuration
#define DC_BOT_NAME         "Your bot name"
#define DC_PREFIX           "!"
#define DC_PREFIX_LENGTH    1

#include <discord-command>

DC_CMD:help(DCC_User:userid, params[], DCC_Message:message) {
    new 
        DCC_Channel:channelid;
    
    DCC_GetMessageChannel(message, channelid);
    SendDiscordMessage(channelid, "Hello, this is my bot!");
    return 1;
}

public OnDiscordCommandPerformed(const params[], success, DCC_Message:message) {
    return 1;
}
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To testing this script, first you need to change few settings such as:
* your_channel_id from examples.pwn -> to your actual channel id
* your_discord_token from pawn.json -> to your actual discord token (don't share it to ANYONE!)

then, simply run this command:
```bash
sampctl package run
```
