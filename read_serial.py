import serial
import time
import csv

ser = serial.Serial('COM3', 115200)
print("Serial port opened:", ser.name)
time.sleep(2)

data_stream_start = False

while True:
		time.sleep(1/1000) # 1 ms delay to avoid terminal freezing

		incoming_data = ser.readline()
		if not incoming_data:
			continue
		else:
			print("Received data:", incoming_data)
			line = incoming_data.hex()
			print(line)
			if line.startswith('7374617274'):  # 'start' in hex
				data_stream_start = True
				print("Data stream started")
			elif line.startswith('73746f70'):  # 'stop' in hex
				data_stream_start = False
				print("Data stream stopped")
			elif data_stream_start:
				with open('data_log.csv', 'a', newline='') as csvfile:
					csv_writer = csv.writer(csvfile)
					csv_writer.writerow([line])
