#include "VapourSynth.h"

/// <summary>
/// Configures RIFE in it's NCNN implementation.
/// </summary>
/// <param name="id">Sets the GPU id index to use.</param>
/// <param name="thread">Sets the number of GPU threads to use.</param>
/// <param name="tta">Enables test time augmentation for better interpolation quality.</param>
/// <param name="uhd">Enables or disabled UHD mode for better frame rendering.</param>
/// <param name="sc">Enables or disables scene change detection.</param>
/// <returns>String representation of the argument.</returns>
QString VapourSynth::RIFE(int multi, int id, int thread, QString tta, QString uhd, QString sc) {
	return QString("clip = core.rife.RIFE(clip, model=0, fps_num=%1, fps_den=1, gpu_id=%2, gpu_thread=%3, tta=%4, uhd=%5, sc=%6)\n\n").arg(multi).arg(id).arg(thread).arg(tta).arg(uhd).arg(sc);
}