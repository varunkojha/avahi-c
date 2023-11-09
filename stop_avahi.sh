#! /bin/bash

sudo systemctl disable avahi-daemon.socket
sudo systemctl disable avahi-daemon
sudo systemctl stop avahi-daemon.socket
sudo systemctl stop avahi-daemon
sudo systemctl status avahi-daemon
