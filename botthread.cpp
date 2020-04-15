#include "botthread.h"

#include <QDebug>
#include <QRandomGenerator>


static QStringList answers = {
    "Its so intresting with you!",
    "You are so cute!",
    "Tell me something more!",
    "Wooooow!... ",
    "I excited... >_<",
    "Nyan neko neko neko chan!",
    "I want to walk with you... And maybe I will kiss you!"
};

BotThread::BotThread(QObject *parent) :
    QThread(parent),
    m_curl(),
    m_bot("1087440270:AAFzhcWWWe6OmX45hN2ZSvWVAPChwjIU03g", m_curl),
    m_markup(std::make_shared<TgBot::InlineKeyboardMarkup>()),
    m_markdown(std::make_shared<TgBot::ReplyKeyboardMarkup>())
{
    auto button = std::make_shared<TgBot::InlineKeyboardButton>();

    button->text = "WoW!";
    button->callbackData = "sdsa1";


    auto button2  = std::make_shared<TgBot::InlineKeyboardButton>();
    button2->text  = "wooow";
    button2->callbackData = "sdsa2";


    auto button3  = std::make_shared<TgBot::InlineKeyboardButton>();
    button3->text  = "----> <----";
    button3->callbackData = "sdsa3";

    std::vector<TgBot::InlineKeyboardButton::Ptr> line1 = { button, button2 };
    std::vector<TgBot::InlineKeyboardButton::Ptr> line2 = { button3 };
    m_markup->inlineKeyboard.push_back(line1);
    m_markup->inlineKeyboard.push_back(line2);



    auto button4 = std::make_shared<TgBot::KeyboardButton>();

    button4->text = "WoW!";

    auto button5 = std::make_shared<TgBot::KeyboardButton>();

    button5->text = "Nice!";

    auto button6 = std::make_shared<TgBot::KeyboardButton>();

    button6->text = "Trolololo!";
//    button4->


    m_markdown->keyboard = {
        {button4, button5},
        {button6}
    };
    m_markdown->resizeKeyboard = true;


    m_bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr msg)
    {
        m_bot.getApi().sendMessage(msg->chat->id, "Privetick ;)", false, 0, m_markdown);
    });

    m_bot.getEvents().onCallbackQuery([/*this*/](const TgBot::CallbackQuery::Ptr& query)
    {
        qDebug() << "Got query";
        if (!query)
        {
            return;
        }
        qDebug() << "Query message:" << query->data.c_str();
    });

    m_bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr msg)
    {
        const auto & api = m_bot.getApi();
        auto messageText =  QString::fromLatin1(msg->text.c_str());

        qDebug() << messageText;

        if(messageText.contains("Hello") || messageText.contains("Hi")
                || messageText.contains("Greetings"))
        {
            api.sendMessage(msg->chat->id, "Hello my darling!! ^_^");
        }
        else if(messageText.contains("send photo"))
        {
            api.sendPhoto(msg->chat->id, "https://make.girls.moe/thumb.png");
            api.sendMessage(msg->chat->id, "How do I look, senpai? O_O");
        }
        else
        {
            int index = QRandomGenerator::securelySeeded().bounded(0,answers.size() -1);
            api.sendMessage(msg->chat->id, answers.at(index).toStdString());
        }
    });
}

void BotThread::run()
{
    try
    {

        TgBot::TgLongPoll lP(m_bot);

        while(true)
        {
            qDebug()<<"Bot is working may be";
            lP.start();
        }

    }
    catch(TgBot::TgException& e)
    {
        qDebug()<<"error: "<< e.what();
    }
}
