import serial
import time

ser = serial.Serial (port = "/dev/ttyAMA0", bytesize = 8, stopbits = 1,timeout=10)
ser.baudrate = 115200 

HexFile=open(r"My_Hex.txt", "r")
Local=HexFile.readline()

hexindex=0
FirstByteFlag=1
RecievedByteFromBluePill='N'
RecordCounter=1

NewLine=[0x00,0x00,0x00,0x01,0xFE]
EndOfRecord=[0x00,0x00,0x00,0x01,0xFD]

while(hexindex<len(Local)):
    if(Local[hexindex]==':'):
            ser.write(NewLine[0].to_bytes(1, 'big'))
            print("         BOR:",NewLine[0].to_bytes(1, 'big'))
            ser.read(1)
            ser.write(NewLine[1].to_bytes(1, 'big'))
            print("         BOR:",NewLine[1].to_bytes(1, 'big'))
            ser.read(1)
            ser.write(NewLine[2].to_bytes(1, 'big'))
            print("         BOR:",NewLine[2].to_bytes(1, 'big'))
            ser.read(1)
            ser.write(NewLine[3].to_bytes(1, 'big'))
            print("         BOR:",NewLine[3].to_bytes(1, 'big'))
            ser.read(1)
            ser.write(NewLine[4].to_bytes(1, 'big'))
            print("         BOR:",NewLine[4].to_bytes(1, 'big'))
            while(RecievedByteFromBluePill!=b'Z'):
                RecievedByteFromBluePill=ser.read(1)
            print("Record Number:",RecordCounter)
            hexindex=hexindex+1  


    elif (Local[hexindex]==' ' or Local[hexindex]=='\n'):
        ser.write(EndOfRecord[0].to_bytes(1, 'big'))
        print("         EOR:",EndOfRecord[0].to_bytes(1, 'big'))
        ser.read(1)
        ser.write(EndOfRecord[1].to_bytes(1, 'big'))
        print("         EOR:",EndOfRecord[1].to_bytes(1, 'big'))
        ser.read(1)
        ser.write(EndOfRecord[2].to_bytes(1, 'big'))
        print("         EOR:",EndOfRecord[2].to_bytes(1, 'big'))
        ser.read(1)
        ser.write(EndOfRecord[3].to_bytes(1, 'big'))
        print("         EOR:",EndOfRecord[3].to_bytes(1, 'big'))
        ser.read(1)
        ser.write(EndOfRecord[4].to_bytes(1, 'big'))
        print("         EOR:",EndOfRecord[4].to_bytes(1, 'big'))
        RecievedByteFromBluePill=ser.read(1)
        while(RecievedByteFromBluePill!=b'C'):
            RecievedByteFromBluePill=ser.read(1)
        hexindex=hexindex+1
        RecordCounter=RecordCounter+1


    elif(RecievedByteFromBluePill==b'Z'):
        valuetosend=int(Local[hexindex:hexindex+2],16)
        hexindex=hexindex+2
        ser.write(valuetosend.to_bytes(1, 'big'))
        print("     Data:",valuetosend.to_bytes(1, 'big'))
        ser.read(1)

ser.close()