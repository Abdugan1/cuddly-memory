#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) :
    QSyntaxHighlighter(parent)
{
    // 103, 216, 239 -> blue
    // 249, 36, 114 -> red
    // 172, 128, 255 -> violet

    const QStringList blueKeywordPatterns = {
        QStringLiteral("\\bbool\\b"),   QStringLiteral("\\bint\\b"),    QStringLiteral("\\bvoid\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\bfloat\\b"),  QStringLiteral("\\bchar\\b"),
        QStringLiteral("\\bclass\\b"),  QStringLiteral("\\bstruct\\b"), QStringLiteral("\\bunion\\b")
    };

    QTextCharFormat blueKeywordFormat;
    blueKeywordFormat.setForeground(QColor(103, 216, 239));
    blueKeywordFormat.setFontItalic(true);

    addRules(blueKeywordPatterns, blueKeywordFormat);


    const QStringList redKeywordPatterns = {
        QStringLiteral("\\bconst\\b"),  QStringLiteral("\\bvirtual\\b"),    QStringLiteral("\\bmutable\\b"),
        QStringLiteral("\\bthrow\\b"),  QStringLiteral("\\bfor\\b"),        QStringLiteral("\\bconst_cast\\b"),
        QStringLiteral("\\belse\\b"),   QStringLiteral("\\bswitch\\b"),     QStringLiteral("\\bnoexcept\\b"),
        QStringLiteral("\\bnew\\b"),    QStringLiteral("\\breturn\\b"),     QStringLiteral("\\bnamespace\\b"),
        QStringLiteral("\\busing\\b"),  QStringLiteral("\\bthis\\b"),       QStringLiteral("\\boverride\\b"),
        QStringLiteral("\\bcase\\b"),   QStringLiteral("\\bstatic\\b"),     QStringLiteral("\\bstatic_cast\\b"),
        QStringLiteral("\\bif\\b"),     QStringLiteral("\\bdynamic_cast\\b")
    };

    QTextCharFormat redKeywordFormat;
    redKeywordFormat.setForeground(QColor(249, 36, 114));

    addRules(redKeywordPatterns, redKeywordFormat);


    const QStringList violetKeywordPatterns = {
        QStringLiteral("\\btrue\\b"), QStringLiteral("\\bfalse\\b"), QStringLiteral("\\bnullptr\\b")
    };

    QTextCharFormat violetKeywordFormat;
    violetKeywordFormat.setForeground(QColor(172, 128, 255));

    addRules(violetKeywordPatterns, violetKeywordFormat);


    const QStringList singleLineCommentPattern = {
        QStringLiteral("//[^\n]*")
    };
    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::gray);


    addRules(singleLineCommentPattern, singleLineCommentFormat);
}


void SyntaxHighlighter::highlightBlock(const QString& str)
{
    // highlight digits
    if (str.contains(QRegularExpression("\\d")))
        highlightDigits(str);

    // highlight multi line comments


    // highlight rules
    for (const HighlightingRule& rule : qAsConst(highlightingRules_)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(str);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}

void SyntaxHighlighter::addRules(const QStringList& patterns, const QTextCharFormat& format)
{
    static HighlightingRule rule;
    for (const QString& pattern : patterns) {
        rule.pattern    = QRegularExpression(pattern);
        rule.format     = format;

        highlightingRules_.push_back(rule);
    }
}

void SyntaxHighlighter::highlightDigits(const QString& str)
{
    const int size = str.size();
    for (int i = 0; i < size; ++i) {
        if (str[i].isNumber()) {
            // do not highlight if before digit is letter
            if (i != 0 && str[i - 1].isLetter()) {
                while (!str[i].isSpace()) {
                    i++;
                    if (i >= size - 1)  // end of string, exit the function
                        return;
                }
            }
            setFormat(i, 1, QColor(172, 128, 255));
        }
    }
}
