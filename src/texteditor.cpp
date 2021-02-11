#include "texteditor.h"
#include "ui_texteditor.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>

TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::on_action_SaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), QDir::currentPath()
                                                    , "text files (*.txt);;"
                                                      "cpp files (*.cpp);;"
                                                      "header files (.h)");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}
