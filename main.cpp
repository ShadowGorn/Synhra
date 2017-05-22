/*! \file main.cpp
 * Главный файл программы
 */

#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <QCoreApplication>
#include <QString>
#include <QMap>
#include <QVector>
#include <QTextStream>
#include <QFile>

/*! Перечисление типов ошибок.
 */
enum errorType
{
    noFileIn, //!< Нет имени входного файла
    noNameOut, //!< Нет имени выходного файла
    noExistFile, //!< Входного файла с указанным именем не существует
    noOpenFile, //!< Входной файл не удалось открыть
    noAction, //!< Отсутствие номера действия в соответствии режимов
    noMode, //!< В соответствии отсутствует описание режима
    duplicateAction, //!< В соответствии несколько раз содержится номер действия
    invalidChar, //!< В последовательность входит недопустимый символ
    noDescribeMode, //!< Имеется номер, для которого не описан режим
    noOpenMode //!< Имеется завершающий режим, не имеющий начала
};

/*!
 * \brief Описание ошибки
 */
struct error
{
    errorType type; //!<Тип ошибки
    int numLine; //!< Номер строки в которой произошла ошибка
};

/*!
 * \brief Функция записи ошибки в поток ошибок
 * \param [in] error Описание ошибки
 */
void qError(QString error)
{
    std::wcerr << error.toStdWString() << "\n";
}

/*!
 * \brief Функция проверяющая аргументы командной строки
 * \param [in] argc Кол-во аргументов
 * \param [in] argv Массив аргументов командной строки
 * \param [out] error Ошибка в результате проверки
 * \return Наличие ошибки
 */
bool checkArguments(int argc, char* argv[], error &error);
/*!
 * \brief Функция сопоставления режимов с действиями пользователя
 * \param [in] match Cоответствия действий с режимами
 * \param [in] chain Последовательность действий пользователя
 * \param [out] mappedModes Выходная последовательность переключений режимов
 */
void matchModes(const QMap<int, QString> &match, const QVector<int> &chain, QVector<QString> &mappedModes);
/*!
 * \brief Функция чтения текста из входного файла с соответствиями
 * \param [in] filename Имя входного файла с соответствиями
 * \param [out] matchList Соответствия действий с режимами
 * \param [out] error Ошибка
 * \return Наличие ошибки при чтении файла
 */
bool readMatch(const QString &filename, QStringList &matchList, error &error);
/*!
 * \brief Функция чтения текста из входных файлов
 * \param [in] filename Имя входного файла с последовательностью
 * \param [out] stringChain Последовательность действий
 * \param [out] error Ошибка
 * \return Наличие ошибки при чтении файла
 */
bool readChain(const QString &filename, QString &stringChain, error &error);
/*!
 * \brief Функция, переписывающая считанные данные файла в контейнер QMap
 * \param [in] matchList Соответствия, считанные из файла
 * \param [out] match Последовательность, записанная в контейнер
 * \return Успешность записи
 */
bool putToMap(QStringList &matchList, QMap<int, QString> &match);
/*!
 * \brief Функция, переписывающая считанные данные файла в контейнер QVector
 * \param [in] stringChain Последовательность действий, считанная из файла
 * \param [out] chain Последовательность, записанная в контейнер
 * \param [in] match Соответствия режимов и действий
 * \return Успешность записи
 */
bool putToVector(const QString &stringChain, QVector<int> &chain, const QMap<int, QString> &match);
/*!
 * \brief Функция проверки строки с соответствием действия и режима
 * \param [in] matchList Cоответствия, считанные из файла
 * \param [out] error Ошибка при записи
 * \return Наличие ошибки
 */
bool checkMatch(QString & matchList, error &error);
/*!
 * \brief Функция проверки строки с последовательностью действий
 * \param [in] stringChain Последовательность действий, считанная из файла
 * \param [out] error Ошибка при записи
 * \return Наличие ошибки
 */
bool checkChain(QString &stringChain, error &error);
/*!
 * \brief Функция, записывающая выходной текст в файл
 * \param [in] mappedModes Последовательность переключений режимов
 * \param [in] newfilename Имя создаваемого файла
 * \return Признак успешности записи данных в файл
 */
bool writeData(const QVector<QString> &mappedModes, const QString &newfilename);

/*!
 * \brief Главная функция программы
 * \param [in] argc Количество переданных аргументов командной строки
 * \param [in] argv Массив аргументов командной строки
 * \return 0-при успешном выполнении, 1-в противном случае
 *
 * Аргументы командной строки:
 * argv[0] - аргумент содержащий имя запускаемой программы;
 * argv[1] – аргумент содержащий имя первого исходного файла;
 * argv[2] – аргумент содержащий имя второго исходного файла;
 * argv[3] – аргумент содержащий имя выходного файла
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    _setmode(_fileno(stderr), _O_U8TEXT); // Режим вывода в stderr в кодировке UTF-8

    error error;
    if(!checkArguments(argc, argv, error))
    {
        QString errorDescription = "Ошибка параметров программы: Нет ";
        if(error.type == errorType::noFileIn)
        {
            errorDescription += "входного ";
        }
        else if(error.type == errorType::noNameOut)
        {
            errorDescription += "выходного ";
        }
        errorDescription += "файла";
        qError(errorDescription);
        return 1;
    }

    QStringList matchList;
    if(!readMatch(argv[1], matchList, error))
    {
        QString errorDescription = "Ошибка параметров программы: Файл с соответствиями ";
        if(error.type == errorType::noExistFile)
        {
            errorDescription += "не существует";
        }
        else if(error.type == errorType::noOpenFile)
        {
            errorDescription += "не получается открыть";
        }
        qError(errorDescription);
        return 1;
    }

    QString stringChain;
    if(!readChain(argv[2], stringChain, error))
    {
        QString errorDescription = "Ошибка параметров программы: Файл c последовательностью действий ";
        if(error.type == errorType::noExistFile)
        {
            errorDescription += "не существует";
        }
        else if(error.type == errorType::noOpenFile)
        {
            errorDescription += "не получается открыть";
        }
        qError(errorDescription);
        return 1;
    }

    QMap<int, QString> match;
    putToMap(matchList, match);

    QVector<int> chain;
    putToVector(stringChain, chain, match);

    QVector<QString> mappedModes;
    matchModes(match, chain, mappedModes);

    writeData(mappedModes,argv[3]);
    return 0;
}

bool checkArguments(int argc, char* argv[], error &error)
{
    if(argc < 3) // Нет одного и двух входных файлов
    {
        error.type = errorType::noFileIn;
        return false;
    }
    else if(argc < 4) // Нет выходного файла
    {
        error.type = errorType::noNameOut;
        return false;
    }
    return true;
}

void matchModes(const QMap<int, QString> &match, const QVector<int> &chain, QVector<QString> &mappedModes)
{
    QVector<QString> openModes; // Список открытых режимов в порядке открытия
    QString startMode = ""; // Начальный режим, в который приходим по завершении всех режимов
    for(QVector<int>::const_iterator chainIt = chain.begin(); chainIt != chain.end(); chainIt++)
    {
        int action = *chainIt;
        QString mode = match[abs(action)]; // Название режима

        if(startMode == "") // По умолчанию первое действие становится начальным
        {
            startMode = mode;
        }

        if(action > 0) // Начало нового режима
        {
            openModes.push_back(mode);
            mappedModes.push_back(QString::number(action) + "->" + mode);
        }
        else
        {
            openModes.removeAt(openModes.lastIndexOf(mode)); // Удалим последний открытый режим такого типа
            if(!openModes.empty())
            {
                mappedModes.push_back(QString::number(action) + "->" + openModes.back()); // Перейдем в последний открытый режим
            }
            else
            {
                mappedModes.push_back(QString::number(action) + "->" + startMode); // Перейдем в стартовый режим
            }
        }
    }
}

bool readMatch(const QString &filename, QStringList &matchList, error &error)
{
    QFile matchFile(filename);
    if(!matchFile.exists())
    {
        error.type = errorType::noExistFile;
        return false;
    }

    if (!matchFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error.type = errorType::noOpenFile;
        return false;
    }

    QTextStream in(&matchFile);
    while (!in.atEnd())
    {
        matchList.append(in.readLine());
    }
    return true;
}

bool readChain(const QString &filename, QString &stringChain, error &error)
{
    QFile chainFile(filename);
    if(!chainFile.exists())
    {
        error.type = errorType::noExistFile;
        return false;
    }

    if (!chainFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        error.type = errorType::noOpenFile;
        return false;
    }

    QTextStream in(&chainFile);
    while (!in.atEnd())
    {
        QString temp = " " + in.readLine();
        stringChain += temp;
    }
    return true;
}

bool putToMap(QStringList &matchList, QMap<int, QString> &match)
{
    bool wasError = false;
    for(QStringList::iterator it = matchList.begin(); it != matchList.end(); ++it)
    {
        error matchError;
        if(checkMatch(*it,matchError))
        {
            QTextStream in(&(*it));
            int action;
            in >> action;
            QString mode;
            in.skipWhiteSpace();
            mode = in.readLine();
            if(match.contains(action))
            {
                wasError = true;
                QString errorDescription = "Файл содержит некорректные данные: в строке " + QString::number((it - matchList.begin()) + 1) + " дублируется ";
                if(matchError.type == errorType::duplicateAction)
                {
                    errorDescription += "номер действия";
                }
                qError(errorDescription);
            }
            else
            {
                match.insert(action, mode);
            }
        }
        else
        {
            wasError = true;
            QString errorDescription = "Файл содержит некорректные данные: в строке " + QString::number((it - matchList.begin()) + 1) + " отсутствует ";
            if(matchError.type == errorType::noAction)
            {
                errorDescription += "номер действия";
            }
            else if(matchError.type == errorType::noMode)
            {
                errorDescription += "описание режима";
            }
            qError(errorDescription);
        }
    }
    return !wasError;
}

bool putToVector(const QString &stringChain, QVector<int> &chain, const QMap<int, QString> &match)
{
    error chainError;
    QString copyStringChain = stringChain;
    if(!checkChain(copyStringChain,chainError))
    {
        QString errorDescription = "Файл содержит некорректные данные: в последовательность в столбце ";
        errorDescription += QString::number(chainError.numLine);
        if(chainError.type == errorType::invalidChar)
        {
            errorDescription += " входит символ, не являющийся целым числом, пробелом или минусом";
        }
        qError(errorDescription);
        return false;
    }

    QTextStream in(&copyStringChain);
    QVector<int> copy;
    while(!in.atEnd())
    {
        int action;
        in >> action;
        chain.push_back(action);
        copy.push_back(action);
    }

    bool wasError = false;
    int deletedCount = 0;
    for(int i = 0; i < chain.length(); ++i)
    {
        if(!match.contains(abs(chain[i])))
        {
            wasError = true;
            QString errorDescription = "Файл содержит некорректные данные: последовательность содержит номер, которому не соответствует режим под номером ";
            errorDescription += QString::number(chain[i]);
            qError(errorDescription);
        }
        else
        {
            if(chain[i] < 0)
            {
                int pos = openModes.lastIndexOf(-chain[i],i); // Найдем индекс последнего соответствующего открывающего действия
                if(pos == -1)
                {
                    wasError = true;
                    QString errorDescription = "Файл содержит некорректные данные: последовательность содержит под номером ";
                    errorDescription += QString::number(i+1);
                    errorDescription += " завершающее действие ";
                    errorDescription += QString::number(-chain[i]);
                    errorDescription += ", не имеющее начального действия перед собой";
                    qError(errorDescription);
                }
                else
                {
                    copy.removeAt(pos); // Удалим открывающее действие
                    deletedCount++;
                }
                copy.removeAt(i); // Удалим закрывающее действие
                deletedCount++;
            }
        }
    }
    return !wasError;
}

bool checkMatch(QString & matchList, error &error)
{
    QTextStream in(&matchList);
    int action;
    in >> action;
    if(in.status() != QTextStream::Ok)
    {
        error.type = errorType::noAction;
        return false;
    }
    QString mode;
    mode = in.readLine();
    if(in.status() != QTextStream::Ok || mode.trimmed().length() == 0)
    {
        error.type = errorType::noMode;
        return false;
    }
    return true;
}

bool checkChain(QString &stringChain, error &error)
{
    for(int i=0; i < stringChain.length(); ++i)
    {
        bool good_symbol = stringChain[i].isDigit() || stringChain[i] == '-' || stringChain[i].isSpace();
        bool digit_before_minus = i > 0 && stringChain[i] == '-' && stringChain[i-1].isDigit();
        if(!good_symbol || digit_before_minus)
        {
            error.type = errorType::invalidChar;
            error.numLine = i + 1;
            return false;
        }
    }
    return true;
}

bool writeData(const QVector<QString> &mappedModes, const QString &newfilename)
{
    QFile file(newfilename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    for(QVector<QString>::const_iterator it = mappedModes.begin(); it != mappedModes.end(); ++it)
    {
        out << *it << "\n";
        if(out.status() != QTextStream::Ok)
        {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}
