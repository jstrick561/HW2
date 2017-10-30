********************
Raspberry Pi Project
********************

.. contents::

Introduction
************

The sound of the motors burst the quiet room. The wheels begin spinning and off goes our Zumo Robot. It's alive!! Our first attempt at creating a use for the Raspberry Pi is a success. Many hours of hard work by **Alan Mangold**, **Robert Reza** and **Jerry Strickland** of team ``Alpha`` has come to fruition.

Contemplating what we could do with a Raspberry Pi left us baffled. We did not want to just make the Pi run a program (anyone can do that). We wanted it to do something (like move, speak or shoot aliens) and above all have fun. So we started looking on Google for projects that would do just that.  We searched and searched and found robots. Now, that's a possibility!  We examined several and decided that with the time constraints (and money constraints) we would create a Zumo Robot, but just moving was not enough, we had to go farther. So we would add a distance sensor module to make sure it didn't run into walls and program it to dance. So our adventure begins.


Board History
*************

We began by examining the history of the Raspberry Pi. The Raspberry Pi was created in Febuary 2012 by the Raspberry Pi Foundation, Originally setup to promote and teach basic computer science in schools and colleges around the UK. They initially released 2 Devices the Model A and the Model B, these computers ranged in specifications and cabilities. Soon after the release of these products a community was formed and thousands of “Tech-Heads” bought one and started to create new projects with it, for instance one project was to setup a Home Media Centre and play the popular game Minecraft.

The products were so popular due to their low cost (ranging from $25 – $35), their efficiency and durability. This made them easy to modify and create projects.  The device ran Linux, a popular open-source OS for developers.

On the Raspberry Pi website they created 2 images that could be installed easily onto a sd card which would then act as the OS for the device. One of the images was based off of Debian a popular lightweight Linux OS and was called Raspbian, and the other was called Raspbmc and was based off the popular media centre software Kodi (Formally known as XBMC).

In Feburary 2014 they had been reported to have sold 4.5 millions boards, soon after this success they released the Model A+ and Model B+ which provided more GPIO’s and used less power to run. In early 2015 the Raspberry Pi 2 was announced with increased Mhz by 200 to bring it to 900Mhz and doubled the ram to make it 1GB. In early 2016 the Raspberry Pi 3 was released with again increased Mhz (now 1.2 Ghz), on-board WiFi and on-board Bluetooth.

The official Raspberry Pi magazine announced in March of 2017 that over 12.5 million of the affordable little Linux boards have been sold since the original Pi was launched in 2012.


Basic Board Setup
*****************

Next, we looked at the configuration of the Raspberry Pi. The Raspberry Pi 3 Model B builds upon the features of its predecessors with a new, faster processor on board to increase its speed. It also features WiFi and Bluetooth Low Energy capabilities to enhance the functionality and the ability to power more powerful devices over the USB ports.

The specificatons include:

- Quad Core 1.2GHz Broadcom BCM2837 64bit CPU
- 1GB RAM
- BCM43438 WiFi and Bluetooth Low Energy (BLE) on board
- 40-pin Extended GPIO
- 4x USB 2 ports
- 4 Pole stereo output and composite video port
- Full size HDMI
- CSI camera port for connecting a Raspberry Pi camera
- DSI display port for connecting a Raspberry Pi touchscreen display
- Micro SD port for loading your operating system and storing data
- Upgraded switched Micro USB power source up to 2.5A


Processor Architecture
**********************

Digging deeper we delved into what made the Raspberry Pi work. The BCM2837 is the Broadcom chip used in the Raspberry Pi 3, and in later models of the Raspberry Pi 2. The underlying architecture of the BCM2837 is identical to the BCM2836. The only significant difference is the replacement of the ARMv7 quad core cluster with a quad-core ARM Cortex A53 (ARMv8) cluster.

The quad-core ARM Cortex A53 (ARMv8) cluster run at 1.2GHz, making the device about 50% faster than the Raspberry Pi 2. The VideocoreIV runs at 400Mhz

.. image:: Cortex-A53-large_678x452.png

The Cortex-A53 processor has one to four cores, each with an L1 memory system and a single shared L2 cache. 

The Architecture is Armv8-A. It has a Multicore with 1-4x Symmetrical Multiprocessing (SMP) within a single processor cluster, and multiple coherent SMP processor clusters through AMBA 4 technology. It has ISA Support which includes AArch32 for full backward compatibility with Armv7, AArch64 for 64-bit support and new architectural features, TrustZone security technology, NEON advanced SIMD, VFPv4 floating point (FPU) and Hardware virtualization support. The Cortex-A53 can be implemented in two execution states: AArch32 and AArch64. The AArch64 state gives the Cortex-A53 its ability to execute 64-bit applications, while the AArch32 state allows the processor to execute existing Armv7-A applications.

Some of the key features are in-order, 8-stage, dual-issue pipeline, lower power consumption, extensive dual-issue capability, increased peak instruction throughput via dual instruction decode and execution, advanced branch predictor, increased branch hit rate with 6Kb Conditional Predictor and 256 entry indirect predictor, extensive power-saving features and hierarchical clock gating, power domains, advanced retention modes.

The Cortex-A53 processor delivers significantly more performance than its predecessors at a higher level of power efficiency. This takes the performance of the core above that of the Cortex-A7 processor, which defines many popular mainstream and entry-level mobile platforms. 

These include 64-bit data processing, extended virtual addressing and a 64-bit general purpose registers. The Cortex-A53 processor is Arm’s first Armv8-A processor aimed at providing power-efficient 64-bit processing.

More information can be found at https://developer.arm.com/products/processors/cortex-a/cortex-a53.


Processor Assembly Language
***************************

We also discovered that the ARM Cortex-A53's microarchitecture is implementing the ARMv8-A 64-bit instruction set designed by ARM Holdings.


Performance
***********

The Raspberry Pi has different performance and power saving modes for the cpu.
  
- Conservative: Smoothly change cpu frequency depending on cpu load
- Performance: Always use max cpu frequency
- Powersave: Always use min cpu frequency
- On demand: Change cpu frequency depending on cpu load, min or max.
- Userspace: Allow user space daemon to control cpu frequency

These can be changed with the following line::

echo "performance" |sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor


Overclocking
************

The Raspberry Pi 3's stock frequency is 1.2Ghz, but if more speed is needed the cpu can be overclocked.  The max speed you will be able to get out of your chip is dependent on the chip itself and the cooling you have installed on the arm cpu.  There are aftermarket aluminum heat sinks that can be applied to the cpu with thermal tape to help dissipate the additional heat brought on from the higher clock speed.  Other more extreme heat sinks are available as well.

To change the arm cpu clock speed bring up the /boot/config.txt file as follows::

sudo nano /boot/config.txt

The arm_freq field is the arm cpu clock frequency.  You will see that the stock frequency is set to 1200. 

In testing I was able to get my personal RaspberryPi 3 to 1250mhz. ::

	pi@raspberrypi:~ $ sudo cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
	1250000

When I tried for 1300mhz the machine would not boot.  In a no boot situation you remove the sd card, insert it in a personal computer and navigate to the config.txt file. When you open the file change the arm_freq back to a working frequency and reinstall it back into the Raspberry Pi.


Developement Tools
******************

It was now time to evaluate what software and hardware was needed to build our robot. We would need and OS, a way to create our program, a way to write our documentation, a way to communicate with Github to perserve our programs and documentation and as the project requires, Docker. The software loaded on the Raspberry Pi is as follows:

- NOOBS Raspbian (Jessie) (which included Python)
- build-essential
- Vim-gtk
- Git-core
- Docker

To build our Zumo Robot, we needed a flame thrower, grenade launcher and a space alien ... no, no, no, what was I thinking? We needed the following parts:

- Raspberry Pi 3
- Zumo Chassis Kit
- JUHANG minikey1456 2.4Ghz Wireless Mini Keyboard with Backlit Remote Control Touchpad Android TV Box Tablet HTPC Laptop 
- Jackery Mini 3200mAh Portable Battery Charger Power Bank
- L298N Motor Drive Controller Board
- 2x 6V 1400RPM Micro Speed Reduction Motor Mini Gear Box Motor
- HC-SR04 Ultrasonic Distance Sensor Module
- Mini Rocker Switch
- Breadboard and Capacitors for Distance Sensor
- Assorted Wires, Wood, Glue, Screws, Spacers, etc. to build the robot platform


Demonstration Project
*********************

The building began: format sd drive; load raspbian noob image; boot sd disk in raspberry pi loading Raspbian Jessie OS; run update; load build-essential; load git-core; load vim-gtk; run update again; run upgrade; change raspberry configuration for keyboard and language (US not UK); load docker; cut; cut; solder; bang; screw; curse; solder again; bang; screw; curse some more; drill; bang; screw; and POOF!! **The Zumo Robot**.

Oh no, now what! Oh, the program: program; program; test; program; test; start over; program; test; program; and POOF again!! The Zumo Robot moves. We completed our creation (as if you ever complete a robot).

As a quick recap, we got a Raspberry Pi and sd card. Loaded the sd card with software. Purchased a Zumo chassis, couple of small motors and a controller board to spin and control the wheels. Purchased a wireless keyboard and power bank to run the Raspberry Pi. Added a Distance Sensor to the mix. Put it all together. Programmed it up and POOF!! The Zumo Robot.

More information can be found at https://www.youtube.com/watch?v=AZSiqj0NZgU and http://www.modmypi.com/blog/hc-sr04-ultrasonic-range-sensor-on-the-raspberry-pi and https://www.youtube.com/watch?v=iNXfADw0M9Y.
