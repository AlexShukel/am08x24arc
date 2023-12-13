import os
from PIL import Image 
import re

def extract_integer(s):
    # Using regular expression to find the first occurrence of an integer in the string
    match = re.search(r'\d+', s)
    
    if match:
        # Convert the matched string to an integer
        result = int(match.group())
        return result
    else:
        # If no integer is found, return an appropriate value (e.g., 0 or None)
        return None
    
def convert_to_black_and_white(input_path, output_path, threshold = 128):
    img = Image.open(input_path)
    img = img.convert('L')
    data = img.getdata()
    new_data = [(0 if pixel < threshold else 255) for pixel in data]

    new_img = Image.new('L', img.size)
    new_img.putdata(new_data)

    new_img.save(output_path)

def resize_image(input_path, output_path):
    image = Image.open(input_path)

    base_image  = Image.new( mode = "RGB", size = (32, 32), color = (255, 255, 255))

    base_image = base_image.copy()
    base_image.paste(image, (0, 4))

    base_image.save(output_path)

def getPixelData(pixelData):
    data = []

    for y in range(31, -1, -1):
        row = ""

        for x in range(16, 32):
            r = pixelData[x,y][0]

            if(r < 128):
                row += '0'
            else:
                row += '1'

        data.append(row)

        row = ""

        for x in range(0, 16):
            r = pixelData[x,y][0]

            if(r < 128):
                row += '0'
            else:
                row += '1'

        data.append(row)

    return data

def image_byte_array(input_path, output_path):
    image = Image.open(input_path)

    file = open(output_path, "w")
    file.write("v2.0 raw\n")

    pixelData = image.load()

    data = getPixelData(pixelData)

    for d in data:
        file.write('{:0{width}x}'.format(int(d,2), width=4) + " ")

    file.close()

def preprocess():
    files = os.listdir("raw_frames")
    files = sorted(files, key=extract_integer)

    for filename in files:
        im = Image.open("raw_frames\\" + filename)  

        convert_to_black_and_white("raw_frames\\" + filename, "clean_frames\\" + filename)

        resize_image("clean_frames\\" + filename, "resized_frames\\" + filename)

        image_byte_array("resized_frames\\" + filename, "text_frames\\" + os.path.splitext(filename)[0] + ".txt")

        print(filename)

def compose_big():
    data = []
    col = []

    f = 0

    files = os.listdir("raw_frames")
    files = sorted(files, key=extract_integer)

    for filename in files:
        image = Image.open("resized_frames\\" + filename)

        pixelData = image.load()

        for v in getPixelData(pixelData):
            col.append(v)

        f += 1

        if f >= 1000:
            data.append(col)
            f = 0
            col = []

    data.append(col)

    p = 0    
    for d in data:
        file = open("frames_" + str(p) + ".txt", "w")
        file.write("v2.0 raw\n")

        for v in d:
            file.write('{:0{width}x}'.format(int(v,2), width=4) + " ")

        file.close()

        p += 1

preprocess()
compose_big()
