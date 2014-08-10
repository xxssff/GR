#ifndef CLASSIFICATIONCLIENT_H
#define CLASSIFICATIONCLIENT_H

#include <QObject>
#include <QtCore/QThread>

class ClassificationAlg;

class ClassificationClient : public QThread
{
    Q_OBJECT
    
public:
    ClassificationClient( QObject *parent );
    ~ClassificationClient();
    
    void run();
    
private:
    ClassificationAlg *client;
};

#endif // CLASSIFICATIONCLIENT_H
