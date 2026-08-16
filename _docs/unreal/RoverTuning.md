
This document aims to inform on how to tune the rovers as they change. It is *mostly without* the exact knowledge of what a rover should actually have in terms of speed and acceleration, just doing what feels functional.

### Rover Status
Rover currently expected to have max speed of about 40mph; currently working.

Actual Sim rover
+ Turns slower than desired
+ takes longer to stop than desired.

Fixing both of these while maintaining same max speed and good acceleration unclear.

\*Note; what follows was not made with exact speed knowledge.

### 1. Engine and Brakes

The rover's starting and stopping power is in the blueprint (\*friction also matters, see Wheels and Friction) under rover set up (unique to custom class RoverVehiclePawn) and Torque Control (part of arcade Control)

#### Rover Setup
The parameters work with the following code (from ARoverVehiclePawn::ApplyTorque, C++ syntax, some parts removed). Throttle is input (-1 to 1).

`torque = Clamp((MotorPower * throttle) / (0.01 + angularVelocity * FinalGearRatio), -MotorMaxTorque, MotorMaxTorque) * FinalMechanicalEfficiency * FinalGearRatio;`<br>
`SetDriveTorque(0.01 * torque * TorqueMultiplier)`<br>
`SetBrakeTorque(0.01 * BrakeForce)`<br>

\*Note that FinalGearRatio is actually effectively just a multiplier on MotorMaxTorque (found through distribution into the Clamp. Technically not true because of the 0.01 added, but thats for preventing dividing by zero)

In English, the wheels are applied MotorMaxTorque until the wheels get fast enough (angularVelocity) that the torque calculated with motor power is less than MotorMaxTorque, so the wheels get less acceleration and eventually plateau.
+ More MotorMaxTorque = more acceleration, but same max speed
+ More MotorPower or FinalGearRatio = higher max speed, but same acceleration
+ Higher FinalMechanicalEfficiency; same as TorqueMultiplier: final multipler for torque, increases acceleration.

In total, change MotorPower to change max speed, MotorMaxTorque and FinalGearRatio to increase acceleration limit, and FinalMechanicalEfficiency or TorqueMultiplier for both.<br>

\*There is a restriction on the ratio of motor power to max motor torque; too little of the former/too much of the latter makes turning pulse. Solution is to test different amounts, and use debug statements to figure out if you reach max motor torque in a single frame and then motor power can't maintain it.<br>

BrakeForce is the torque applied to slow the wheels down. It might affect the rover when it is speeding up too.<br>
We absolutely need a brake button.

#### Torque Control

Torque Control is a weird built in system, part of Arcade Control. It may be evil. 

Three parameters matter/are used;
+ Yaw Torque Scaling - Unclear effect 
+ Yaw From Steering - Unclear effect
+ Rotation Dampening - Higher = Slower turn

\*Yaw is rotation about the vertical axis, so you end up turned left or right.

### 2. Wheels and Resistance

For wheel position and weight, see Weight and Balance.

If you understand how the forces work to make a car move, you will know that friction is what actually moves the car forward. To be specific, the friction force, calcuated with the coefficient of friction times the normal force, which is effectively mass\*gravity, is the *maximum* force the wheels can excerate before the car starts slipping. <br>
<br>
In short, increase Friction Force Multipler if the wheels are slipping; this shouldn't need to be adjusted often.<br>
Wheels may be slipping if the wheels are going faster but the rover is not. Also consider weight as a potential problem source. <br>
<br>
For Rotation Damping, see Engine and Brakes -> Torque Control (this page) <br>
For drag, see Weight and Balance -> Blueprint (also this page) <br>

### 3. Weight and Balance

This is mainly about weight distribution, as it is highly prefered the rover has a realistic weight, as long as the rover can be effectively driven.

The rover has two main places that should affect the weight: the Physics Asset and the main blueprint. <br>
The Physics Asset contains...
+ the main body
+ six wheels
+ possibly more pieces for the main body (the connections to the wheels)

The Physics Asset should have an equal distribution of weight across the (left-right) center of the rover. This means things with a twin (wheels, say the front right wheel) should match their twin in position (reflected of course), weight, size, etc. Things without a twin (i.e. the main body) should be centered along the left-right axis.<br>
<br>

The Blueprint contains...
+ The Vehicle Setup (Part of movement component)
  + the weight field (different from the sum of weight in the Physics body, but the value shouldn't be much different, if at all)
  + center of mass override, which can be used to prevent wheelies better
  + Drag coefficient (and area parameters used to calculate drag)
+ other assets that should weigh the rover down (signal stack, autohead, and arm{?})
+ assets that should *not* weight the rover down (LED panel, which does not exist on the real rover)

For current iteration (6/25/26), the physics body of Athena got the wheel-connection-hitboxes removed, as they were found to cause issues even with extremely negligable mass and gravity turned off. They were also effectively static.

### Problems and Solutions

Doing a wheelie? Decrease torque. <br>
Max speed to high/low? Change motor power. That doesn't work? Try increasing wheel friction. (friction limits max speed)<br> 
Getting to max speed too fast/slow? Change motor torque.<br> 
Turning too slow/fast? Change Rotation damping <br>
Vehicle randomly turns when going straight? Check balance. (see balance) Can't find the issue? Same. <br>
Rover too quick/slow to slow down? Brakeforce and/or Drag.
**Turning is pulsing?** Decrease max torque and/or increase motor power. At rest, angular velocity is so low that the equation goes straight to max motor torque, which can increase angular velocity so much that the torque can't maintain it for the next tick. Increase motor power to maintain the high, decrease max torque to lower the power needed for stability.  

### Notes

In the file WheelSystem.h, in the class FSimpleWheelSim, the variable ExternalDriveTorque is stated in a comment to have a unit of N.m, or Newton meters, which is the normal torque unit. It is otherwise used in another variable where it is explicitly stated in a comment that it is one of the few places where meters must be used, and cm will not work. Despite this... <br>
...in the file ChaosWheeledVehicleMovementComponent.cpp, in the function UChaosWheeledVehicleMovementComponent::SetDriveTorque, using other (reviewed) functions, an input of Torque converted from meters to cm, and then ExternalDriveTorque is set as that value. In summary, Unreal is not good with their units. 
<br>
<br>
In my experience, GAIs (at least Microsoft Copilot) are extremely bad with ChaosVehicles. Feel free to taken their input, as they can get some things right, but take it with a mountain of salt.

### Misc Notes From Active Development While Writing
Lowered Rover weight by about 90% to get it to realistic level

With weight lowered, "stabilize control" (from arcade control, part of movement component) needed to be disabled, as it was dramatically slowing falling.

Previously, Substepping (World Settings -> Physics) was disabled, which made the arm unable to pick things up. Enabling substepping fixed that issue, but also made Athena functional--- it previously had a collision issue causing it to fall slowly while rocking left and right very quickly. This fix worked for Athena, but Talos appeared to be unchanged.<br>
However, with further testing, it seemed both Athena and Talos had become "untuned" (different speed-- forward, backward, turning). This was made worse by the weight reduction.

