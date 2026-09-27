import serial

PORT = "COM4"
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
        line = ser.readline()

        if line.strip() == b"IMAGE_START":
            print("ERROR img not found")
            continue

        print("REciving image data...")

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

        with open("camera.jpg", "wb") as file:
            file.write(image_data)

        print("✅ IMAGE RECEIVED")
        print(f"Saved {len(image_data)} bytes → camera.jpg")
        print("--------------------------------")