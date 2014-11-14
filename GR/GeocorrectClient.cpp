#include "GeocorrectClient.h"

GeocorrectClient::GeocorrectClient( QObject *parent )
    : QObject( parent )
{

}

GeocorrectClient::~GeocorrectClient()
{

}

/// <summary>
/// Corrects the specified source img.
/// </summary>
/// <param name="srcImg">The source img.</param>
/// <param name="refImg">The reference img.</param>
/// <param name="resultImg">The result img.</param>
void GeocorrectClient::correct( GDALDataset *srcImg, GDALDataset *refImg, GDALDataset *resultImg )
{

}

void GeocorrectClient::handleFilePath( QString srcFile, QString refFile, QString resultFile )
{
    this->srcFile = srcFile;
    this->refFile = refFile;
    this->resultFile = resultFile;
}
