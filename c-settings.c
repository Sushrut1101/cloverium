#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DESTINATION_PATH "/home/anon/.comfy/wp.png"

// Function to set the background image
void set_background(const char *image_path) {
    if (copy_file(image_path, DESTINATION_PATH) == -1) {
        g_print("Error copying image to destination.");
        return;
    }

    restart_panel();
}

// Function to copy a file
int copy_file(const char *src, const char *dest) {
    FILE *source, *destination;
    char buffer[4096];
    size_t bytes;

    // Open source file in read mode
    source = fopen(src, "rb");
    if (source == NULL) {
        perror("Error opening source file");
        return -1;
    }

    // Open destination file in write mode
    destination = fopen(dest, "wb");
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return -1;
    }

    // Copy data from source to destination
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        if (fwrite(buffer, 1, bytes, destination) != bytes) {
            perror("Error writing to destination file");
            fclose(source);
            fclose(destination);
            return -1;
        }
    }

    // Close the files
    fclose(source);
    fclose(destination);

    return 0;
}

// Function to restart a process
void restart_panel() {
    // Kill existing process
    system("pkill -f panel.py");

    // Restart the process
    system("python3 panel.py &");
}

// Callback for the "Choose Image" button
void on_choose_image(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Please choose an image",
        GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL);

    // Add image file filter
    GtkFileFilter *filter_image = gtk_file_filter_new();
    gtk_file_filter_set_name(filter_image, "Image files");
    gtk_file_filter_add_mime_type(filter_image, "image/jpeg");
    gtk_file_filter_add_mime_type(filter_image, "image/png");
    gtk_file_filter_add_mime_type(filter_image, "image/gif");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter_image);

    // Show the dialog
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        // Get the selected image path
        char *selected_image = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (selected_image) {
            set_background(selected_image);
            g_free(selected_image);
        }
    }

    gtk_widget_destroy(dialog);
}

// Callback for the "Open xfce4-appearance-settings" button
void on_open_theme_settings(GtkButton *button, gpointer user_data) {
    // Open xfce4-appearance-settings
    system("xfce4-appearance-settings &");
}

// Main function
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button;

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150); // Adjusted height for two buttons

    // Create a vertical box to hold the widgets
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create the "Choose Image" button
    button = gtk_button_new_with_label("Set wallpaper (Might need to set it twice and reset panel)");
    g_signal_connect(button, "clicked", G_CALLBACK(on_choose_image), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    button = gtk_button_new_with_label("Change window decorations");
    g_signal_connect(button, "clicked", G_CALLBACK(on_open_theme_settings), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    gtk_main();

    return 0;
}
