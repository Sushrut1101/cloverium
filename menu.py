import gi
import subprocess

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk, Gdk

class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="")

        # Create a fixed layout to set the background image
        self.fixed = Gtk.Fixed()
        self.add(self.fixed)

        # Load an image and set it as a background
        self.image = Gtk.Image.new_from_file("/home/anon/.comfy/menubg.png")
        self.fixed.put(self.image, 0, 0)

        # Create a vertical box with added padding
        self.box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=1)
        self.fixed.put(self.box, 0, 0)

        # Load CSS
        self.load_css()

        # Create buttons
        self.create_button("Appearance Settings", self.on_button1_clicked)
        self.create_button("Display Settings", self.on_button2_clicked)
        self.create_button("Set Wallpaper", self.on_button3_clicked)

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
        x_position = 2
        y_position = height - window_height - 50

        self.move(x_position, y_position)

    def on_button1_clicked(self, widget):
        subprocess.Popen(["xfce4-appearance-settings"])
        self.destroy()  # Close the menu window

    def on_button2_clicked(self, widget):
        subprocess.Popen(["xfce4-display-settings"])
        self.destroy()  # Close the menu window
        
    def on_button3_clicked(self, widget):
        subprocess.Popen(["build/settings"])
        self.destroy()  # Close the menu window
        
win = MyWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()