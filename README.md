# MyHomeSwitch
This repo is realized IoT.

# What is this!
This is the easy IoT solution.
This solution was written Spring Boot and C.

You need two servers if your home network is in secure. And You need a Arduino(If you need, you can use some servo or relay circuit)
First to bridge internet to home network ( and you need gateway). In my case, I used Windows Azure Virtual Network and Virtual Gateway. I connected my home network to Virtual Network through VPN connection(Of course I encrypted this route).
Next, to bridge network to physical object(Arduino) I use Raspberry Pi Type B+.


# How to compile
To compile, you need IntelliJ IDEA and gcc and Arduino IDE.
First, you can see "in_Arduino" folder in this project. This folder uses Arduino IDE. You can open .ino file using Arduino IDE
and Upload to Arduino.

Next, you can see "in_DMZ_Server" in this project. To open this folder, you can use IntelliJ IDEA which is made by JetBrain.
In my case, I use community edition.

Last, you can see "in_Raspberry_Pi" in this project. You can see "serial.c" file and "IoT-Internal".
You can transfer "serial.c" to Raspberry Pi and compile it in command line like below.

```C
gcc serial.c -o serial-on

```

To open "IoT-Internal", you can use IntelliJ IDEA like "in_DMZ_Server" folder.
You can compile using IntelliJ IDEA and can output .jar file.
You can transfer output .jar file to Raspberry Pi and type command in command line like below.

```C

java -jar output.jar

```

in production...
