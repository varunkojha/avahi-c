## Avahi Integration and Network Connection Readme

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

# Desired Outcomes:
The desired outcome is to establish controlled 1-to-1 connections between specific mobile devices and TVs without Avahi automatically forwarding mDNS packets. This will ensure a restricted and secure network connection, allowing specific mobile devices to connect only to certain TVs.

Note: It's essential to ensure that Avahi doesn't automatically forward packets unless the integration program is actively running.

This README provides an overview of the scenario, its objectives, and the proposed solution to facilitate a controlled connection between mobile devices and TVs across different networks. Adjustments and detailed implementation specifics are required based on the project's exact requirements and network configurations.

Remember to update the README with further details, instructions, and information pertinent to your specific implementation.

# To run the C program use below as example:
gcc -o avahi_integration avahi_integration.c -lavahi-client -lavahi-common
./avahi_integration

There are .sh files to install avahi on ubuntu, stop and start the deamon services as well.
