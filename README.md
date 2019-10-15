# Embdedded-Systems-Software-Engineering
Code to program an RC car using a MSP430 and make the car fully autonomous.
# What I have done and decided to post so far
https://www.youtube.com/watch?v=CkMhl6mH2F0 . As you can see I used timers, interrupts and Pulse Width Modulation to make a car move forward, reverse, counter clockwise and clockwise.
The LCD display also prints the apporpriate message in accordance to the state the car is in.
https://www.youtube.com/watch?v=RpS5oOqgKR8 .
# Important files to look at to get a idea of what is going on
macros.h, main.c, timers.c, timers_init.c and ports.c.
# Compiler and other important information
The IAR compiler is used. (https://www.iar.com/) This is why you will see files such as .r43 and this precompiled code only works for IAR.




