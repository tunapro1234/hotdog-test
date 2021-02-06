from time import sleep
import serial

# Establish the connection on a specific port
ser = serial.Serial("COM4", 9600)
# Below 32 everything in ASCII is gibberish

while True:
    # Convert the decimal number to ASCII then send it to the Arduino
    try:
        ser.write(input(">>> ").encode())
    except KeyboardInterrupt:
        exit()

    char, final = "", ""
    while char != "\n".encode():
        final += (char := ser.read()).decode()
        # print((char := ser.read()), char == "\n".encode())
    print(final)
    sleep(.1)
