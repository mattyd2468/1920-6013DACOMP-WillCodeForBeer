#### embedded-systems
Coursework

Group Name: WillCodeForBeer
Members: Matt, Chris, Becky, Sean

When pulling changes from stash you will find that you will get compile errors. To fix this you need to go into the spec.d file and change the file location to your local. Also if you go into Project>Properties make sure that under C/C++ Build>Environment that any paths are correct (they will be set to Matt's laptop as he created the project so you will need to change them for your own local

##Circuit for Task B:
I have colour co-ordinated the wires for this but if you want different colours feel free
#Power:

5V -  row 1 (+) (white wire)

GRN - row1 (-) (black wire)

#RGB light:
pin 10 - B1 (RED)

pin 9 - B3 (GREEN)

pin 8 - B4 (BLUE)

c1 - f1 (1k resistor)

c3 - f3 (1k resistor)

c4 - f4 (1k resistor)

h2 - GND (black wire)

i1 - i4 (RGB LED) - 1 pin is longer than the others, this is the ground pin so goes into i2

#Potentiometer:
row 20 (+) - a20 (white wire)

PIN A0 - a21 (blue wire)

row 24 (-) - a22 (black wire GND)

b21-d20-d22 (potentiometor)

e20-f20 (orange wire)
