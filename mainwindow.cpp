#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->build_toolbar_programatically();
    this->load_dictionary_from_internal_resources();
    this->display_all_words();

    connect(search_textfield, &QLineEdit::textChanged, this, &MainWindow::search_textfield_text_has_changed);
}

/*
 *
 * This functions just create a new component (QToolbar) programmatically just to give you an
 * example of how to it from code instead using the Designer.
 *
*/
void MainWindow::build_toolbar_programatically(){
    ui->toolBar->setStyleSheet("margin: 1; padding: 3;");
    ui->toolBar->setMovable(false);

    this->search_textfield = new QLineEdit(ui->toolBar);
    this->search_textfield->setStyleSheet("color: black; border-radius: 5px;");
    this->search_textfield->setPlaceholderText("Search");
    this->search_textfield->setValidator(new QRegExpValidator( QRegExp("[a-zA-Z]{1,30}"), this ));
    this->search_textfield->setAttribute(Qt::WA_MacShowFocusRect, 0);

    QWidget* spacer= new QWidget(ui->toolBar);
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    ui->toolBar->addWidget(spacer);
    ui->toolBar->addWidget(this->search_textfield);
}


/*
 *
 * This function open the dictionary file and read it line by line.
 * Per line the word and meaning are extracted.
 *
 * */
void MainWindow::load_dictionary_from_internal_resources() {

    QFile resource_file(":/input/resources/EnglishDictionary.txt");

    if (resource_file.open(QIODevice::ReadOnly)) {
        QTextStream in(&resource_file);
        while (!in.atEnd()) {
            auto line       = in.readLine().toStdString();
            auto word       = line.substr(0, line.find(" "));
            auto meaning    = line.substr(word.size() + 2 , line.find("\n"));

            this->complete_dictionary[word] = meaning;

            /*
             *
             * HERE you can use word and meaning to create your own structure and add it
             * to your data structure. Both are of type std::string
             *
             * */
        }
        resource_file.close();
    } else {
        qFatal("File doesn't exists");
    }
}

void MainWindow::search_textfield_text_has_changed(const QString &text) {
    ui->autocompletion_list->clear();
    ui->autocompletion_list->clearSelection();

    if(text.size() == 0){
        this->display_all_words();
        return;
    }


    /*
     *
     * REPLACE the lines below in order to suggest a list of words based on Patricia Tries
     * like the following:
     *
     * std::std_text = text.toStdString()
     * vector<string> autocompletion_result = PatriciaTrie::instance.search(std_text);
     *
     * */

    std::vector<std::string> autocompletion_result = {"alpha", "beta", "gamma"};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(autocompletion_result.begin(), autocompletion_result.end(), g);


    /*
     *
     * Use the following line to display your results, it expects a std::vector<std::string>
     *
     * */
    this->display_suggested_words(autocompletion_result);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::display_suggested_words(std::vector<std::string> suggested_words) {
    for (auto const& word : suggested_words){
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(word));
        item->setSizeHint(QSize(item->sizeHint().width(), 40));
        ui->autocompletion_list->addItem(item) ;
    }
    ui->autocompletion_list->setFocusPolicy(Qt::NoFocus);
    ui->browser->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::display_all_words() {
    // Get map keys as std vector
    std::vector<std::string> std_vector_words;
    transform(complete_dictionary.begin(), complete_dictionary.end(), back_inserter(std_vector_words), [](auto item) {
        return item.first;
    });

    this->display_suggested_words(std_vector_words);
}


/*
 *
 * This funcions is triggered every time the user clicks on some item of the suggested words list
 * It search for the meaning of the selected word and add it to the result in HTML format.
 *
 * */
void MainWindow::on_autocompletion_list_itemClicked(QListWidgetItem *item) {

    auto qword       = item->text();
    auto qmeaning    = QString::fromStdString(this->complete_dictionary[item->text().toStdString()]);

    /*
     *  REPLACE the above lines with your search algorithm, something like the following:
     *

        std::string word = item->text().toStdString();
        std::string meaning = <your_data_structure>.search(word).meaning;

        auto qword      = QString::fromStdString(word);
        auto qmeaning   = QString::fromStdString(meaning);
    */


    QString content =   "<b><font size=7 color=black>" + qword + "</font></b>";
    content         +=  "<br><br>";
    content         +=  "<font size=4 color=\"#565151\">" + qmeaning + "</font>";

    ui->browser->setHtml(content);
}

