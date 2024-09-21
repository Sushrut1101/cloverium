#include <gtk/gtk.h>
#include <gdk/gdk.h>

int main(int argc, char *argv[]) {
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Panel");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    // Set window size
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 720);

    // Create a fixed container
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Load an image and set it as a background
    GtkWidget *image = gtk_image_new_from_file("/home/anon/.comfy/menubg.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);
    GtkWidget *image2 = gtk_image_new_from_file("assets/user.png");
    gtk_fixed_put(GTK_FIXED(fixed), image2, 455, 20);

    // Create a vertical box to hold the buttons
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 13, 10); // Position the box at the top-left

    // Create a helper function to create buttons with images and labels
    GtkWidget *create_button(const gchar *label, const gchar *icon_path) {
        GtkWidget *button = gtk_button_new();
        GtkWidget *label_widget = gtk_label_new(label);
        GtkWidget *icon_widget = gtk_image_new_from_file(icon_path);

        // Create a horizontal box to hold the icon and label
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_box_pack_start(GTK_BOX(hbox), icon_widget, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(hbox), label_widget, FALSE, FALSE, 0);

        // Set the hbox as the child of the button
        gtk_container_add(GTK_CONTAINER(button), hbox);

        return button;
    }

    // Create buttons using the helper function
    GtkWidget *button1 = create_button("Web Browser", "assets/clover.png");
    GtkWidget *button2 = create_button("File Manager", "assets/clover.png");
    GtkWidget *button3 = create_button("Terminal", "assets/clover.png");
    GtkWidget *button4 = create_button("Screen Settings", "assets/clover.png");
    GtkWidget *button5 = create_button("Appearance Settings", "assets/clover.png");
    GtkWidget *button6 = create_button("Set Wallpaper", "assets/clover.png");
    GtkWidget *button7 = create_button("Settings", "assets/clover.png");
    GtkWidget *button8 = create_button("Search", "assets/clover.png");

    // Add the buttons to the vertical box
    gtk_box_pack_start(GTK_BOX(vbox), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button6, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button7, FALSE, FALSE, 0);
    // Add button7 with a spacing of 50px
    gtk_box_pack_start(GTK_BOX(vbox), button8, FALSE, FALSE, 150);

    // Set button size
    gtk_widget_set_size_request(button1, 375, 60); // Assuming 100x30 is default size
    gtk_widget_set_size_request(button2, 200, 60);
    gtk_widget_set_size_request(button3, 200, 60);
    gtk_widget_set_size_request(button4, 200, 60);
    gtk_widget_set_size_request(button5, 200, 60);
    gtk_widget_set_size_request(button6, 200, 60);
    gtk_widget_set_size_request(button7, 200, 60);
    gtk_widget_set_size_request(button8, 200, 40);
    
    // Make the window visible
    gtk_widget_show_all(window);

    // Get the screen
    GdkScreen *screen = gdk_screen_get_default();

    // Get the screen's width and height
    int screen_width = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);

    // Set the window position to the bottom left corner, adjusted for the 50px margin
    gtk_window_move(GTK_WINDOW(window), 3, screen_height - 640 - 130);

    // Load CSS stylesheet
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Start the GTK+ event loop
    gtk_main();

    return 0;
}
