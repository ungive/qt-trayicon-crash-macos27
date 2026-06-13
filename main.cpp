#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QStyle>
#include <QDebug>

static void createTestTrayIcon(QApplication &app)
{
    auto *tray = new QSystemTrayIcon(&app);

    QIcon icon = app.style()->standardIcon(QStyle::SP_ComputerIcon);
    tray->setIcon(icon);
    tray->setToolTip("Qt Tray Test");

    auto *menu = new QMenu();

    QAction *helloAction = menu->addAction("Hello");
    QObject::connect(helloAction, &QAction::triggered, [] {
        qDebug() << "Hello clicked";
    });

    menu->addSeparator();

    QAction *quitAction = menu->addAction("Quit");
    QObject::connect(quitAction, &QAction::triggered,
                     &app, &QApplication::quit);

    tray->setContextMenu(menu);

    QObject::connect(
        tray,
        &QSystemTrayIcon::activated,
        [](QSystemTrayIcon::ActivationReason reason)
        {
            qDebug() << "Tray activated:" << reason;
        });

    tray->show();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    createTestTrayIcon(app);

    return app.exec();
}
