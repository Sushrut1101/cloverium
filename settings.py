import gi
import os
import shutil
import subprocess

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class BackgroundSetter:
    def __init__(self):
        self.window = Gtk.Window(title="Set Background")
        self.window.set_default_size(300, 100)

        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.window.add(vbox)

        button = Gtk.Button(label="Choose Image")
        button.connect("clicked", self.on_choose_image)
        vbox.pack_start(button, True, True, 0)

        self.window.show_all()

    def on_choose_image(self, widget):
        dialog = Gtk.FileChooserDialog(
            title="Please choose an image",
            parent=self.window,
            action=Gtk.FileChooserAction.OPEN,
        )
        dialog.add_buttons(
            Gtk.STOCK_CANCEL,
            Gtk.ResponseType.CANCEL,
            Gtk.STOCK_OPEN,
            Gtk.ResponseType.OK,
        )

        filter_image = Gtk.FileFilter()
        filter_image.set_name("Image files")
        filter_image.add_mime_type("image/jpeg")
        filter_image.add_mime_type("image/png")
        filter_image.add_mime_type("image/gif")
        dialog.add_filter(filter_image)

        response = dialog.run()
        if response == Gtk.ResponseType.OK:
            selected_image = dialog.get_filename()
            self.set_background(selected_image)
        dialog.destroy()

    def set_background(self, image_path):
        try:
            destination = "/home/anon/.comfy/wp.png"  # Or your desired path
            shutil.copyfile(image_path, destination)

            # Optionally, refresh the desktop background here (method varies by DE)
            # Example for some desktop environments:
            # os.system("gsettings set org.gnome.desktop.background picture-uri file://" + destination) # GNOME
            # os.system("xfconf-modify -c xfce4-desktop -p /backdrop/screen0/monitor0/workspace0/last-image -s " + destination) # XFCE

            # Restart panel.py twice
            for _ in range(2):
                # Kill existing panel.py instance
                subprocess.run(["pkill", "-f", "panel.py"])

                # Restart panel.py
                subprocess.Popen(["python3", "panel.py"])

        except Exception as e:
            print(f"Error setting background: {e}")
            # Handle the error appropriately (e.g., display an error dialog)

if __name__ == "__main__":
    app = BackgroundSetter()
    Gtk.main()
