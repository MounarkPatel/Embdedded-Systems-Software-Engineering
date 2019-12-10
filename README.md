# Embdedded-Systems-Software-Engineering
An MSP-430 was programmed with an GS2101MIP Wi-Fi module. Sending the proper IoT commands will make my RC car go Forwards, Backwards, Left and right. In other words it will make it an autonomous car that uses IoT as navigation.
# What I have done and decided to post so far
https://youtu.be/mapBG7jkuEk, in this video you will see my car getting commands and doing what the car says. Unfortunately for my car to make turns successfully I have added weight in the front of my car because friction does not just exists in physics textbooks but also real life.
The LCD display also prints the apporpriate message in accordance to the state the car is in.
https://www.youtube.com/watch?v=RpS5oOqgKR8 .
# Important files to look at to get a idea of what is going on
main.c, timers.c, timers_init.c, ports.c, macros.h, eUSCI.c and init_USCA0.c. But mainly main.c and for clarification on whats going on the rest.
# Compiler and other important information
The IAR compiler is used. (https://www.iar.com/) This is why you will see files such as .r43 and this precompiled code only works for IAR.




