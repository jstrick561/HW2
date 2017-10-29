**********************
Docker Running Pi-hole
**********************

Overview
*********

First I installed Docker in the Raspbian OS on the RaspberryPI.  To test Docker I ran a program that I had running natively in the Raspbian OS.  The program is Pi-hole.  It blocks ads on webpages via domain name.  You change the DNS server on all of your machines to the IP address of the RaspberryPI and it filters out the ads.
To get it running in Docker I found a Docker image for Pi-hole specifically for the arm processor in the raspberry pi.  To get it running you will need to open a few ports and know the ip address of the host machine.  You also need to create a folder /var/pihole and make it writeable for the Docker user.

Implementation
***************

To get it running  run the following code:

Create folder and give access::

	sudo mkdir /var/pihole
	sudo chown -R MYLINUXUSER:MYLINUXUSER /var/pihole

Download the latest image::

	docker pull diginc/pi-hole:arm

Build the container (replace xxxx with host ip)::

	docker run -d \
	--name pihole \
	-p 53:53/tcp -p 53:53/udp -p 80:80 \
	-v "${DOCKER_CONFIGS}/pihole/:/etc/pihole/" \
	-v "${DOCKER_CONFIGS}/dnsmasq.d/:/etc/dnsmasq.d/" \
	-e ServerIP="xxxx" \
	-e ServerIPv6="${IPv6}" \
	--restart=always \
	diginc/pi-hole:arm

Make sure container is created and get container number::

	docker ps -a

Start the container (replace xxxx with container number)::

	docker start xxxx

After that change the DNS server on your machines to the IP address of the Pi-hole host and most ads on your network will be blocked.  You can access pi-hole on the client machines by entering: http://pi.hole/admin. 
