#ifndef GEOCORRECTCLIENT_H
#define GEOCORRECTCLIENT_H

#include <QObject>

class GDALDataset;

/// <summary>
/// Class GeocorrectClient.
/// </summary>
class GeocorrectClient : public QObject
{
    Q_OBJECT
    
public:
    GeocorrectClient( QObject *parent );
    ~GeocorrectClient();
    
public slots:
    void handleFilePath( QString srcFile, QString refFile, QString resultFile );
    void correct( GDALDataset *srcImg, GDALDataset *refImg, GDALDataset *resultImg );
private:
    QString srcFile;
    QString refFile;
    QString resultFile;
};

#endif // GEOCORRECTCLIENT_H
