import subprocess
import sys
from datetime import datetime
import os
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Pango
from gi.repository import Gtk, Gdk, GLib, GdkPixbuf 

class Panel(Gtk.Window):
    def __init__(self):
        super().__init__(title="Panel")
        self.load_css()

        # Get screen size using the new algorithm
        display = Gdk.Display.get_default()
        monitor = display.get_primary_monitor()
        scale_factor = monitor.get_scale_factor()
        geometry = monitor.get_geometry()
        self.width = geometry.width * scale_factor
        self.height = 50  

        self.set_default_size(self.width, self.height)

        # Calculate y-position based on screen height
        y_position = geometry.height * scale_factor - self.height
        self.move(0, y_position)

        # Necessary settings for the panel to function correctly
        self.set_type_hint(Gdk.WindowTypeHint.DOCK)
        self.set_decorated(False)
        self.set_app_paintable(True)
        self.set_accept_focus(False)
        self.set_keep_above(True)  # Ensure panel stays on top
        self.fixed = Gtk.Fixed()
        self.add(self.fixed)
        self.image = Gtk.Image.new_from_pixbuf(GdkPixbuf.Pixbuf.new_from_file("/home/anon/.comfy/panel.png"))
        self.fixed.put(self.image, 0, 0)

        # Create a button with an icon
        self.start_menu_button = Gtk.Button()
        self.start_menu_button.connect("clicked", self.on_start_menu_clicked)
        self.fixed.put(self.start_menu_button, 2, 1)    # Button location
        self.start_menu_button.set_size_request(0, 40)  # Fixed height for the button

        # Load the clover icon
        clover_icon = Gtk.Image.new_from_file("assets/clover.png")
        self.start_menu_button.set_image(clover_icon)
        self.clock_button = Gtk.Button(label="")
        self.clock_button.set_size_request(100, 40)  # Fixed height for the button
        self.clock_button.connect("clicked", self.on_clock_clicked)
        self.fixed.put(self.clock_button, self.width - 103, 1)

        GLib.timeout_add_seconds(1, self.update_clock)

        # Task List
        self.tasklist_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=6)
        self.fixed.put(self.tasklist_box, 72, 1)
        self.update_tasklist()
        GLib.timeout_add_seconds(1, self.update_tasklist)  # Refresh every second
        self.menu_process = None
        self.show_all()
        self.update_clock()

        # Run blur.sh when the panel is shown
        subprocess.Popen(["./blur.sh"], shell=True)  # Replace with the actual path to blur.sh

    def load_css(self):
        style_provider = Gtk.CssProvider()
        style_provider.load_from_path("style.css")
        Gtk.StyleContext.add_provider_for_screen(Gdk.Screen.get_default(), style_provider, Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION)

    def on_start_menu_clicked(self, widget):
        if self.menu_process is None:
            #self.menu_process = subprocess.Popen(["build/menu"])
            self.menu_process = subprocess.Popen([sys.executable, "menu.py"])
        else:
            self.menu_process.terminate()
            self.menu_process.wait()
            self.menu_process = None

    def on_clock_clicked(self, widget):
        print(f"Current time is: {self.clock_button.get_label()}") 

    def update_clock(self):
        now = datetime.now()
        formatted_time = now.strftime("%H:%M")
        self.clock_button.set_label(formatted_time)
        return True  

    def update_tasklist(self):
        # Clear the current task list
        for child in self.tasklist_box.get_children():
            self.tasklist_box.remove(child)

        # Get the list of running processes
        try:
            # Sample command that lists running GUI applications
            proc = subprocess.Popen(['wmctrl', '-l'], stdout=subprocess.PIPE)
            output = proc.communicate()[0].decode('utf-8')

            for line in output.splitlines():
                parts = line.split()
                if len(parts) > 3:
                    title = " ".join(parts[3:])
                    
                    # Skip "Panel" and "Desktop" titles
                    if "Panel" in title or "Desktop" in title or "Whisker Menu" in title or "Find" in title  or "Open" in title or "xfce4-panel" in title:
                        continue

                    # Create a button with left-aligned text
                    button_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=6)
                    button_box.set_halign(Gtk.Align.START)  # Align to the left

                    # Create an icon image (you'll need to provide a way to get the icon for the window)
                    # For this example, we'll just use a placeholder icon.
                    icon_image = Gtk.Image.new_from_file("assets/clover.png")  
                    button_box.pack_start(icon_image, False, False, 0) 

                    # Create a label for the button
                    label = Gtk.Label(label=title)
                    label.set_ellipsize(Pango.EllipsizeMode.END)  # Ellipsize long titles
                    # Set a fixed width of 150px for the button
                    label.set_size_request(100, -1) 
                    button_box.pack_start(label, True, True, 0)

                    # Create the button with the label
                    button = Gtk.Button()
                    button.add(button_box)
                    button.connect("clicked", self.on_task_clicked, parts[0])  # Pass window ID
                    button.set_size_request(100, 40)  # Set max width to 100px and fixed height

                    # Add the button to the task list box
                    self.tasklist_box.pack_start(button, True, True, 0)

        except Exception as e:
            print("Error retrieving tasklist:", e)

        self.show_all()
        return True


    def on_task_clicked(self, widget, window_id):
        # Use wmctrl to activate a window using its ID
        subprocess.call(['wmctrl', '-ia', window_id])

def main():
    window = Panel()
    window.connect("destroy", Gtk.main_quit)
    window.show_all()
    Gtk.main()

if __name__ == "__main__":
    main()
