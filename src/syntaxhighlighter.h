#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QVector>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument* parent = nullptr);
protected:
    virtual void highlightBlock(const QString& str) override;
private:
    void addRules(const QStringList& patterns, const QTextCharFormat& format);
    void highlightDigits(const QString& str);

    struct HighlightingRule
    {
        QRegularExpression  pattern;
        QTextCharFormat     format;
    };

    QVector<HighlightingRule> highlightingRules_;
};

#endif // SYNTAXHIGHLIGHTER_H
