import serial

ser = serial.Serial('COM6',9600)

        
if ser.isOpen():
    
    print ("Serial is Connected. Yeh KHUPACH ^_^")

    while True:
        #datain = input()
        #print("data >> %s"%datain)
        #datain = datain.encode('ascii')
        #ser.write(datain)

        data = ser.readline()
        data = data.decode('utf-8')
        print (data)

        with open('Aedc_data.txt','w') as file: file.write(data)

        

else:
    print ("Waiting")
