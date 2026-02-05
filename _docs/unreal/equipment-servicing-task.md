---
title: Equipment Servicing
---

Under Construction.
## Overview
Switch (and Lights)

Button (and Light)

Keyboard (and display)

Drawer (and package)

PVC Pipes

Test Tubes?

USB?

Cube?

Screw?

### Switch (and Lights)
not implemented
### Button (and Light)
not implemented
### Keyboard (and display)
Keys are all instances of BP_Key. The key's physics asset has two physics bodys, between which is the only physics constraint, which gives the "spring" effect. The first physics body, bound to root, is kinematic and has 1 primative that is a box with zero extent, meaning it is effectly empty. I am fairly confident the kinematic part is necessary for the spring to function, but I am uncertain about the "zero" physics body; it may still be necessary for the root physics body to exist, however. The second physics body is on the center key bone, which has a square hitbox. Notably, this hitbox is scaled up by the key BP on construction, and attempting to scale it dynamically (e.g. while the game runs, give it new scale) will not work (though it may alter the display for the hitbox seen with alt+C). 
The Key's skeleton is set up with a center bone for the key and two outer bones for the sides. This allows the control rig to scale up the center bone, increasing the distance between it and the outer bones, expanding the length of the key. The side bones are then scaled inversely to cancel out the effect and keep the edges/bevel at the same angle as for other keys.
The Blueprint holds the rest of the logic for the keys, including the key name display, scaling on construction functionaliy, and trigger for key being pressed. The last in the list is done via an event dispatcher, which also sends some of the key's variables through. The key name display us a TextRender component that bears the character of the key or, if a second character is provided, both keys with a space between them. It also has a font size property that scales down the text to allow some of the bigger character(s)/words to fit on the keys.

The Keyboard Blueprint has ~87 keys and a display. Many of the keys are nonfunctional, such as ctrl, shift, alt, F1, F2, Page up, and print screen. Those keys all are unimplemented due to a lack of clear functionality and/or requiring multiple fingers to press. Insert, delete, down arrow, up arrow, home and end are all theorectially functional but not yet implemented (and low priority). The tab key was found to be nonfunctional due to issues with the tab character. Left arrow, right arrow, capslock, backspace and enter are all notable keys that *do* have functionality. 
The Keyboard works by getting all the key references on start and combining them into an array. They are referenced directly, which should allow for multiple keyboard instances. The keys are sorted by row, and once in a complete array, make a new array of BP_Key references. This array is then used to bind the keys' event dispatcher "OnKeyPressed" to the Keyboard's "HandleKeyPressed," which alters the screen display based on the key pressed. Notably, the alternate symbol property is not actually possible to type because doing so would require holding shift while pressing a key, which is not possible with the arm. 
The Keyboard's viewport key assets are organized by row, with an exception for the islands of the arrow keys and functionality keys directly above them. Those keys are grouped into rows that are grouped under an extra component.
Every key had its variables manually filled out. The "letter" variable controls both how the key is recongized for typing and what the key displays, so left shift and right shift *are not distingishable from each other;* giving them distingishable keycodes will currently affect the key display.  
### Drawer (and package)

### PVC Pipes
Approximated cylinders with 16 boxes per cylinder. Small Pipes are 1cm in diameter, and can be scaled up for alternate sizes. 
### Test Tubes?
not implemented
### USB?
not implemented
### Cube?
not implemented
### Screw?
not implemented
