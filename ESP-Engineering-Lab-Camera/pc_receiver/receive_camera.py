import serial
import os

PORT = "COM4" # will need modification
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=5)

print(f"Listening on {PORT} at {BAUD} baud rate...")
print("waiting for image data...")

while True:
    line = ser.readline()
    if line.startswith(b"IMAGE_SIZE:"):
        size = int(line.split(b":")[1])

        print(f"Image size: {size} bytes")

        #Waiting for IMAGE_START
        line = ser.readline().strip()

        while line != b"IMAGE_START":
            line = ser.readline().strip()

        print("Reciving image data...")

        image_data = ser.read(size)

        if len(image_data) != size:
            print(
                f"ERROR: expected {size} bytes,"
                f"received {len(image_data)}"
            )    
            continue
        # Read IMAGE_END
        end_marker = ser.readline()

        if b"IMAGE_END" not in end_marker:
            print("WARNING: IMAGE_END not found")

        output_path = os.path.abspath("camera.jpg")
        with open(output_path, "wb") as file:
            file.write(image_data)
            print(f"Image saved to {output_path}")

        print("✅ IMAGE RECEIVED")
        print(f"Saved {len(image_data)} bytes → camera.jpg")
        print("--------------------------------")