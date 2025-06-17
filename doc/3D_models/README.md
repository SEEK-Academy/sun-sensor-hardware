# 3D models

This directory serves as the central repository for managing and organizing 3D model components, and calculation sheets used in the CubeSat project. The resources provided here support the development, iteration, and documentation of the mechanical aspects of the project.

## Model Development:

This section provides a chronological record of development.

### Release 2025-06-17 SunSensor v2.1

#### Parts:
- Slit sensor face v8
- Frame cup v1

#### Notes:
The frame cup creation:

Combine the parts: `Frame Stick` and `Frame Stick Lid` into one part. Combining the parts forms a square shape without one side. This allows you to slide the `Slit Sensor Face` inside. This is to reduce the number of parts and make the whole device easier to assemble.

### Release 2025-06-09 SunSensor v2.0

#### Parts:
- Slit sensor face v8
- Frame stick v4

#### Notes:
The sensor face changes:

Remove 2 parts: `Mount Separator Top` and `Mount Separator Bottom`, making it possible to mount the electrical board directly. Increase size of the separator due to the increased distance between photoresistors directly on the eletrical board. Use 4 instead of 2 bolt holes to mount the electrical board to the wall to increase stability. Adjust spacing of the bolt holes to the raster of the standard electrical board. Add grating hole on the wall between its edges and the center point.

The frame changes:

Remove mounting points for internal platforms. For both parts, fill the empty space in the corner to increase their strength. For the `Stick Lid` part, reduce the distance separating the nut from the mounting bolt to allow the use of a 16mm long bolt. Add a diagonal stabilizer to connect two opposite walls for the nuts and connect them to the filling of the parts in the corner. This is to increase durability with narrower walls for the nuts. The size of the nut slot at the wall of the `Stick Lid` part is too small due to the accuracy of printing small parts.

Remove internal platforms to mount the electrical boards directly on the walls with separators. For all parts, change the screw size to M1.6.

### Release 2025-02-18

#### Parts:
- Slit sensor face v7
- Frame stick v3
- Internal platform v4

#### Notes:
The platform changes:

Reduced size of internal void, the electrical board fits perfectly inside. 
Changed support grid pattern on the bottom of the internal void to match the solder pattern on the bottom of the electrical board.

### Release 2025-01-22

#### Parts:
- Slit sensor face v7
- Frame stick v3
- Internal platform v3

#### Notes:
The platform changes:

Small size changes to better fit with an electrical board inside interial void.
After printing there is still a little width spacing for an electrical board.
Added a grid pattern on the bottom of the void to better hold an electronic board.
The grid is intended to be universal by being able to cut out individual grid segments.
The grid pattern does not mesh with the solder at the bottom of an electronic board.

### Release 2025-01-22

#### Parts:
- Slit sensor face v7
- Frame stick v3
- Internal platform v2

#### Notes:
The platform changes:

New internal platform is in smother shape on the borders.
The center of the platform is removed due to the central installation of an electronic board.
But the center void is too wide to hold an electronic board in place.
The stabilizers are added to stabilize an electronic board vertically and prevent of prolapse.
The stabilizers have pointed edges to cover a minimum area on the board, and they are also mounted with a screw and nut.

### Release 2024-12-28

#### Parts:
- Slit sensor face v7
- Frame stick v3
- Internal platform v1

#### Notes:
The frame changes:

A lot of material has been removed from the interior of the CubeSat. 
Platform joints in the stick part and face joints in the stick lid part are not well attached to the rest of the frame parts. 
These segments are prone to breaking, especially during post-printing processing. 
After assembly with face parts, it is well fitted and stable. 
Spacing between plafotm joints was set to 16mm, which looks enought for platforms with electronics.

### Release 2024-12-27

#### Parts:
- Slit sensor face v7
- Frame stick v2
- Internal platform v1

#### Notes:
An internal platform for mounting the electronic board has been added. 
It has been designed to fit with preview face and frame models. 
The sticks for mounting the electronic board were too long, thin and crackly, instead of being flexible in one dimension.

### Release 2024-12-22

#### Parts:
- Slit sensor face v7
- Frame stick v2

#### Notes:
The face changes:
- Decreased size up to 90x90 mm.
- Removed perpendicular hooks on the edges to simplify assembly.
- Reduced number of connecting holes.
- Moved connecting holes to the edge of the frame to allow connection with through the frame stick.
- Filled empty space between the separation part and sensor array part to eliminate curvature effect after screws installation.

The frame changes:
- Increased size and wall thickness due to smaller face area.
- Removed perpendicular joints.
- Added holes on only in one dimension.
- Added top and bottom slit for the top and bottom face corners.
- Added secound frame stick lid pard for top and bottom face connection with slit and nut installation.
 
The tolerance of the slits is enough for printing precision. 
The weight of fully assembled two faces of the CubeSat  is around 130g, and there is an possibility to reduce the weight of the frame parts.

### Release 2024-12-18

#### Prats:
- Slit sensor face v6
- Slit sensor face lid v1
- Frame stick v1

#### Notes:
The faces are too wide, so the sticks front walls are too thin. 
The face needs to be modelled a little smaller. 
The sticks need a margin error at the joint of the faces. 
The Face lid has not been printed.

### Previous releases

Testing and prototyping.
