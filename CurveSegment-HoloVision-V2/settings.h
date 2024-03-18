#pragma once

namespace settings
{
	inline constexpr int frameWidth = 615;
	inline constexpr int frameHeight = 432;
	inline constexpr int segmentLength = 64;
	inline constexpr float segmentThreshold = 0.3f; //The threshold that needs to be reached for a segment to be considered hologram
	inline constexpr int targetHoloCountPerVideo = 100;
	inline constexpr int targetNonHoloCountPerVideo = 100;
}