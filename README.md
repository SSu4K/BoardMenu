# Board Menu
A simple manu for controlling a STM microcontroller board from user terminal.

The program was created as the final task for the *Embedded Systems* course at my university. It was created for a ***KAmeleon-STM32L4*** board. It allows user to communicate with the bord via the LPUART interface and send it some commands. The commands are orgnised into intuitive sections based on the sub-device they control. It was designed to be used via a terminal application like *PuTTy* or *minicom*. Each command causes visible changes to the board or sends it's results back to the users terminal.


### Sections summary:
| Section | Description |
| - | - |
| HOME | Allows to enter each of the subsequent sections by inputing its name.|
| DIODE | Lets user control each of the 8 diodes on the board and the RGB diode (as 3 separate diodes). |
| 7SEG | Lets user display numbers on the 7 segment display. |
| JOY |  Allows user to read the state of the joystick. |
| LPUART | Provides inforamtion about the current configuration of the LPUART interface. |

### Commands summary:
Each command is case insensitive and accepts at most one argument.

| Section | Name | Use | Decription | Valid Arguments |
| - | - | - | - | - |
| *any* | HELP | help | display help for available commands | *None* |
| *any* (except HOME) | UP | up | go back to HOME section. | *None* |
| HOME | DIODE | diode | go to DIODE section. | *None* |
| HOME | 7SEG | 7seg | go to 7SEG section. | *None* |
| HOME | JOY | joy | go to JOY section. | *None* |
| HOME | LPUART | lpuart | go to LPUART section. | *None* |
| DIODE | SET | set *\<id>* | sets a diode. | digits 0..7, r, g, b |
| DIODE | RESET | reset *\<id>* | resets a diode. | digits 0..7, r, g, b |
| DIODE | TOGGLE | toggle *\<id>* | toggle a diode. | digits 0..7, r, g, b |
| DIODE | STATUS | reset *\<id>* | resets a diode. | digits 0..7, r, g, b |
| DIODE | BLINK | blink *\<id>* | start async blinking for a diode. | digits 0..7, r, g, b |
| 7SEG | DISPLAY | display *\<number>* |  shows number on the 7 segment display.| number 0..9999 |
| 7SEG | CLEAR | clear | clears the 7 segment display. | *None* |
| 7SEG | READ | read | sends the contents of display back to user. | *None* |
| JOY | READ | read *\<key>* | read if a joystick button is pressed | char L, R, U, D, C |
| LPUART | STATUS | status | read current configuartion of the interface.| *None* |

### Errors summary:
Inputting a command can cause multiple errors. Each of them is sent back to the user in a form of a informative error massege.
| Error message | Cause |
| - | - |
| *Invlaid command!* | user inputed an ivalid command |
| *Missig argument!* | user provided no too few arguments |
| *Too many arguments!* | user provided too many arguments |
| *Invalid argument!* | an argument didn't pass inner validation. |
| *Reached max command length!* | user provided a too long command. |
