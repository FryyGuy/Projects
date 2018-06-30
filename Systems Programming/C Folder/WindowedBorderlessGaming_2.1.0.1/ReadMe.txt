AUTHOR: GameplayCrush http://steamcommunity.com/profiles/76561198027421333
WEBSITE: 
FORUM: http://steamcommunity.com/groups/WindowedBorderlessGaming/discussions
____________________

Update notes:

2.1.0.1
  * Added sub-menu's in tray to prevent it from getting to crowded.
  * Added mouselock compatibility with more games.
  * Window no longer gets redrawn when automatically set to borderless.
  * Window no longer gets redrawn when manually setting to borderless, you can still do this however if you hold the hotkey for a second before releasing it.
  * Added the option to NOT automatically manage borderless settings, it is not yet implemented in the options menu, to disable auto monotoring open the config file and add the line "AutoManage = never" under the first line that says "[Global_Config]"
  ________

2.1.0.0
  * Has new options menu.
  * Friendly names are now used in the options menu.
  * Option to remove title from identifier.
  * ALERT: the following mouse locking features still have compatibility issuess with a lot of games (Skyrim works)
  * Mouse locking feature: lock mouse to game window (usefull for people with multiple screens, or for game windows smaller then your sceen)
  * Mouse locking feature: lock mouse to hide (usefull for games that have double cursor issuess, or games that have no mouse support)
  * Added function to check for updates.
  * Added link to online manual
  ________

2.0.0.0
  * Created interface for the global options, to set options click "Open global options"
  * Added outlines to the tray icon for better visibillity on dark taskbars
  * Added global option to disable re-trigger hotkey
  ________

1.1.1.5
  * Fixed a issue where DXWnd would not run if the path had spaces in it.
  * Updated the forum link to the new forums.
  * Added global options that can be configured trough the config file, when upgrading from a older version please open the config file and add the following to the top: [Global_Config]
  * Added Global option: AutoSetResolution if set to always then your desktop resolution will automatically be set for the game,If it gets the resolution wrong then you can change your desired resolution using DefaultDeskTopWidth and DefaultDeskTopHeight
  * Added global option: AutoSetOffset if set to always then your desired offset will be saved for the game you are adding, you can define the offset by using DefaultPosX and DefaultPosY
  * Added global option: KeyBind1_AddWindow you can use this to change the keybind for adding a window default is 72 (F3) you can check the key codes at: http://msdn.microsoft.com/en-us/library/ms927178.aspx
  * Added global option: KeyBind1_ForceBorderless and KeyBind2_ForceBorderless you can use this to rebind the key to force a window in borderless mode. put the same values in both options to bind it to a single key or 2 diffrent values to bind it to a key-combo, default is 73 (F4) you can check the key codes at: http://msdn.microsoft.com/en-us/library/ms927178.aspx
  * Added global option: ForceKeyCheckTitle if set to never then it will not check for title when switching to borderless using the keybind.
  * Added global option: ForceTriggerCheckTitle if set to never then it will not check for title when automatically switching to borderless.
  * Added global option: AddWindow_Confirmation if set to always it will ask for confirmation if you add a window to the app, default is never.
  ________

1.1.1.4
  * Fixed an issue with F4 not working properly.
  ________

1.1.1.3
  * In addition to automatically setting your games borderless you can also trigger this action by pressing F4 while ingame.
  * Included basic version of DXWnd into the package, you can also use a advanced version by ghotik that you can find here: http://sourceforge.net/projects/dxwnd/files/Latest%20build/
  ________

1.1
  * App now needs even less memory.
  * There is now a proper settings menu, so you can edit your game settings and apply them without restarting the game. (The config file is still available for whoever wants to do it manual) Settings are launched as a separate process to not increase need for resources.
  * Config file is written more tidy to increase reading/writing actions speed for those who have a huge list of games added to it.
  * When selecting "Add window" it will time out after 15 seconds in case you chose the option by accident.
  ________