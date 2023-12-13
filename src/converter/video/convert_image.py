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

dirs = os.listdir("raw_frames")
dirs.sort()

for filename in dirs:
    im = Image.open("raw_frames\\" + filename)  

    res = [int(i) for i in filename.split() if i.isdigit()]

    im.save("raw_frames\\" + str(extract_integer(filename)) + ".jpg")