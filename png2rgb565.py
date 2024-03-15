#!/usr/bin/python

import sys
import os

from PIL import Image
from PIL import ImageDraw
import struct


def img_to_565(img_source, img_out_name):
    isSWAP = True
    filesize = 0
    im=Image.open(img_source)

    image_height = im.size[1]
    image_width = im.size[0]

    binoutfile = open(img_out_name,"wb")

    pix = im.load()  #load pixel array
    for h in range(image_height):
        for w in range(image_width):
            R=pix[w,h][0]>>3
            G=pix[w,h][1]>>2
            B=pix[w,h][2]>>3

            rgb = (R<<11) | (G<<5) | B

            if (isSWAP == True):
                swap_string_low = rgb >> 8
                swap_string_high = (rgb & 0x00FF) << 8
                swap_string = swap_string_low | swap_string_high
                binoutfile.write(struct.pack('H', swap_string))
            else:
                binoutfile.write(struct.pack('H', rgb))

    binoutfile.close()
