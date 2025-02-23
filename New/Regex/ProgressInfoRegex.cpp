#include "ProgressInfoRegex.h"

QList<QRegularExpression> ProgressInfoRegex::Indexer;

void ProgressInfoRegex::SetupPatterns() {
	Indexer << QRegularExpression("frame=\\s*([0-9]*)");
	Indexer << QRegularExpression("fps=\\s*([0-9]*\\.?[0-9]?)");
	Indexer << QRegularExpression("bitrate=\\s*([0-9]*\\.?[0-9]?)kbits/s");
	Indexer << QRegularExpression("time=\\s*([0-9]*):([0-9]*):([0-9]*)\\.([0-9]*)");
}

bool ProgressInfoRegex::ProgressRegex(QString output, QTime totalDuration, int totalFrames, QElapsedTimer timer, QTime pause) {
	if (Indexer.isEmpty())
		SetupPatterns();

	QRegularExpressionMatch matchFrames = Indexer.at(GetInfo::Frame).match(output);
	QRegularExpressionMatch matchFps = Indexer.at(GetInfo::Fps).match(output);
	QRegularExpressionMatch matchBitrate = Indexer.at(GetInfo::Bitrate).match(output);
	QRegularExpressionMatch matchTimeProcessed = Indexer.at(GetInfo::Time).match(output);

	int frames;
	QString fps, bitrate;
	QTime timeProcessed;

	if (!matchFrames.hasMatch() && !matchFps.hasMatch() && !matchBitrate.hasMatch() && !matchTimeProcessed.hasMatch())
		return false;
	else {
		frames = matchFrames.captured(1).toInt();
		fps = matchFps.captured(1);
		bitrate = matchBitrate.captured(1);
		timeProcessed = QTime(matchTimeProcessed.captured(1).toInt(), matchTimeProcessed.captured(2).toInt(), matchTimeProcessed.captured(3).toInt(),
			QString(matchTimeProcessed.captured(4) + "0").toInt());

		int mSecondsProcessed = QTime(0, 0, 0, 0).msecsTo(timeProcessed);
		int mSecondsTotal = QTime(0, 0, 0, 0).msecsTo(totalDuration);

		double percentage = ceil(static_cast<double>(mSecondsProcessed) / mSecondsTotal * 10000.0) / 100.0;

		int elapsed = (timer.elapsed() + QTime(0, 0, 0, 0).msecsTo(pause)) / 1000;

		int framesLeft = totalFrames - frames;
		double timeLeft = framesLeft * (static_cast<double>(elapsed) / frames);

		int seconds = ((int)timeLeft % 60);
		timeLeft /= 60;
		int minutes = ((int)timeLeft % 60);
		timeLeft /= 60;
		int hours = ((int)timeLeft);

		if (seconds < 0)
			seconds = 0;
		if (minutes < 0)
			minutes = 0;
		if (hours < 0)
			hours = 0;

		if (percentage > 100)
			percentage = 100;

		QTime qTimeLeft = QTime(hours, minutes, seconds);

		int sec = (int)(elapsed % 60);
		elapsed /= 60;
		int min = (int)(elapsed % 60);
		elapsed /= 60;
		int hr = (int)(elapsed);

		QTime timeElapsed = QTime(hr, min, sec);

		if (bitrate.isEmpty())
			bitrate = QString("0.0");
		if (fps.isEmpty())
			fps = QString("0.0");

#ifdef PROGRESSINFO_H
		ProgressInfo::SetTimeLeft(qTimeLeft);
		ProgressInfo::SetTimeElapsed(timeElapsed);
		ProgressInfo::SetProcessedFrames(frames);
		ProgressInfo::SetTotalFrames(totalFrames);
		ProgressInfo::SetTime(timeProcessed);
		ProgressInfo::SetFps(fps);
		ProgressInfo::SetBitrate(bitrate);
		ProgressInfo::SetPercentage(percentage);
#endif // PROGRESSINFO_H

		return true;
	}
}