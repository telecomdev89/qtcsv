#ifndef QTCSVREADER_H
#define QTCSVREADER_H

#include <QList>
#include <QStringList>

#include "separator.h"
#include "data.h"
#include "qtcsv_global.h"

namespace QtCSV
{
	class QTCSVSHARED_EXPORT Reader
	{
	public:
		// Read .csv file to QList<QStringList>
		static QList<QStringList> readToList(const QString &filePath,
								const Separator &separator = Separator::COMMA);

		// Read .csv file to QList<QStringList>
		static QList<QStringList> readToList(const QString &filePath,
									   const QString &separator = ",");

		// Read .csv file to QCSVData
		static Data readToData(const QString &filePath,
							 const QString &separator = ",");
	};
}

#endif // QTCSVREADER_H
