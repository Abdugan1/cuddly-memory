#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>

namespace Ui {
class TextEditor;
}

class SyntaxHighlighter;

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

private slots:

    void on_action_SaveAs_triggered();

private:
    Ui::TextEditor *ui;
    SyntaxHighlighter* syntaxHighlighter_;
};

#endif // TEXTEDITOR_H
