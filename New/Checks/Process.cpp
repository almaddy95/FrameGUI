#include "Checks.h"

/// <summary>
/// Checks to ensure that the audio codec is compatible with the selected output video container.
/// </summary>
/// <param name="format">The audio codec index.</param>
/// <param name="container">The output video container.</param>
/// <returns>True or false.</returns>
bool Checks::CheckAudioCompatability(int format, QString container) {
	bool result = true;

	switch (format) {
	case AAC:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case MP3:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case AC3:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case FLAC:
		if (container.contains(".mkv") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case VORBIS:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case OPUS:
		if (container.contains(".mp4") || container.contains(".mkv"))
			result = true;
		else
			result = false;
		break;
	case DTS:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov"))
			result = true;
		else
			result = false;
		break;
	case TRUEHD:
		if (container.contains(".mp4") || container.contains(".mkv"))
			result = true;
		else
			result = false;
		break;
	case EAC3:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov"))
			result = true;
		else
			result = false;
		break;
	case ALAC:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov"))
			result = true;
		else
			result = false;
		break;
	case WMA:
		if (container.contains(".mkv") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case PCM:
		if (container.contains(".mkv") || container.contains(".mov") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	case MP2:
		if (container.contains(".mp4") || container.contains(".mkv") || container.contains(".mov") || container.contains(".avi"))
			result = true;
		else
			result = false;
		break;
	}

	return result;
}

/// <summary>
/// Checks to ensure that the subtitle codec is compatible with the selected output container.
/// </summary>
/// <param name="format">The subtitle codec.</param>
/// <param name="container">The output video container.</param>
/// <returns>True or false.</returns>
bool Checks::CheckSubtitleCompatability(QString format, QString container) {
	bool result = false;

	if ((format.contains("subrip") || format.contains("srt")) && container.contains(".mkv")) {
		result = true;
		return result;
	}
	else
		result = false;
	if (format.contains("webvtt") && container.contains(".mkv")) {
		result = true;
		return result;
	}
	else
		result = false;
	if ((format.contains("ass") || format.contains("ssa")) && container.contains(".mkv")) {
		result = true;
		return result;
	}
	else
		result = false;
	if (format.contains("mov_text") && (container.contains(".mp4") || container.contains(".mov"))) {
		result = true;
		return result;
	}
	else
		result = false;

	return result;
}