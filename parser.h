#ifndef PARSER_H
#define PARSER_H

#include <QVector>
//class QVector;
//class RecordInfo;
class QXmlStreamReader;
#include "parser.h"


class Parser
{
public:
    Parser();
    static QVector<RecordInfo *> parseXml(QByteArray &data);
};

#endif // PARSER_H
