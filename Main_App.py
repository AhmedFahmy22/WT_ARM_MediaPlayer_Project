import subprocess
import serial
import itertools
import os
from PIL import Image
from Lib_functions import *
from png2rgb565 import *
import PIL.ImageOps

playlist_path = "./Playlist"

COM_NUM = "COM6"
config_baudrate = 230400
config_sampling_rate = 10000
pack_length = 256

## Copy & Rename files
subprocess.call('mkdir temp_folder')
subprocess.call('mkdir temp_folder/img_temp')

subprocess.call(f'cp {playlist_path}/*.mp3 ./temp_folder/')

song_max_num=0
for song_iterator in os.listdir("./temp_folder/"):
    if song_iterator.endswith(".mp3"):
        song_max_num = song_max_num + 1
        os.rename(f'./temp_folder/{song_iterator}',f'./temp_folder/s{song_max_num}.mp3')
        subprocess.call(f'eyeD3 -Q --write-images=./temp_folder/ ./temp_folder/s{song_max_num}.mp3')
        for img_iterator in os.listdir("./temp_folder/"):
            if img_iterator.endswith(".jpg"):
                image = Image.open(f'./temp_folder/{img_iterator}')
                image_resized = image.resize((128, 160))
                inverted_image = PIL.ImageOps.invert(image_resized)
                inverted_image.save(f'./temp_folder/img_temp/i{song_max_num}.jpg')
                subprocess.call(f'rm ./temp_folder/{img_iterator}')
            elif song_iterator.endswith(".png"):
                image = Image.open(f'./temp_folder/{img_iterator}')
                image_resized = image.resize((128, 160))
                inverted_image = PIL.ImageOps.invert(image_resized)
                inverted_image.save(f'./temp_folder/img_temp/i{song_max_num}.jpg')
                subprocess.call(f'rm ./temp_folder/{img_iterator}')
## Create song files
for cntr in range(song_max_num):
    subprocess.call(f'sox ./temp_folder/s{cntr+1}.mp3 -c 1 -e unsigned-integer -r {config_sampling_rate} -b 8 ./temp_folder/{cntr+1}.raw')
    img_to_565(f'./temp_folder/img_temp/i{cntr+1}.jpg', f'./temp_folder/img_temp/{cntr+1}.bin')

subprocess.call('rm ./temp_folder/*.mp3')
subprocess.call('rm ./temp_folder/img_temp/*.jpg')

## Serial Configurations
com_init = False
while True:
    if song_max_num == 0:
        print("Playlist is empty")
        break

    if COM_NUM in serial_ports():
        ser = serial.Serial(
        port=COM_NUM,
        baudrate=config_baudrate,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=10
        )
        print(COM_NUM, "opened successfully...")
        break
    elif com_init == False:
        com_init = True
        print(COM_NUM,"not found, waiting for connection...")


## Send Data
current_state = "play"
song_indx = 0

# Send Image Data

file = open(f'./temp_folder/img_temp/{song_indx+1}.bin', 'rb')
img_data = file.read()
file.close()
print("Image sending...")
img_data_final = img_data[::-1]
img_len = len(img_data_final)
pack_to_send = img_data_final[0:pack_length]
indx_cntr = 0
error_cntr = 0
ser.write(b'a')
print(ser.read(1))
while indx_cntr <= (img_len-256):
    ser.write(pack_to_send)
    indx_cntr = indx_cntr+pack_length
    pack_to_send = img_data_final[indx_cntr:(indx_cntr+pack_length)]

    response = ser.read_until(b'\n')
    print(response)
    if response == b'O\n':
        continue
    else:
        print("Image Transfer Waiting....")

while True:
    if song_max_num == 0:
        break

    song_indx = song_indx+1
    if song_indx > song_max_num:
        song_indx=1
    elif song_indx <= 0:
        song_indx = song_max_num

    # Read Data
    file = open(f'./temp_folder/{song_indx}.raw', 'rb')
    song_data = file.read()
    file.close()
    song_len = len(song_data)
    remaining_to_buffer = pack_length-(song_len%pack_length)
    arr_zero = bytes([0]*(remaining_to_buffer+pack_length))
    song_ready = song_data + arr_zero
    song_len = len(song_ready)

    print("Song started...")
    pack_to_send = song_ready[0:pack_length]
    indx_cntr = 0
    error_cntr = 0
    while indx_cntr < song_len:
        if current_state == "play":
            ser.write(pack_to_send)
            indx_cntr = indx_cntr+pack_length
            pack_to_send = song_ready[indx_cntr:(indx_cntr+pack_length)]

        response = ser.read(1)
        match response:
            case b'A':
                current_state = "pause"
            case b'B':
                current_state = "play"
            case b'C':
                current_state = "stop"
                pack_to_send = song_ready[0:pack_length]
                indx_cntr = 0
            case b'D': #next song
                current_state = "play"
                break
            case b'E': #prev song
                current_state = "play"
                song_indx = song_indx-2
                break
            case _:
                if current_state=="play" :
                    if response == b'O':
                        continue
                    else:
                        error_cntr = error_cntr +1

subprocess.call('rm -r ./temp_folder')
