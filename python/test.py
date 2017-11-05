#!/usr/bin/python

# pylint: skip-file

import socket
import struct

# Socket server definition (sends to X-Plane)
print "Opening X-Plane socket at 127.0.0.1:4900"
try:
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except:
    print "[ERROR] Couldn\'t create server (already in use?)"
    pass
    sys.exit(1)

ref = [0,0,0,0]

ref[0] = float(.50)
ref[1] = float(.50)
ref[2] = float(.50)
ref[3] = float(.50)

msg = bytearray("DATA" + struct.pack('B', 0) + struct.pack('B', 25) + struct.pack('B', 0) + struct.pack('B', 0) + struct.pack('B', 0)
    + struct.pack('f', ref[0]) + struct.pack('f', ref[1]) + struct.pack('f', ref[2]) + struct.pack('f', ref[3])
    + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0))
   # + struct.pack('B', 25) + struct.pack('B', 0) + struct.pack('B', 0) + struct.pack('B', 0)
   # + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0)
   # + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0))

while True:
    server.sendto(msg, ('127.0.0.1', 49000))

#function [header, throttle_cmd]  = fcn(throttle1, throttle2, throttle3, throttle4)

#%The header have 4 bytes plus one byte with 0

#header = typecast(uint8([uint8(68) uint8(65) uint8(84) uint8(65)]), 'singl#e');

#%To send no comand for the instances we dont need to use, it is used -999#

#No_Comand = single(-999);

#%The first group of four bytes in a selected field presents a label to identify the set of data(in this case throttle). 
#%The second group has the first instance of the data set ;
#%The third group has the second instance, etc. (Throttle1, 2, 3 and 4) 

#Throttle_header = typecast(uint8([uint8(25) uint8(0) uint8(0) uint8(0)]), 'single');
#throttle_cmd = [Throttle_header throttle1 throttle2 throttle3 throttle4 No_Comand 
# No_Comand No_Comand No_Comand Throttle_header No_Comand No_Comand No_Comand 
# No_Comand No_Comand No_Comand No_Comand No_Comand];
