#ifndef UTILSETTING_H
#define UTILSETTING_H

#include <QVariant>
#include <QString>
#include <QPoint>
#include <QJsonObject>


class ConfigSetting {
public:
   static bool writeValue(const QString& path, const QString& group, const QString& user_key, const QVariant &value);
   static int ReadInt(const QString& path, const QString& group, const QString& user_key, const int& defaultValue);
   static QString ReadString(const QString& path, const QString& group, const QString& user_key, const QString& defaultValue);
};

#define PATH_OUT		"path_out"
#define CAPTHER_TIME		"Screenshot_time"

#define GROUP_DEFAULT           "default"
#define DEL_FILE_LIST		"del_file_list"
#define PATH_IN		"path_in"
#define PATH_OUT		"path_out"


#define SKU		"SKU"
#define PUBLISHER	"publisher"
#define BOOK_NAME		"book_name"
#define SUB_BOOK_NAME		"sub_book_name"
#define CREATOR1		"creator1"
#define CREATOR2		"creator2"
#define TRANSLATOR		"translator"
#define IDENTIFIER		"identifier"
#define DATE		"Date"

#endif // UTILSETTING_H
