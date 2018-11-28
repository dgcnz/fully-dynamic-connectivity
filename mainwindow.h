#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QListWidgetItem>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <random>

#include <redblack/Tree.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_autocompletion_list_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QLineEdit * search_textfield;
     Tree<DictionaryTrait> rb_tree;
    std::map<std::string, std::string> complete_dictionary;

    void build_toolbar_programatically();
    void load_dictionary_from_internal_resources();

    void display_suggested_words(std::vector<std::string> suggested_words);
    void display_all_words();

    void search_textfield_text_has_changed(const QString &text);
};

#endif // MAINWINDOW_H
