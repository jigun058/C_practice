import pyautogui
import cv2
import numpy as np
import time

def find_and_click_all_images_in_region_continuously(target_image_path, top_left, bottom_right):
    # Calculate region from top-left and bottom-right points
    region = (
        top_left[0],
        top_left[1],
        bottom_right[0] - top_left[0],
        bottom_right[1] - top_left[1]
    )

    # Load the target image to find
    target_image = cv2.imread(target_image_path, cv2.IMREAD_GRAYSCALE)
    target_height, target_width = target_image.shape[:2]

    # Set the threshold for image match
    threshold = 0.95
    print("Press Ctrl+C to stop.")

    try:
        while True:
            # Capture the specified screen region
            screenshot = pyautogui.screenshot(region=region)
            screenshot = cv2.cvtColor(np.array(screenshot), cv2.COLOR_RGB2GRAY)

            # Perform template matching
            result = cv2.matchTemplate(screenshot, target_image, cv2.TM_CCOEFF_NORMED)
            
            # Find all points where match quality is above threshold
            match_locations = np.where(result >= threshold)
            
            # Iterate over all found locations
            for (match_x, match_y) in zip(match_locations[1], match_locations[0]):
                # Calculate the center position of each matched area
                center_x = top_left[0] + match_x + target_width // 2
                center_y = top_left[1] + match_y + target_height // 2

                # Click on the center of each matched area
                pyautogui.click(center_x, center_y)
                print(f"Clicked on image at ({center_x}, {center_y})")

            # Short delay to prevent excessive CPU usage
            time.sleep(0.1)  # Adjust this delay as needed for optimal speed
    except KeyboardInterrupt:
        print("\nStopped by user.")

# Define the region with top-left and bottom-right corners
target_image_path = "/Users/taegwon/Desktop/C_practice/inLecture/target_image.png"
top_left = (1306, 440)
bottom_right = (1623, 935)

# Start the continuous image search
find_and_click_all_images_in_region_continuously(target_image_path, top_left, bottom_right)