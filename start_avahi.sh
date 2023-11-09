#! /bin/bash

sudo systemctl enable avahi-daemon
sudo systemctl start avahi-daemon
sudo systemctl status avahi-daemon
