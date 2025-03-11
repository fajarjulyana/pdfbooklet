#include <gtk/gtk.h>
#include <iostream>
#include <vector>
#include <string>

GtkWidget *entry_paper, *entry_outer_margin, *entry_inner_margin, *entry_top_margin, *entry_bottom_margin, *entry_signature;

void on_button_clicked(GtkWidget *widget, gpointer data) {
    GtkFileChooserDialog *dialog;
    dialog = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new(
        "Select PDF Files", GTK_WINDOW(data), GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_ACCEPT, NULL));
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        GSList *files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));
        std::vector<std::string> file_list;
        
        for (GSList *iter = files; iter != NULL; iter = iter->next) {
            file_list.push_back(static_cast<char *>(iter->data));
            g_free(iter->data);
        }
        g_slist_free(files);

        std::string command = "pdfbook2 --paper=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_paper))) +
            " --outer-margin=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_outer_margin))) +
            " --inner-margin=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_inner_margin))) +
            " --top-margin=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_top_margin))) +
            " --bottom-margin=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_bottom_margin))) +
            " --signature=" + std::string(gtk_entry_get_text(GTK_ENTRY(entry_signature))) +
            " --no-crop";

        for (const auto &file : file_list) {
            command += " \"" + file + "\"";
        }

        system(command.c_str());
    }
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PDF Booklet Creator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);
    
    GtkWidget *label_paper = gtk_label_new("Paper Size:");
    gtk_box_pack_start(GTK_BOX(box), label_paper, FALSE, FALSE, 0);
    entry_paper = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_paper), "a4paper");
    gtk_box_pack_start(GTK_BOX(box), entry_paper, TRUE, TRUE, 0);
    
    GtkWidget *label_outer_margin = gtk_label_new("Outer Margin:");
    gtk_box_pack_start(GTK_BOX(box), label_outer_margin, FALSE, FALSE, 0);
    entry_outer_margin = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_outer_margin), "10");
    gtk_box_pack_start(GTK_BOX(box), entry_outer_margin, TRUE, TRUE, 0);
    
    GtkWidget *label_inner_margin = gtk_label_new("Inner Margin:");
    gtk_box_pack_start(GTK_BOX(box), label_inner_margin, FALSE, FALSE, 0);
    entry_inner_margin = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_inner_margin), "5");
    gtk_box_pack_start(GTK_BOX(box), entry_inner_margin, TRUE, TRUE, 0);
    
    GtkWidget *label_top_margin = gtk_label_new("Top Margin:");
    gtk_box_pack_start(GTK_BOX(box), label_top_margin, FALSE, FALSE, 0);
    entry_top_margin = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_top_margin), "10");
    gtk_box_pack_start(GTK_BOX(box), entry_top_margin, TRUE, TRUE, 0);
    
    GtkWidget *label_bottom_margin = gtk_label_new("Bottom Margin:");
    gtk_box_pack_start(GTK_BOX(box), label_bottom_margin, FALSE, FALSE, 0);
    entry_bottom_margin = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_bottom_margin), "10");
    gtk_box_pack_start(GTK_BOX(box), entry_bottom_margin, TRUE, TRUE, 0);
    
    GtkWidget *label_signature = gtk_label_new("Signature:");
    gtk_box_pack_start(GTK_BOX(box), label_signature, FALSE, FALSE, 0);
    entry_signature = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_signature), "36");
    gtk_box_pack_start(GTK_BOX(box), entry_signature, TRUE, TRUE, 0);
    
    GtkWidget *button = gtk_button_new_with_label("Select PDF Files");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}

