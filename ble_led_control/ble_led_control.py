#!/usr/bin/env python
"""
  09/01/2015
  Author: Makerbro
  Platforms: Raspberry Pi (Raspbian)
  Language: Python
  File: ble_led_control.py
  ------------------------------------------------------------------------
  Description: 
  Sends data over BLE to control an RGB LED connecte to an RFduino.
  ------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 
  https://acrobotic.com/
  ------------------------------------------------------------------------
  License:
  Beerware License; if you find the code useful, and we happen to cross 
  paths, you're encouraged to buy us a beer. The code is distributed hoping
  that you in fact find it useful, but  without warranty of any kind.
"""
import subprocess, sys
import os
import signal
import subprocess
import threading
import tempfile
import sys
import time
import commands

MAC = "DC:E2:F4:0B:3A:03"
CHAR = 0x0011

def initialize():
    commands.getoutput('hciconfig hci0 down')
    commands.getoutput('hciconfig hci0 up')
    print commands.getoutput('hciconfig -a')
    commands.getoutput('killall hcitool')
    
def sendColor(c):
    command = 'sudo gatttool -t random -b {0} --char-write-req -a {1} -n {2}'.format(MAC, CHAR, c)
    p = subprocess.Popen(command.split(), shell=False)
    print p.communicate()[0]

if __name__ == '__main__':
    initialize()
    sendColor('FF0000')
    time.sleep(1)
    sendColor('00FF00')
    time.sleep(1)
    sendColor('0000FF')
    time.sleep(1)
    sendColor('000000')
