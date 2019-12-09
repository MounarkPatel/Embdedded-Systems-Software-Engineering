# Embdedded-Systems-Software-Engineering
An MSP-430 was programmed with an GS2101MIP Wi-Fi module. Sending the proper IoT commands will make my RC command go Forwards, Backwards, Left and right. In other words it will make it an autonomous car that uses IoT as navigation.
# What I have done and decided to post so far
https://www.youtube.com/watch?v=CkMhl6mH2F0 . As you can see I used timers, interrupts and Pulse Width Modulation to make a car move forward, reverse, counter clockwise and clockwise.
The LCD display also prints the apporpriate message in accordance to the state the car is in.
https://www.youtube.com/watch?v=RpS5oOqgKR8 .
# Important files to look at to get a idea of what is going on
macros.h, main.c, timers.c, timers_init.c and ports.c.
# Compiler and other important information
The IAR compiler is used. (https://www.iar.com/) This is why you will see files such as .r43 and this precompiled code only works for IAR.




