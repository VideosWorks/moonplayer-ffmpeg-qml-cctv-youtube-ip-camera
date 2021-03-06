#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
class QLocalServer;
class QLocalSocket;

/* MacOS handles file opening in a different way.
 * It doesn't use arguments, but FileOpenEvent.
 */

class Application : public QApplication
{
public:
    Application(int &argc, char **argv);
    virtual ~Application();
    bool parseArgs(void);
    
protected:
    bool event(QEvent *e);

private:
    
    void onNewConnection(void);
    int m_argc;
    char **m_argv;
    QLocalServer *m_server;
    QLocalSocket *m_client;
    QStringList m_files;
    bool m_isLocalFiles;
};

#endif // APPLICATION_H
