#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include "ChessPiece.hpp"
#include "ChessBoard.hpp"

static QObject *gameControllerSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    ChessBoard *controller = new ChessBoard();
    QThread* thread = new QThread();
    controller->moveToThread(thread);
    return controller;
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    qmlRegisterSingletonType<ChessBoard>("com.chess.controller", 1, 0, "GameController", gameControllerSingletonProvider);

    engine.load(url);

    return app.exec();
}
