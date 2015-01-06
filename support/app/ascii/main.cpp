#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>

int main() {
    qDebug() << "Type the name of the file to write to:";
    QTextStream in(stdin);
    QFile out(in.readLine());

    if (!out.open(QIODevice::WriteOnly)) {
        qDebug() << "failed to open file";
        return 1;
    }

    qDebug() << "Input character codes (0...255), each on a new line; input \"q\" to quit:";

    while (true) {
        QString line = in.readLine();

        if (line == "q")
            return 0;

        bool ok = false;
        int code = line.toInt(&ok);

        if (!ok || (code < 0) || (code > 255)) {
            qDebug() << "wrong format";
        } else {
            out.write(QByteArray(1, code).constData());
        }
    }

//    return 0;
}
