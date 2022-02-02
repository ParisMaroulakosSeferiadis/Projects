from time import sleep
from SX127x.LoRa import *
from SX127x.board_config import BOARD
import urllib
import requests

BOARD.setup()
class LoRaRcvCont(LoRa):
    def __init__(self, verbose=False):
        super(LoRaRcvCont, self).__init__(verbose)
        self.set_mode(MODE.SLEEP)
        self.set_dio_mapping([0] * 6)
    def start(self):
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT)
        while True:
            sleep(.5)
            rssi_value = self.get_rssi_value()
            status = self.get_modem_status()
            sys.stdout.flush()         
    def on_rx_done(self):
        print ("\nReceived: ")
        self.clear_irq_flags(RxDone=1)
        payload = self.read_payload(nocheck=True)
        print (bytes(payload).decode("utf-8",'ignore'))
        data = bytes(payload).decode("utf-8",'ignore')
        print(data)
        ide= (data[2:5])
        st=int(data[5])
        sh=int(data[6])
        sl=int(data[7])
        slp=int(data[8])
        slt=int(data[9])
        su=int(data[10])
        temp = float ((data[11:(11+st)]))
        humidity = float((data[(11+st):(11+st+sh)]))
        Lux =float ((data[(11+st+sh):(11+st+sh+sl)]))
        Lpress=float((data[(11+st+sh+sl):(11+st+sh+sl+slp)]))
        Ltemp=float((data[(11+st+sh+sl+slp):(11+st+sh+sl+slp+slt)]))
        Uv=int((data[(11+st+sh+sl+slp+slt):(11+st+sh+sl+slp+slt+su)]))
        print("ID:")
        print(ide)
        print("st:")
        print(st)
        print("sh:")
        print(sh)
        print("sl:")
        print(sl)
        print("slp:")
        print(slp)
        print("slt:")
        print(slt)
        print("su:")
        print(su)
        print("Temperature:")
        print(temp)
        print("Humidity:")
        print(humidity)
        print("Lux:")
        print(Lux)
        print("LPressure:")
        print(Lpress)
        print("LTemperature:")
        print(Ltemp)
        print("UV-Index:")
        print(Uv)
        if (ide == "1.1"):
          userdata ={"temperature" : temp,"humidity": humidity,"Lux":Lux,"lps_temperature":Ltemp,"lps_pressure":Lpress,"UV-Light":Uv }
          resp = requests.post('http://localhost/data_esties.php',params=userdata)
        if (ide == "1.2"):
          userdata ={"temperature" : temp,"humidity": humidity, "Lux": Lux,"lps_temperature":Ltemp,"lps_pressure":Lpress,"UV-Light":Uv }
          resp = requests.post('http://localhost/data_athina.php',params=userdata)
        self.set_mode(MODE.SLEEP)
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT) 
lora = LoRaRcvCont(verbose=False)
lora.set_mode(MODE.STDBY)
#  Medium Range  Defaults after init are 434.0MHz, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on 13 dBm
lora.set_pa_config(pa_select=1)
try:
    lora.start()
except KeyboardInterrupt:
    sys.stdout.flush()
    print ("")
    sys.stderr.write("KeyboardInterrupt\n")
finally:
    sys.stdout.flush()
    print ("")
    lora.set_mode(MODE.SLEEP)
    BOARD.teardown()
