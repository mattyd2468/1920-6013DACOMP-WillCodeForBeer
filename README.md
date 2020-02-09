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


#RGB light 1:

pin 10 - B1 (RED)

pin 9 - B3 (GREEN)

pin 8 - B4 (BLUE)


c1 - f1 (1k resistor)

c3 - f3 (1k resistor)

c4 - f4 (1k resistor)

h2 - row 4(+) (black wire)

i1 - i4 (RGB LED) - 1 pin is longer than the others, this is the ground pin so goes into i2

#RGB light 2:

pin 7 - B8 (RED)
pin 6 - B10 (GREEN)

pin 5 - B11 (BLUE)

c8 - f1 (1k resistor)

c10 - f3 (1k resistor)

c11 - f4 (1k resistor)

h9 - row 9(+) (black wire)

i8 - i11 (RGB LED) - 1 pin is longer than the others, this is the ground pin so goes into i9

#RGB light 3:

pin 4 - B14 (RED)

pin 3 - B16 (GREEN)

pin 2 - B17 (BLUE)

c14 - f14 (1k resistor)

c16 - f16 (1k resistor)

c17 - f17 (1k resistor)

h15 - row 15(+) (black wire)

i14 - i17 (RGB LED) - 1 pin is longer than the others, this is the ground pin so goes into i15


#POTENTIOMETER:

row 27 (+) - a27 (white wire)

PIN A0 - a28 (yellow wire)

row 30 (-) - a29 (black wire GND)

b28-d27-d29 (potentiometor)

