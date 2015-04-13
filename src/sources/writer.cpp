#include "include/writer.h"

#include <QFile>
#include <QDebug>

#include "include/abstractdata.h"
#include "filechecker.h"

using namespace QtCSV;

// Write data to .csv file
// @input:
// - filePath - string with absolute path to csv file
// - data - not empty data that should be written to .csv file
// - separator - string or character separating columns
// - header - strings that will be written at the beginning of the file in
// one line. separator will be used as delimiter character.
// - footer - strings that will be written at the end of the file in
// one line. separator will be used as delimiter character.
// - mode - write mode of the file: rewrite file or append data to the end
// @output:
// - bool - True if data was written to the file, otherwise False
bool Writer::write(const QString &filePath, const AbstractData &data,
                   const QString &separator, const QStringList &header,
                   const QStringList &footer, const WriteMode &mode)
{
    if ( true == filePath.isEmpty() ||
         true == data.isEmpty() )
    {
        qDebug() << __func__ << "Error - invalid arguments";
        return false;
    }

    if ( false == CheckFile(filePath) )
    {
        qDebug() << __func__ << "Error - wrong file path/name:" << filePath;
        return false;
    }

    QFile csvFile;
    csvFile.setFileName(filePath);

    bool fileOpened = csvFile.open(GetMode(mode) | QIODevice::Text);
    if ( false == fileOpened )
    {
        qDebug() << __func__ << "Error - can't open file:" << filePath;
        return false;
    }

    QTextStream stream;
    stream.setDevice(&csvFile);

    if ( false == header.isEmpty() )
    {
        for ( const QString &str : header )
        {
            stream << str << separator;
        }

        stream << endl;
    }

    int rowsNum = data.getNumberOfRows();
    for (int i = 0; i < rowsNum; ++i)
    {
        QStringList rowValues = data.getRowValues(i);
        for ( QString &val : rowValues )
        {
            stream << val << separator;
        }

        stream << endl;
    }

    if ( false == footer.isEmpty() )
    {
        for ( const QString &str : footer )
        {
            stream << str << separator;
        }

        stream << endl;
    }

    csvFile.close();

    return true;
}

// Get QIODevice mode
// @input:
// - mode - write mode
// @output:
// - QIODevice::OpenMode - corresponding QIODevice::OpenMode
QIODevice::OpenMode Writer::GetMode(const Writer::WriteMode &mode)
{
    switch (mode)
    {
        case WriteMode::APPEND:
            return QIODevice::Append;
        case WriteMode::REWRITE:
        default:
            return QIODevice::WriteOnly;
    }

    return QIODevice::WriteOnly;
}
