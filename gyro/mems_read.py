import serial
import time

GYRO_500 = 17.50e-3
ACC_2G = {0.061/1000.0}

class IMUDriver:

    def __init__(self, port = '/dev/ttyACM0', baud=115200):
        self.__b = baud
        self.__p = port

    def open(self):
        self.__ser = serial.Serial(self.__p, self.__b, 8, "N", 1, 1000)
    

    def sample(self):
        self.__ser.write("\r")
        #legge le grandezze fisiche misurate e mette in data
        data = __ser.read(12)
        (ax, ay, az, gx, gy, gz) = struct.unpack("<hhhhhh", data)
        return (ax * ACC_2G, ay * ACC_2G, az * ACC_2G, 
                gx * GYRO_500, gy * GYRO_500, gz * GYRO_500)



if __name__ == "__main__":
    
    #apro il collegamento con la scheda
    imu_drv = IMUDriver()
    imu_drv.open()

    while True:

        package = imu_d.sample() #tupla di 6 elementi
        print(package)
        time.sleep(0.5) #500 ms


""" 
classe python che attraverso l'utilizzo di una porta seriale (UART)
va a interrogare i nostri sensori, interrogare la scheda, alla quale
restituisce tramite un pacchetto binario di 01, i dati relativi a
le accelerazioni nei tre assi e il valore delle velocità angolari
nei 3 assi. Quindi in pratica va a campionare accelerometri e giroscopi.

le costanti sopra definite servono a scalare le informazioni di
accelerazione lineare e velocità angolare sulla base della configurazione
dell'accelerometro e giroscopio stesso sulla base del fondo scala.
(, , , , ,) stiamo restituendo una tupla python

accelerazioni in g e velocità angolari in gradi al secondo ritorna
"""

"""
il carriage return \r in pratica la riga scritta sul terminale la
sovrascrive ogni volta che ne scrivi un'altra tornando all'inizio
della riga. 
"""