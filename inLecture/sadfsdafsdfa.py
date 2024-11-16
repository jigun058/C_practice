import cv2

target_image_path = "/Users/taegwon/Desktop/C_practice/inLecture/target_image.png"
target_image = cv2.imread(target_image_path, cv2.IMREAD_GRAYSCALE)

if target_image is None:
    print("Failed to load image. Check the file path and file permissions.")
else:
    print("Image loaded successfully.")