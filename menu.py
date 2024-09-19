import gi
import subprocess

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk, GdkPixbuf

class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="")

        # Create a fixed layout to set the background image
        self.fixed = Gtk.Fixed()
        self.add(self.fixed)

        # Load an image and set it as a background
        self.image = Gtk.Image.new_from_pixbuf(GdkPixbuf.Pixbuf.new_from_file("/home/anon/.comfy/menubg.png"))
        self.fixed.put(self.image, 0, 0)

        # Create a vertical box with added padding
        self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=1)
        self.fixed.put(self.box, 0, 0)

        # Load CSS
        self.load_css()

        # Create buttons
        self.create_button("Web Browser", self.on_button1_clicked)
        self.create_button("File Explorer", self.on_button2_clicked)
        self.create_button("Video Player", self.on_button3_clicked)
        self.create_button("Appearance Settings", self.on_button4_clicked)
        self.create_button("Display Settings", self.on_button5_clicked)
        self.create_button("Shut Down", self.on_button6_clicked)
        self.create_button("Lock Screen", self.on_button7_clicked)
        self.create_button("Reboot", self.on_button8_clicked)
        self.create_button("Set Wallpaper", self.on_button9_clicked)

        # Remove window decorations
        self.set_decorated(False)

        # Connect the 'map' event to position the window
        self.connect("map", self.on_map)

    def load_css(self):
        css_provider = Gtk.CssProvider()
        css_provider.load_from_path("style.css")

        screen = Gdk.Screen.get_default()
        Gtk.StyleContext.add_provider_for_screen(screen, css_provider, Gtk.STYLE_PROVIDER_PRIORITY_USER)

    def create_button(self, label, callback):
        hbox = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=6)
        button_label = Gtk.Label(label=label)
        button_label.set_xalign(0)

        hbox.pack_start(button_label, True, True, 0)
        button = Gtk.Button()
        button.add(hbox)
        
        button.set_size_request(100, 48)
        button.connect("clicked", callback)

        button.get_style_context().add_class('large-button')

        button.set_margin_top(6)
        button.set_margin_bottom(6)
        button.set_margin_left(6)
        button.set_margin_right(6)

        self.box.pack_start(button, True, True, 0)

    def on_map(self, widget):
        screen = Gdk.Screen.get_default()
        width = screen.get_width()
        height = screen.get_height()

        window_height = self.get_allocation().height
        x_position = 0
        y_position = height - window_height - 48

        self.move(x_position, y_position)

    def on_button1_clicked(self, widget):
        subprocess.Popen(["chromium"])
        self.destroy()  # Close the menu window

    def on_button2_clicked(self, widget):
        subprocess.Popen(["thunar"])
        self.destroy()  # Close the menu window

    def on_button3_clicked(self, widget):
        subprocess.Popen(["parole"])
        self.destroy()  # Close the menu window

    def on_button4_clicked(self, widget):
        subprocess.Popen(["xfce4-appearance-settings"])
        self.destroy()  # Close the menu window

    def on_button5_clicked(self, widget):
        subprocess.Popen(["xfce4-display-settings"])
        self.destroy()  # Close the menu window

    def on_button6_clicked(self, widget):
        subprocess.Popen(["shutdown"])
        self.destroy()  # Close the menu window

    def on_button7_clicked(self, widget):
        subprocess.Popen(["xscreensaver-command", "-lock"])
        self.destroy()  # Close the menu window

    def on_button8_clicked(self, widget):
        subprocess.Popen(["systemctl", "reboot"])
        self.destroy()  # Close the menu window
        
    def on_button9_clicked(self, widget):
        subprocess.Popen(["python3", "settings.py"])
        self.destroy()  # Close the menu window
        
# CSS to make the buttons text larger
css = b"""
.large-button {
    font-size: 24px;  /* Adjust this value for larger text */
}
"""

# Load CSS
style_provider = Gtk.CssProvider()
style_provider.load_from_data(css)
Gtk.StyleContext.add_provider_for_screen(
    Gdk.Screen.get_default(),
    style_provider,
    Gtk.STYLE_PROVIDER_PRIORITY_USER
)

win = MyWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
