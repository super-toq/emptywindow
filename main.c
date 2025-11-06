/*
 * toq 2025, LICENCE MIT
 *
 * gcc $(pkg-config --cflags gtk4 libadwaita-1) -o window main.c $(pkg-config --libs gtk4 libadwaita-1) 
 */

#include <adwaita.h>

static void
on_activate (AdwApplication *app, gpointer user_data) //Callback-Funktion wird aufgerufen wenn Anw. aktiviert wird
{
    /* ----- Adwaita-Fenster wird erstellt und als "win" gespeichert -------------------------- */
    AdwApplicationWindow *win = ADW_APPLICATION_WINDOW (adw_application_window_new (GTK_APPLICATION (app))); 

    gtk_window_set_title (GTK_WINDOW (win), "empty window");   // Fenstertitel
    gtk_window_set_default_size (GTK_WINDOW (win), 640, 360);  // Standard-Fenstergröße
    gtk_window_present (GTK_WINDOW (win));                     // Fenster anzeigen lassen

    /* ----- ToolbarView (als Root‑Widget) erstellt und als Inhalt des Fensters festgelegt ---- */
    AdwToolbarView *toolbar_view = ADW_TOOLBAR_VIEW (adw_toolbar_view_new ());
    adw_application_window_set_content (win, GTK_WIDGET (toolbar_view));

    /* ----- HeaderBar mit TitelWidget erstellt und dem ToolbarView hinzugefügt -------------- */
    AdwHeaderBar *header = ADW_HEADER_BAR (adw_header_bar_new ());
    adw_header_bar_set_title_widget (header, gtk_label_new ("My first Window"));
    adw_toolbar_view_add_top_bar (toolbar_view, GTK_WIDGET (header));
}

/* ---------------------------------------------------------------------------
 * Anwendungshauptteil, main()
 * --------------------------------------------------------------------------- */
int
main (int argc, char **argv)
{
    g_autoptr (AdwApplication) app =                        // Instanz erstellen, mit App-ID und Default-Flags
        adw_application_new ("free.toq.emptywindow", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL); // Signal mit on_activate verbinden

    return g_application_run (G_APPLICATION (app), argc, argv); // g_application_run startet Anw. u. wartet auf Ereignis
}
