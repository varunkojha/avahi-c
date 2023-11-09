#! /bin/bash

sudo apt update; sudo apt install -y snapd
sudo snap install -y avahi
sudo apt update; sudo apt install -y libavahi-compat-libdnssd-dev

