# U-Verse Prevent Sleep

While watching television using a U-Verse set top box for extended periods of time without interacting with the remote or set top box, the device will stop playing, and enter a sort of "sleep mode" where only a photograph is shown along with the message "Press OK to watch TV".  When this occurs, the user must use the remote (or the buttons on the set top box itself) in order to resume watching television.

The arduino project in this repository periodically sends an input from the remote, which has the effect of preventing the set top box from entering this timed-out state.

Technically, this just sends a few "OK" button presses to the set top box every few seconds.  These button presses do affect the screen, so it's annoying for any humans watching  television, but I like to leave the television on for my pets and the built-in timeout prevented this from working if I was away from home for more than a few hours at a time.

This was written a long time ago; I'm honestly not even sure if it works anymore.
