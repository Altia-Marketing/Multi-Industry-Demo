# Multi-Industry-Demo

## 1.	Required Hardware:
-	MCIMX8ULP-EVK (tested with SCH-76883 REV B3)
-	RK055HDMIPI4M (for RK055HDMIPI4M0 a different device tree file can be used)

## 2.	Hardware setup:
Connect the display to the board.
Follow NXP out of the box instructions link. [https://www.nxp.com/document/guide/getting-started-with-the-i-mx-8ulp-evk:GS-I.MX-8ULP-EVK?section=out-of-the-box&subSection=out-of-the-box-5#out-of-the-box-5]

## 3.	Program the board’s eMMC:
Follow the NXP instructions to program the board with BSP 6.1.22_2.0.0:
https://www.nxp.com/document/guide/getting-started-with-the-i-mx-8ulp-evk:GS-I.MX-8ULP-EVK?section=embedded-linuxsupregsup

Below is a summary of the steps executed, use the link above for detailed instructions:
-	Download a 6.1.22_2.0.0 8ULP EVK binary from here. [https://www.nxp.com/design/software/embedded-software/i-mx-software/embedded-linux-for-i-mx-applications-processors:IMXLINUX]
-	Power on the board on Serial Download SW5 01xxxxxx
-	Run uuu on your host (Windows or Linux): uuu `zip file`
-	(Optional) You can open a serial terminal to follow the programming progress.
-	Change SW5 to Single Boot-eMMC 1000xx00
-	Cycle power the board.
-	Linux BSP 6.1.22_2.2.0 will boot up.

## 4.	Change the Device Tree:
-	Connect the Debug cable (J17) to your computer, see NXP out of the box instructions for more information. 
-	Configure your favorite terminal program to  115200 8N1, no hw/sw flow control.
-	Cycle power the board and during the countdown hit any key to stop at the U-Boot prompt.
-	Edit the “fdtfile” variable. For RK055HDMIPI4M use imx8ulp-evk-rk055hdmipi4m.dtb, or for  RK055HDMIPI4M0 use imx8ulp-evk-rk055hdmipi4mv2.dtb.
-	Save the updated environment variable and boot.
-	Linux will boot and the display will show the Weston desktop.

## 5.	Stop Weston:
This version of the Altia Demo runs directly on the DRM device, please contact Altia if you are interested in a Weston version.
On the board debug terminal:  
>	`root@imx8ulpevk:~# systemctl stop Weston`

(Optional) If you are interested in having this demonstration on “autorun” you can disable Weston so it does not start on boot:  

>	`root@imx8ulpevk:~# systemctl disable Weston`  
>	`root@imx8ulpevk:~# systemctl daemon-reload`  

## 6.	Copy Demo files to the board:
This step can be accomplished in different ways, the goal is to copy the files from the 8ULP_binaries.zip to the board. Link to be added.
A USB flash stick can be used, to copy the files to it, plug it on the board and copy them to “home/root/” on the board.

Or a network connection can be used, here are steps manually configuring the IP addresses:
-	Connect a network cable from the board ethernet port to a router or directly to the host.
-	If using a router (DHCP server) skip the steps to assign the IP address.
-	Assuming the host is manually configured with:  
>	IPv4 Address. . . . . . . . . . . : 192.168.100.1

-	Configure the board to use 192.168.100.2:  
>	`root@imx8ulpevk:~# ip a add 192.168.100.2/24 dev eth0`  
>	`root@imx8ulpevk:~# ip link set dev eth0 down`  
>	`root@imx8ulpevk:~# ip link set dev eth0 up`  
 
-	Ping the host to test the connection.  
 
-	Now, use scp to copy the files to the board, if the host is running Windows, WinSCP can be used.  

Linux:
-	Navigate to the folder where the files are saved.
>	`scp ByteSizedDemo root@192.168.100.2://home/root/`  
>	`scp -r reflash/ root@192.168.100.2://home/root/`  

Windows:
-	Install WinSCP (or another windows scp application)
-	Establish a connection with the board.
-	Login
-	Drag and drop the “reflash” folder and the “ByteSizedDemo” to /home/root/ on the board.
 
On the board:
-	Confirm the files were properly copied (ls -lha) and use the sync command.

## 7.	Run the demo:

Once the files are copied and Weston is stopped, you can start the demo.
Depending on the method used for copying the files, executable permission might need to be set:  
> `root@imx8ulpevk:~# chmod +x ByteSizedDemo`  

Run:
>	`root@imx8ulpevk:~# ./ByteSizedDemo`  

The demo should start like on this video: https://altia.box.com/s/obix66l83upmsvn0dcyj2tel7ldg13n9
You can touch on the center of the display to change the main screen or on the Altia logo on top, or bottom for other animations.

## 8.	(Optional) Autorun the demo
The board can be configured to automatically start the demo after boot. 
-	Disable Weston as described on chapter #5.  
-	Create altia.service on the board:  
  o	Using the instructions from chapter #6, copy the “altia.service” file to “/lib/systemd/system/” on the board root file system. 

Alternatively, the file can be manually created:   

  o create the file with vi `root@imx8ulpevk:~# vi /lib/systemd/system/altia.service`:  
  o Press “I” to go to Insert mode  
  o Copy and paste the altia.service contains to the editor  
  o Press `ESC` and type `:wq` – to exit insert mode, save changes and quit vi.  
  o altia.service content:  
```
[Unit]
Description=altia

[Service]
ExecStartPre=/bin/sleep 10
WorkingDirectory=/home/root/
ExecStart=/home/root/ByteSizedDemo
Restart=always
RestartSec=10

StandardOutput=syslog
StandardError=syslog

[Install]
WantedBy=multi-user.target
```

-	Note that a 10 second delay is added to wait for the touchscreen to be available when the application is launched.

-	Once altia.service is properly copied, the demo can start/stop with:  
`root@imx8ulpevk:~# systemctl start altia`  
#Wait for the 10 seconds delay for the demo to start    
`root@imx8ulpevk:~# systemctl stop altia`  

-	To autostart the demo:  
`root@imx8ulpevk:~# systemctl enable altia`  
`root@imx8ulpevk:~# systemctl daemon-reload`  
`root@imx8ulpevk:~# reboot`  

-	After the system reboots the altia demo should automatically start after the 10 seconds delay.
