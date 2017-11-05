#!/usr/bin/python

# pylint: skip-file

import socket
import struct
import argparse
import serial
import serial.tools.list_ports as list_ports
import sys
import csv

#from inputs import devices 
import time

# Formats hexadecimal string
def hex_format(data):
    return "".join("{:02x}".format(ord(c)) for c in data)  # [1]

# Converts from hexadecimal string to float
def hex2float(data):
    return struct.unpack('!f', data.decode('hex'))[0]

# Arguments parser
parser = argparse.ArgumentParser(description='An X-Plane HIL interface.',
                                 epilog='Developed by GEPSE@UFSM.',
                                 formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument('-a', '--address', dest='IP', default='127.0.0.1',
                    help='X-Plane IP address')
parser.add_argument('-p', '--port', dest='PORT', default=5000, type=int,
                    help='X-Plane port')
parser.add_argument('-s', '--serial', dest='SERIAL', default='auto',
                    help='communication port to write to')
parser.add_argument('-b', '--baudrate', dest='BAUD', default=9600, type=int,
                    help='communication port baudrate')
parser.add_argument('-t', '--timeout', dest='TOUT', default=None,
                    help='communication port timeout')        
parser.add_argument('-f', '--file', dest='FILE', default=argparse.SUPPRESS,
                    help='references file (see documentation for more info)')          

args = parser.parse_args()

try:
    IP = args.IP
    PORT = args.PORT
    SERIAL = args.SERIAL
    BAUD = args.BAUD
    TOUT = args.TOUT
    FILE = args.FILE
except:
    FILE = "NULL"
    pass

# Socket client definition (receives from X-Plane)
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print "Receiving from X-Plane at " + IP + ":" + str(PORT)
try:
    client.bind((IP, PORT))
except:
    print "[ERROR] Couldn\'t bind to X-Plane (already in use?)"
    pass
    sys.exit(1)

# Socket server definition (sends to X-Plane)
print "Opening X-Plane socket at " + IP + ":49000"
try:
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except:
    print "[ERROR] Couldn\'t create server (already in use?)"
    pass
    sys.exit(1)

# Serial communication
if SERIAL == 'auto':
    print "Trying to find any communication ports...",
    ports = serial.tools.list_ports.comports()
    if len(ports) == 0:
        print "Found nothing! Not using com."
        #sys.exit(3)
        SERIAL = "NULL"
    else:
        print "Found",
        if (len(ports)) > 1:
            print str(len(ports)) + " ports"
        else:
            print "a port!"
        SERIAL = ports[0].device 

if SERIAL != "NULL":
    print "Connecting to serial at " + SERIAL + ", " + str(BAUD) + " baudrate,",
    if TOUT == None:
        print "no timeout",
    else:
        TOUT = float(TOUT)
        print str(TOUT * 1000) + " ms timeout",
    try:
        serial = serial.Serial(SERIAL, BAUD, timeout=TOUT, write_timeout=1)
    except:
        print "\n[ERROR] Couldn\'t connect to serial port (not found or already in use?)"
        pass
        sys.exit(2)
    print "\nConnected to " + serial.name

# Parse references
if FILE != "NULL":
    print "Trying to get references from \'" + FILE + "\'...",
    try:
        with open(FILE) as f:
            file_ref = [line.rstrip('\n') for line in open(FILE)]
            

        parsed_ref_list = list(csv.reader(file_ref, delimiter=';'))
        #print "Got \'em."

    except:
        print "Nope, ignoring references."

first_run = True
ref =  [0,0,0,0]
throttle = [0,0,0,0]
ref_add = 0
pause = bytearray("CHAR" + struct.pack('B', 0) + struct.pack('B', 112))

print "\n" + IP + ":" + str(PORT) + " >>"

ref[0] = float(0.0)         #ref_x
ref[1] = float(0.0)         #ref_y
ref[2] = float(0.0)       #ref_z
ref[3] = float(0.0)         #ref_yaw

try:
    while True:
        data, addr = client.recvfrom(4096)  # buffer  

        #header0 = data[:4]
        #index0 = data[5:9]
        parameters0 = data[9:41]
        realt_xp = (parameters0[:4])[::-1]
        totlt_xp = (parameters0[4:8])[::-1]
        missnt_xp = (parameters0[8:12])[::-1]
        timert_xp = (parameters0[12:16])[::-1]

        #param04 = (parameters0[16:20])[::-1]
        zulut_xp = (parameters0[20:24])[::-1]
        localt_xp = (parameters0[24:28])[::-1]
        hobbst_xp = (parameters0[28:32])[::-1]
        
        #index1 = data[41:45]
        parameters1 = data[45:77]
        q_xp = (parameters1[:4])[::-1]
        p_xp = (parameters1[4:8])[::-1]
        r_xp = (parameters1[8:12])[::-1]
        #param13 = (parameters1[12:16])[::-1]
        #param14 = (parameters1[16:20])[::-1]
        #param15 = (parameters1[20:24])[::-1]
        #param16 = (parameters1[24:28])[::-1]
        #param17 = (parameters1[28:32])[::-1]        
        
        #index2 = data[77:81]
        parameters2 = data[81:113]
        pitch_xp = (parameters2[:4])[::-1]
        roll_xp = (parameters2[4:8])[::-1]
        hdingt_xp = (parameters2[8:12])[::-1]
        hdingm_xp = (parameters2[12:16])[::-1]
        #param24 = (parameters2[16:20])[::-1]
        #param25 = (parameters2[20:24])[::-1]
        #param26 = (parameters2[24:28])[::-1]
        #param27 = (parameters2[28:32])[::-1]

        #index3 = data[113:117]
        parameters3 = data[117:149]
        x_xp = (parameters3[:4])[::-1]
        y_xp = (parameters3[4:8])[::-1]
        z_xp = (parameters3[8:12])[::-1]
        vx_xp = (parameters3[12:16])[::-1]
        vy_xp = (parameters3[16:20])[::-1]
        vz_xp = (parameters3[20:24])[::-1]
        #param36 = (parameters3[24:28])[::-1]
        #param37 = (parameters3[28:32])[::-1]    

        try: 
            # If there is some file of references
            if FILE != "NULL":
                missnt = struct.unpack('>f', missnt_xp)
                mission_time = int(float(missnt[0]))    

                # Use mission time to search on the list references
                for parsed_ref in parsed_ref_list:
                    if int(parsed_ref[0]) == mission_time:
                        ref[0] = float(parsed_ref[1])           #ref_x
                        ref[1] = float(parsed_ref[2])           #ref_y
                        ref[2] = float(parsed_ref[3])           #ref_z
                        ref[3] = float(parsed_ref[4])           #ref_yaw

            else:
                ref[0] = float(0.0)         #ref_x
                ref[1] = float(0.0)         #ref_y
                ref[2] = float(-20.0)       #ref_z
                ref[3] = float(0.0)         #ref_yaw

        except:
            pass    

        packet = bytearray("$" + x_xp  + ";" + y_xp + ";" + z_xp + ";" + vx_xp + ";" + vy_xp + ";" + vz_xp + ";" + q_xp + ";" + p_xp + ";" + 
                          r_xp + ";" + pitch_xp + ";" + roll_xp + ";" + hdingt_xp + ";" + 
                          struct.pack('>f', ref[0]) + ";" + struct.pack('>f', ref[1]) + ";" + struct.pack('>f', ref[2]) + ";" + struct.pack('>f', ref[3]) + ";*")

        '''
        print ("%.4f" % struct.unpack('>f', x_xp))
        print ("%.4f" % struct.unpack('>f', y_xp))
        print ("%.4f" % struct.unpack('>f', z_xp))
        print ("%.4f" % struct.unpack('>f', vx_xp))
        print ("%.4f" % struct.unpack('>f', vy_xp))
        print ("%.4f" % struct.unpack('>f', vz_xp))
        print ("%.4f" % struct.unpack('>f', q_xp))
        print ("%.4f" % struct.unpack('>f', p_xp))
        print ("%.4f" % struct.unpack('>f', r_xp))
        print ("%.4f" % struct.unpack('>f', pitch_xp))
        print ("%.4f" % struct.unpack('>f', roll_xp))
        print ("%.4f" % struct.unpack('>f', hdingt_xp))
        print ("%.4f" % ref[0])
        print ("%.4f" % ref[1])
        print ("%.4f" % ref[2])
        print ("%.4f" % ref[3])
        print "-------------------------------------"
        '''

        if SERIAL != "NULL":
            serial.write(packet)
            #print packet

            # TODO try except
            received = serial.readline()
            print received

            #raw_input()

            try:
                received_array = received.split(';')
                throttle[0] = float(received_array[0][2:])
                throttle[1] = float(received_array[1])
                throttle[2] = float(received_array[2])
                throttle[3] = float(received_array[3][:-1])
            except:
                #print "numero bizarro"
                pass
                continue    
            
            '''
            received_array = received.split(';')
            throttle[0] = float(received_array[0][2:])
            throttle[1] = float(received_array[1])
            throttle[2] = float(received_array[2])
            throttle[3] = float(received_array[3][:-1])
            '''

        msg = bytearray("DATA" + struct.pack('b', 0) + struct.pack('B', 25) + struct.pack('B', 0) + struct.pack('B', 0) + struct.pack('B', 0)
            + struct.pack('f', throttle[0]) + struct.pack('f', throttle[1]) + struct.pack('f', throttle[2]) + struct.pack('f', throttle[3])
            + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0)
            + struct.pack('B', 25) + struct.pack('B', 0) + struct.pack('B', 0) + struct.pack('B', 0)
            + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0)
            + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0) + struct.pack('f', -999.0))


        server.sendto(msg, ('127.0.0.1', 49000))

except KeyboardInterrupt:
    print "\nUser interrupted, closing connections and exiting now."
    client.close()
    server.close()
    if SERIAL != "NULL":
        serial.close()
    pass

# [0] http://stackoverflow.com/questions/509211/explain-pythons-slice-notation
# [1] http://stackoverflow.com/questions/12214801/print-a-string-as-hex-bytes

#function [header, throttle_cmd]  = fcn(throttle1, throttle2, throttle3, throttle4)

#%The header have 4 bytes plus one byte with 0

#header = typecast(uint8([uint8(68) uint8(65) uint8(84) uint8(65)]), 'singl#e');

#%To send no comand for the instances we dont need to use, it is used -999#

#No_Comand = single(-999);

#%The first group of four bytes in a selected field presents a label to identify the set of data(in this case throttle). 
#%The second group has the first instance of the data set ;
#%The third group has the second instance, etc. (Throttle1, 2, 3 and 4) 

#Throttle_header = typecast(uint8([uint8(25) uint8(0) uint8(0) uint8(0)]), 'single');
#throttle_cmd = [Throttle_header throttle1 throttle2 throttle3 throttle4 No_Comand No_Comand No_Comand No_Comand Throttle_header No_Comand No_Comand No_Comand No_Comand No_Comand No_Comand No_Comand No_Comand];
