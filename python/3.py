from math import sqrt
from math import ceil
from PIL import Image
from random import randint


def decode(im):
    width, height = im.size
    lst = []
    for y in range(height):
        for x in range(width):
            red, green, blue = im.getpixel((x, y))
            if (blue | green | red) == 0:
                break

            index = (green << 8) + blue
            lst.append(chr(index))

    return ''.join(lst)


def d(filename: str):
    all_text = decode(Image.open(filename))
    with open("{}_decode.txt".format('.'.join(filename.split('.')[:-1])), "w", encoding="utf-8") as f:
        f.write(all_text)


def encode(text):
    width = ceil(sqrt(len(text)))
    im = Image.new("RGB", (width, width), 0x0)
    x, y = 0, 0
    for i in text:
        index = ord(i)
        rgb = (randint(0, 255),  (index & 0xFF00) >> 8,  index & 0xFF)
        im.putpixel((x, y),  rgb)
        if x == width - 1:
            x = 0
            y += 1
        else:
            x += 1
    return im


def e(filename: str):
    with open(filename, encoding="utf-8") as f:
        all_text = f.read()

    im = encode(all_text)
    im.save("{}_layout.bmp".format('.'.join(filename.split('.')[:-1])))


e('s.txt')
# (index & 0xFF0000) >> 16
