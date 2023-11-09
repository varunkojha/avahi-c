## Avahi Integration and Network Connection Readme

# What is Avahi
Avahi is a system which facilitates service discovery on a local network. It's an implementation of the Zeroconf networking specifications, including a service discovery protocol known as mDNS (multicast Domain Name System) and DNS-SD (DNS-based Service Discovery). Avahi allows devices and services to automatically discover each other without needing a centralized server.

The primary purpose of Avahi is to enable devices to advertise their capabilities and services on a local network and for other devices to discover and utilize these services without manual configuration. For instance, it's commonly used for printers, file-sharing, and other networked services.

In practical terms, Avahi enables devices to assign themselves network addresses and announce their services, making it easier for users to discover and connect to these services without requiring them to configure IP addresses or know the network topology. It's widely used in Linux and other Unix-like operating systems to provide zero-configuration networking.

https://avahi.org/

# Run in SUSE Linux OpenSUSE Tumbleweed
The files were successfully installed on my system
vojha@localhost:/usr/include> cd avahi-
avahi-client/           avahi-common/           avahi-compat-libdns_sd/ avahi-core/             avahi-libevent/

I used sudo zypper install avahi-compat-libdns_sd-devel
run
gcc -o avahi_example avahi_example.c -lavahi-client -lavahi-common
./avahi_example
output
vojha@localhost:~/varun_codes/learn_C/avahi> avahi-browse -a
+ wlp0s20f3 IPv6 MyService                                     _example._tcp        local
+ wlp0s20f3 IPv4 MyService                                     _example._tcp        local
+     lo IPv4 MyService                                     _example._tcp        local
+ wlp0s20f3 IPv4 _service                                      _amzn-alexa._tcp     local
+ wlp0s20f3 IPv4 AD873EC6543AE5E9-018A3FBB7B38F5B1             _matter._tcp         local
+ wlp0s20f3 IPv4 {"nm":"R0p 00ppp0pp0pp0p0000pp00pp0","as":"[8193, 8194]","ip":" _mi-connect._udp     local
- wlp0s20f3 IPv6 MyService                                     _example._tcp        local
- wlp0s20f3 IPv4 MyService                                     _example._tcp        local
-     lo IPv4 MyService                                     _example._tcp        local

^CGot SIGINT, quitting.

# Scenario Overview:
This scenario involves the establishment of a 1-to-1 connection between mobile devices (on the 192.168.10.x network) and televisions (on the 192.168.20.x network) through a Linux server that acts as an intermediary. The goal is to allow specific mobile devices to discover and connect only to certain TVs, creating a controlled connection process between networks.

# Problem and Objective:
Avahi Disabled Scenario:

When Avahi is disabled, mobile devices on the 192.168.10.x network are unable to discover any TVs on the 192.168.20.x network.
Avahi Enabled Scenario:

Enabling Avahi allows all mobile devices to discover all TVs, leading to a scenario where mobiles can connect to any TV on the network.
Proposed Solution and Process:
Create a C/C++ Program:

The program will interface with Avahi, handling the detection and communication between mobile and TV networks.
This program identifies the source (mobile) and target (TV) IP addresses and manages mDNS queries.

# Purpose of the C/C++ Program:

When Avahi is disabled, the program will handle and manipulate mDNS queries, allowing a 1-to-1 connection.
This program ensures controlled forwarding of packets between networks, establishing specific connections between mobile devices and TVs.
Steps to Implement:

# Install and start the Avahi service.
Create the C/C++ program to handle mDNS queries and unicast responses between the mobile and TV networks.
This program will act as a proxy server, forwarding and restricting packets between the specified mobile and TV.

# Testing Procedure:

Validate the C program's functionality by sending mDNS queries from mobile devices and forwarding them to the TV network.
Test and confirm that the forwarded responses are unicast and specific to the intended mobile device.

# Desired Outcomes & Future Works:
The desired outcome is to establish controlled 1-to-1 connections between specific mobile devices and TVs without Avahi automatically forwarding mDNS packets. This will ensure a restricted and secure network connection, allowing specific mobile devices to connect only to certain TVs.

Note: It's essential to ensure that Avahi doesn't automatically forward packets unless the integration program is actively running.

This README provides an overview of the scenario, its objectives, and the proposed solution to facilitate a controlled connection between mobile devices and TVs across different networks. Adjustments and detailed implementation specifics are required based on the project's exact requirements and network configurations.

Remember to update the README with further details, instructions, and information pertinent to your specific implementation.

# Result and Outcome
I was able to run a simple service publication

Service Publication:
publishes a service named "MyService" of type "_example._tcp" on all network interfaces and protocols (IPv4 and IPv6) on port 12345. This service can be discovered on the local network.

Output:
output indicates the successful publication of the service. When the service is successfully published, the entry_group_callback function is called, and it prints: "Service 'MyService' successfully published."


# To run the C program use below as example:
gcc -o avahi_integration avahi_integration.c -lavahi-client -lavahi-common
./avahi_integration

There are .sh files to install avahi on ubuntu, stop and start the deamon services as well, which makes life easier when testing different scenarios


Output:
[Yesterday 15:22] Varun Ojha
so the progress 
 
en02 smart_tv found 
 
 
[Yesterday 15:24] Varun Ojha
$ ./avahi_integration 
Resolved service: Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa, _googlecast._tcp, local, a56831aa-ef2a-1db0-9c3f-d6b56ff217fa.local:8009
Resolved service: Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa, _googlecast._tcp, local, a56831aa-ef2a-1db0-9c3f-d6b56ff217fa.local:8009
^C

other tab 
avahi-browse -a
+   eno2 IPv6 Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa _googlecast._tcp     local
+   eno2 IPv4 Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa _googlecast._tcp     local
+   eno1 IPv4 dap2230                                       Web Site             local
-   eno2 IPv6 Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa _googlecast._tcp     local
+   eno2 IPv6 Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa _googlecast._tcp     local
-   eno2 IPv4 Smart-2K-ATV4-a56831aaef2a1db09c3fd6b56ff217fa _googlecast._tcp     local
 Client failure, exiting: Daemon connection failed

Above last message finally came when we stop avahi-deamon `sudo systemctl stop avahi-daemon`. Note that ./avahi_integration ELF file was running in other tab and nothing happened 



