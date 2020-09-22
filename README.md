# interrupt
C51

this repository store the source file(including main function) abuot the system interruption.

# external interrupt.c
using external interrupt//EX0 = 1
while key2 is pressed(P3.2 == 0), the interruption happened.

# external+led.c
firstly, the heart beats in the led dot matrix.
If key2 is pressed, the led dot matrix turns to display the flowing character '哈', looking like "哈哈哈哈哈哈哈哈哈哈".

# timer interrupt.c
using timer0 to cause interruption.//ET0 = 1
the LED lights up for 1 second and then goes out for 1 second again and again.

# serial.c
