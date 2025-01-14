#pragma once

#ifndef VAPOURSYNTH_H
#define VAPOURSYNTH_H

#include <QString>

class VapourSynth {
protected:
	static QString RIFE(int, int, int, QString, QString, QString);
	static QString SRMD(int, int, int, int, QString);
	static QString RGB(QString, QString, QString);
	static QString ColorsInOut(QString, QString, QString, QString, QString, QString, QString);
	static QString ColorsOut(QString, QString, QString, QString);
	static QString SCDetect(QString);
	static QString Plugin(QString);
	static QString Input(QString, QString);
	static QString Include();
	static QString ConcludeClip();
	static QString NewLine();
};

#endif // !VAPOURSYNTH_H