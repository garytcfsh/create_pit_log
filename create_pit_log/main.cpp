#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <math.h>

#define PI 3.1415926

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString outPath = "E:\\toothpick\\program\\create_pit_log\\create_canister_log.txt";
    QFile fileOut( outPath);
    fileOut.open( QFile::WriteOnly|QFile::Text);
    QTextStream fileOutTextStream( &fileOut);


    double ttx[31], tty[31]; //transportTunnelX, transportTunnelY
    int No=1;
    QString cylinderName="canister_", CNN;

    ttx[0] = 192260;
    tty[0] = 2708667;

    //macro set
    fileOutTextStream << "BEGIN SetSeed" << endl;
    fileOutTextStream << '\t' << "Seed = 1567150308" << endl;
    fileOutTextStream << "END" << endl;
    fileOutTextStream << endl;


    //create pits and move their position
    for (int t=0; t<=30; t++)
    {
        double rad;
        rad = 60.0/180.0;
        ttx[t] = ttx[0] + t*40*cos(rad*PI);
        tty[t] = tty[0] + t*40*sin(rad*PI);

        for (int d=0; d<=33; d++) //right
        {
            double x, y;
            QString xx, yy;
            x = ttx[t] + 20.6*sin(rad*PI) + d*7.75*sin(rad*PI);
            y = tty[t] - 20.6*cos(rad*PI) - d*7.75*cos(rad*PI);
            xx.setNum(x, 'g', 7);
            yy.setNum(y, 'g', 9);

            CNN.setNum(No);
            cylinderName = "\"" + cylinderName + CNN + "\"";

            fileOutTextStream << "BEGIN CREATEREGION" << endl;
            fileOutTextStream << '\t' << "ObjectName = " << cylinderName << endl;
            fileOutTextStream << '\t' << "Type = \"Cylinder\"" << endl;
            fileOutTextStream << '\t' << "LockAxisVertical = 0" << endl;
            fileOutTextStream << '\t' << "CreateAround \"Cy\" 8 : -1" << endl;
            fileOutTextStream << "END" << endl;
            fileOutTextStream << endl;
            fileOutTextStream << "BEGIN EDITREGION" << endl;
            fileOutTextStream << '\t' << "ObjectName = " << cylinderName << endl;
            fileOutTextStream << '\t' << "Type = \"Cylinder\"" << endl;
            fileOutTextStream << '\t' << "Origin = " + xx + ", " + yy + ", " + "-502.5" << endl;
            fileOutTextStream << '\t' << "AxisOrientation trend = 0.0000 plunge = 90.0000" << endl;
            fileOutTextStream << '\t' << "AxisLength = 4.835" << endl;
            fileOutTextStream << '\t' << "Radius = 0.525" << endl;
            fileOutTextStream << '\t' << "Sides = 8" << endl;
            fileOutTextStream << "END" << endl;
            fileOutTextStream << endl;

            No++;
            cylinderName = "canister_";
        }

        for (int d=0; d<=33; d++)
        {
            double x, y;
            QString xx, yy;
            x = ttx[t] - 20.6*sin(rad*PI) - d*7.75*sin(rad*PI);
            y = tty[t] + 20.6*cos(rad*PI) + d*7.75*cos(rad*PI);
            xx.setNum(x, 'g', 7);
            yy.setNum(y, 'g', 9);

            CNN.setNum(No);
            cylinderName = "\"" + cylinderName + CNN + "\"";

            fileOutTextStream << "BEGIN CREATEREGION" << endl;
            fileOutTextStream << '\t' << "ObjectName = " << cylinderName << endl;
            fileOutTextStream << '\t' << "Type = \"Cylinder\"" << endl;
            fileOutTextStream << '\t' << "LockAxisVertical = 0" << endl;
            fileOutTextStream << '\t' << "CreateAround \"Cy\" 8 : -1" << endl;
            fileOutTextStream << "END" << endl;
            fileOutTextStream << endl;
            fileOutTextStream << "BEGIN EDITREGION" << endl;
            fileOutTextStream << '\t' << "ObjectName = " << cylinderName << endl;
            fileOutTextStream << '\t' << "Type = \"Cylinder\"" << endl;
            fileOutTextStream << '\t' << "Origin = " + xx + ", " + yy + ", " + "-502.5" << endl;
            fileOutTextStream << '\t' << "AxisOrientation trend = 0.0000 plunge = 90.0000" << endl;
            fileOutTextStream << '\t' << "AxisLength = 4.835" << endl;
            fileOutTextStream << '\t' << "Radius = 0.525" << endl;
            fileOutTextStream << '\t' << "Sides = 8" << endl;
            fileOutTextStream << "END" << endl;
            fileOutTextStream << endl;

            No++;
            cylinderName = "canister_";
        }
    }

    //move pits to newParent
    fileOutTextStream << "BEGIN ReparentObject" << endl;
    for (int i=1; i<=2108; i++)
    {
        CNN.setNum(i);
        cylinderName = "\"" + cylinderName + CNN + "\"";
        fileOutTextStream << '\t' << "Object = " + cylinderName << endl;
        cylinderName = "canister_";
    }
    fileOutTextStream << '\t' << "NewParent = \"Canister\"" << endl;
    fileOutTextStream << "END" << endl;

qDebug()<<"finish";


    return a.exec();
}
