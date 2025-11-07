/* EMPTYWINDOW is part of a learning project
 * toq 2025 Nov  LICENSE: MIT
 * 
 * 
 * From my point of view, this codebase is complete so far, I will then turn to the next level.
 * 
 */

#include <adwaita.h>

/* ----- Response des Dialogs prüfen ----- */
static void on_alert_dialog_response (AdwAlertDialog *dialog, const char *response, gpointer user_data)
{
    if (g_strcmp0 (response, "ok") == 0)
        g_print ("OK pressed\n");
    else
        g_print ("Cancel pressed\n");
}

static void on_button_clicked (GtkButton *button, gpointer user_data)
{
    /* ----- Fenster in welchem der Button untergeordnet ist holen ----- */
    GtkWindow *parent = GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(button)));
    /* ----- ist Fenster gültig? ----- */
    if (!parent || !GTK_IS_WINDOW(parent)) {
        g_warning("No valid parent window for alert dialog");
        return;
    }
    g_print("Hello my friend\n");

    /* ----- Alert-Dialog erstellen ----- */
    AdwAlertDialog *dialog = ADW_ALERT_DIALOG(adw_alert_dialog_new("My Message", 
     "First attempts completed, \nmoving on to the next codebase."));
    /* ----- Schaltflächen hinzufügen ----- */
    //adw_alert_dialog_add_response(dialog, "cancel", "Cancel");
    adw_alert_dialog_add_response(dialog, "ok", "OK");
    adw_alert_dialog_set_default_response(dialog, "ok");

    /* ----- Antwort-Signal mit Callback verbinden ----- */
    g_signal_connect(dialog, "response", G_CALLBACK(on_alert_dialog_response), NULL);

    /* ----- Dialog ausgeben ----- */
    adw_dialog_present(ADW_DIALOG(dialog), GTK_WIDGET(parent));
}

/* --------------------------------------------------------------------------- */
/* ----- Callback-Funktion wird aufgerufen wenn Anwendung aktiviert wird ----- */
static void on_activate (AdwApplication *app, gpointer)
{
    /* ----- Adwaita-Fenster wird erstellt und als "win" gespeichert ------------------------ */
    AdwApplicationWindow *win = ADW_APPLICATION_WINDOW (adw_application_window_new (GTK_APPLICATION (app))); 

    gtk_window_set_title (GTK_WINDOW(win), "empty window");   // Fenstertitel
    gtk_window_set_default_size (GTK_WINDOW(win), 640, 400);  // Standard-Fenstergröße
    gtk_window_present (GTK_WINDOW(win));                     // Fenster anzeigen lassen

    /* ----- ToolbarView (als Root‑Widget) erstellt und als Inhalt des Fensters festgelegt -- */
    AdwToolbarView *toolbar_view = ADW_TOOLBAR_VIEW (adw_toolbar_view_new ());
    adw_application_window_set_content (win, GTK_WIDGET (toolbar_view));

    /* ----- HeaderBar mit TitelWidget erstellt und dem ToolbarView hinzugefügt ------------ */
    AdwHeaderBar *header = ADW_HEADER_BAR (adw_header_bar_new());
    adw_header_bar_set_title_widget (header, gtk_label_new("My First Window"));
    adw_toolbar_view_add_top_bar (toolbar_view, GTK_WIDGET (header));

    /* ---- Haupt‑Box erstellen ----------------------------------------------------------- */
    GtkBox *box = GTK_BOX (gtk_box_new (GTK_ORIENTATION_VERTICAL, 12));
    gtk_widget_set_margin_top    (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_bottom (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_start  (GTK_WIDGET (box), 20);
    gtk_widget_set_margin_end    (GTK_WIDGET (box), 20);
    gtk_widget_set_hexpand (GTK_WIDGET (box), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (box), TRUE);

    /* ----- Text-Label erstellen  ----- */
    GtkWidget *label = gtk_label_new("press butten");
    gtk_widget_set_halign (label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (label, GTK_ALIGN_CENTER);

    /* ----- Label als Inhalt zur hinzufügen ----- */ 
    gtk_box_append (box, label);
    //adw_toolbar_view_set_content (toolbar_view, label);

    /* ----- Schaltfläche erzeugen ----- */
    GtkWidget *first_btn = gtk_button_new_with_label("button");
    gtk_widget_set_halign(first_btn, GTK_ALIGN_CENTER);

    /* ----- Callback auslösen ----- */
    g_signal_connect(first_btn, "clicked", G_CALLBACK(on_button_clicked), app);

    /* ----- Schaltfläche der Box hinzufügen ----- */
    gtk_box_append(box, first_btn);

    /* -----  Box zur ToolbarView hinzufügen ------------ */
    adw_toolbar_view_set_content(toolbar_view, GTK_WIDGET(box));

    /* ----- Fenster desktop‑konform anzeigen lassen ----- */
    gtk_window_present(GTK_WINDOW(win));

}

/* ---------------------------------------------------------------------------
 * Anwendungshauptteil, main()
 * --------------------------------------------------------------------------- */
int main (int argc, char **argv)
{
    g_autoptr (AdwApplication) app =                        // Instanz erstellen + App-ID + Default-Flags;
        adw_application_new ("free.toq.window", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL); // Signal mit on_activate verbinden
    /* --- g_application_run startet Anwendung u. wartet auf Ereignis --- */
    return g_application_run (G_APPLICATION (app), argc, argv);
}