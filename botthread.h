#ifndef BOTTHREAD_H
#define BOTTHREAD_H

#include <QThread>

#include <tgbot/tgbot.h>
#include <tgbot/types/InlineKeyboardButton.h>
#include <tgbot/types/InlineKeyboardMarkup.h>
#include <tgbot/types/ReplyKeyboardMarkup.h>

class BotThread : public QThread
{
    Q_OBJECT
public:
    explicit BotThread(QObject* parent = nullptr);

    // QThread interface
protected:
    void run() override;

private:
    TgBot::CurlHttpClient m_curl;
    TgBot::Bot m_bot;
    TgBot::InlineKeyboardMarkup::Ptr m_markup;
    TgBot::ReplyKeyboardMarkup::Ptr m_markdown;
};

#endif // BOTTHREAD_H
