import os
from PIL import Image
import numpy as np

def rgb_to_monochrome(image_path, output_path, array_name):
    # Load the image
    img = Image.open(image_path).convert('RGB')
    
    # Resize to 42x42 if not already
    img = img.resize((42, 42))
    
    # Pad the image to 64x64 with white (255, 255, 255) background
    padded_img = Image.new('RGB', (48, 48), color=(0, 0, 0))
    padded_img.paste(img, (2, 2))  # Center the 42x42 image in the 64x64 padded image

    # Convert image to grayscale
    gray_img = padded_img.convert('L')
    
    # Convert grayscale image to numpy array
    img_array = np.array(gray_img)
    
    # Threshold to binary (0 or 1)
    threshold = 1  # Adjust threshold as needed
    binary_img = (img_array < threshold).astype(np.uint8)  # 0 for white, 1 for black

    # Flatten binary image and pack into bytes
    flat_binary = binary_img.flatten()
    packed_bytes = np.packbits(flat_binary)  # Pack bits into bytes
    
    # Convert to the format required (unsigned char array in C++)
    with open(output_path, 'w') as f:
        f.write(f"static unsigned char {array_name}[] = {{\n")
        for i in range(0, len(packed_bytes), 6):  # 8 bytes per line
            line_data = f"0b{packed_bytes[i+5]:08b}, 0b{packed_bytes[i+4]:08b}, 0b{packed_bytes[i+3]:08b}, 0b{packed_bytes[i+2]:08b}, 0b{packed_bytes[i+1]:08b}, 0b{packed_bytes[i+0]:08b}"
            f.write(f"    {line_data},\n")
        f.write("};\n")

def process_folder(input_folder, output_folder):
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    
    for filename in os.listdir(input_folder):
        if filename.lower().endswith('.png'):
            input_path = os.path.join(input_folder, filename)
            base_name = os.path.splitext(filename)[0]
            output_filename = f"{base_name}.cpp"
            output_path = os.path.join(output_folder, output_filename)
            rgb_to_monochrome(input_path, output_path, base_name)
            print(f"Processed {filename}")

# Example usage
input_folder = 'images'
output_folder = 'images/converted'
process_folder(input_folder, output_folder)