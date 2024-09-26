#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For system()
#include <sys/wait.h> // For waitpid()
#include <stdio.h>  // For popen()
#include <errno.h> // For errno

#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30
#define BUTTON_SPACING 10

void open_startmenu() {
    system("build/menu");
}

// Function to get the list of open applications
char **get_open_applications() {
    FILE *pipe = popen("wmctrl -l", "r");
    if (pipe == NULL) {
        perror("popen failed");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;
    char **applications = NULL;

    while ((read = getline(&line, &len, pipe)) != -1) {
        // Skip the first line which is a header
        if (count == 0) {
            count++;
            continue;
        }

        // Extract the window title
        char *title = strrchr(line, ' ');
        if (title != NULL) {
            // Skip certain titles
            if (strstr(title, "Panel") || strstr(title, "Desktop") || 
                strstr(title, "Whisker Menu") || strstr(title, "Find") ||
                strstr(title, "Open") || strstr(title, "xfce4-panel")) {
                continue;
            }
            title++; // Move to the first character of the title

            // Resize the applications array
            applications = realloc(applications, sizeof(char *) * (count + 1));
            if (applications == NULL) {
                perror("realloc failed");
                free(line);
                pclose(pipe);
                return NULL;
            }

            // Duplicate the title
            applications[count - 1] = strdup(title);
            count++;
        }
    }

    free(line);
    pclose(pipe);

    // Add a NULL terminator
    applications = realloc(applications, sizeof(char *) * (count + 1));
    applications[count] = NULL;

    return applications;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create a GtkWindow with no decorations
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    // Set window size
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 50);

    // Make the window the same width as the display
    GdkScreen *screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen);
    int height = gdk_screen_get_height(screen);
    gtk_window_resize(GTK_WINDOW(window), width, 50);

    // Move window to bottom of the screen
    gtk_window_move(GTK_WINDOW(window), 0, height - 50); 

    // Create a GtkFixed container to hold the image
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Set taskbar image
    GtkWidget *image1 = gtk_image_new_from_file("/home/anon/.comfy/panel.png");
    gtk_fixed_put(GTK_FIXED(fixed), image1, 0, 0);

    // Create the start menu button
    GtkWidget *startmenu_button = gtk_button_new();
    GtkWidget *image2 = gtk_image_new_from_file("assets/clover.png"); 
    gtk_button_set_image(GTK_BUTTON(startmenu_button), image2);
    gtk_fixed_put(GTK_FIXED(fixed), startmenu_button, 5, 0); // Move to the leftmost position
    g_signal_connect(startmenu_button, "clicked", G_CALLBACK(open_startmenu), NULL); 

    // Get the list of open applications
    char **open_apps = get_open_applications();
    if (open_apps == NULL) {
        // Handle the error
        gtk_main();
        return 1;
    }

    // Add open application buttons (dynamically)
    int x_offset = 75; // Start position for application buttons
    for (int i = 0; open_apps[i] != NULL; i++) {
        // Get the application name
        char *app_name = open_apps[i];

        // Create a button with the application name
        GtkWidget *app_button = gtk_button_new_with_label(app_name);

        // Set the application name as the button's tooltip
        gtk_widget_set_tooltip_text(app_button, app_name);

        // Set button width
        gtk_widget_set_size_request(app_button, BUTTON_WIDTH, BUTTON_HEIGHT); 

        // Position the button
        gtk_fixed_put(GTK_FIXED(fixed), app_button, x_offset, 0);
        x_offset += BUTTON_WIDTH + BUTTON_SPACING; // Adjust x_offset for next button
    }

    // Free allocated memory for open_apps
    for (int i = 0; open_apps[i] != NULL; i++) {
        free(open_apps[i]);
    }
    free(open_apps);

    // Set the window as a top-level window (always on top)
    gtk_window_set_type_hint(GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DOCK);

    // Show the window
    gtk_widget_show_all(window);

    // Load CSS style
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("style.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Set the application name for the taskbar
    gtk_window_set_title(GTK_WINDOW(window), "Panel"); 

    gtk_main();

    return 0;
}
