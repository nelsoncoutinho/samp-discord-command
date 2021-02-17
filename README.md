# samp-discord-command

[![sampctl](https://img.shields.io/badge/sampctl-samp--discord--command-2f2f2f.svg?style=for-the-badge)](https://github.com/Eiikirin/samp-discord-command)

Inspired from old source code [Inn0cent](https://forum.sa-mp.com/showthread.php?t=646843) to brand new one. Now, you can make a command any channel you want, or any user.

## Installation

Simply install to your project:

```bash
sampctl package install Eiikirin/samp-discord-command
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

## Usage

Example script:
```pawn
#include <a_samp>
#include <discord-connector>
#include <discord-command>

DC_CMD:help(DCC_User:userid, DCC_Channel:channel, params[]) 
{
    SendDiscordMessage(channelid, "Hello, this is my bot!");
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
