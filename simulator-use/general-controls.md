## Controls
This is the page for all the controls for using RoveSoSimulator.

This includes;
1. Overarching
2. Rover
3. Arm

Shorthands;
- temp; temporary, as to be replaced with different keys or similar
- incple; incomplete feature/functionality, as to have different behavior than is currently happening
- ntRdy; not ready, as to be a note on how it will be used in the future
- dfalt; Default, an unreal engine feature which is theorectically available
- deprc; Fully Depricated, in any remaining state. Should probably come with a date.

Controller Shorthands - Capitialized, as to tell apart from normal. 
- LX, LY, LP, RX, RY, RP; leftstick y-axis, leftstick x-axis, leftstick press. Same for right stick.
- LB, RB, LT, RT; triggers, bumpers
- WX, NY, SA, EB; xyab buttons, also north east south west for other controller reference
- DL, DR, DU, DD; d-pad left-right-up-down
- M=; menu button (three lines, on the right)
- M[]; menu button (two boxes, on the left)

*\*note. made these, then proceded to make new column purely for controllers. "Rightstick yaxis" is still kinda long though.*

Keyboard and mouse replacement symbols
- \[+\]; windows button
- \[=\]; menu button
- MX, MY, MDX, MDY, ML, MR, MSU, MSD, MSC - mouse x, mouse y, mouse change in x/y, mouse left/right, mouse scroll up/down/click
- Up Arrow, down arrow, etc; exactly what you think; the arrow keys. no <, >, v or ^ because those are also on the keyboard (especially vee)
- N1, N2, N/, N+, Nenter, N., etc; numpad versions of those keys

*\*note. as of 2/3/2026, all unused.*

Key listing method;
- minus between pieces of an axis
- Separate columns for different control methods (keyboard, controller)

### Overarching Controls
This is the page for controls that are always present no matter what the player has control over.

| Use | Key(s) | Notes |
|---|---|---|
| Possession Control (ntRdy) | 123..890 | Soon to be a specific possession choice for each one, including rover, autonomus rover, arm, in the further future drone, and nothing.|
| Arm Possession (temp) | + - | Soon to be a way to cycle through options 123...890. For now (2/3/2026), bound to arm possession.|
| Camera Cycle (incple) | \[ \] | Currently only on arm and only cycles through arm's cameras. |
| Debug Camera (Dfalt) | ; | *Chance* it won't work |
| Second debug camera? (Dfalt)| ' | Single quote |
| Terminal (Dfalt) | ` | Backtick (thing with ~ above it) |

*no controller equivelents
### Rover Controls
This is the page for controlling the rover.

| Keyboard | Controller | Use | Notes |
|---|---|---|---|
| q-a | Leftstick yaxis | Left power | q and e => forward, a-d => back |
| e-d | Rightstick yaxis | Right power | ^^^^ |
| t | | Teleop toggle | Off by default, switches between manual+arm and autonomy+autohead | 
| j | | Set Spawnpoint | Reference vvvv . Set in a fairly clear, flat area, or it may not respawn you in the exact location |
| h | | Teleport to Spawnpoint | Reference ^^^^ . Some variance in exact teleport, especially with obstructions |
| p | | Toggle Pointcloud Visibility ||
| l | | Clear path line | Its an L. ||
| f | | Flip Rover ||
| r | | Reset Rover ||
| space | | Reset/Flip Rover ||

Soon to be reorganized menus;

| Use | Key(s) | Notes |
|---|---|---|
| basestation | b | broke and fixed? today 2.3.2025. May stay as a keybind |
| multiplayer | m | nonfunctional as of at least 2.3.2026 |
| scene menu | enter | weather effects, rendering options, etc |
| level options | n ||

*currently no controller options
### Controlling the Arm
![arm diagram](../assets/images/armDiagramPieces.png) ![arm diagram with rotations](../assets/images/armDiagramRot.png)
![arm diagram](../assets/images/arm-keyboard.png)
Switching to the arm currently involves toggling teleop (T) so the rover is in manual drive, which should also reveal and activate the arm, then press - or + to take control. Pressing + or - again will swap back. Will later be switched to a specific number.
*\*Also, pressing +/- the first time you start the game doesn't trigger the swap, for some reason.*

| Movement | Key | Controller Method | Notes |
|---|---|---|---|
| x-axis/J1 | z-x | Rightstick X |
| J2 (shoulder-bicep) | shift-ctrl | Rightstick Y | 
| J3 (bicep-forarm) | w-s | Leftstick Y |
| J4 (forearm roll) | a-f | Leftstick X |
| J5 (wrist up-down) | e-d | Triggers |
| J6 (gripper roll) | q-r | Bumpers |
| Gripper Open-close| v-c | left-right dpad |c to close, v shape when open |
| Solenoid | y-t | X-Y | out-in; Pull the center line of T away from the rest to make Y | 
| Lasers | g-h | A-B| g for li***g***ht, h for hide |
| Camera Switch | \[-\] || Its \[ and \] |
