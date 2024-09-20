#!/bin/bash

# Get the display width and height
display_width=$(xdpyinfo | grep 'dimensions:' | awk '{print $2}' | cut -d'x' -f1)
display_height=$(xdpyinfo | grep 'dimensions:' | awk '{print $2}' | cut -d'x' -f2)

# Calculate the desired crop dimensions for the panel
crop_width=$display_width
crop_height=50

# Crop the image and apply blur to the panel
convert /home/$USER/.comfy/wp.png -gravity South -crop ${crop_width}x${crop_height}+0+0 +repage -blur 0x6  /home/$USER/.comfy/cropped.png
composite -dissolve 40 assets/taskbaroverlay.png  /home/$USER/.comfy/cropped.png /home/$USER/.comfy/panel.png

# Calculate the desired crop dimensions for the menu
crop_width=400
crop_height=720

# Crop the image and apply blur to the menu
convert /home/$USER/.comfy/wp.png -gravity SouthWest -crop ${crop_width}x${crop_height}+0+48 +repage -blur 0x6  /home/$USER/.comfy/menu-cropped.png
composite -dissolve 40 assets/menuoverlay.png  /home/$USER/.comfy/menu-cropped.png /home/$USER/.comfy/menubg.png
