//=============================================================================
// ■ channel_triangle.cpp
//-----------------------------------------------------------------------------
//   三角波。
//=============================================================================

#include "../global.hpp"

namespace Audio {
	//-------------------------------------------------------------------------
	// ● 构造
	//    freq : 频率（Hz）
	//-------------------------------------------------------------------------
	Channel_Triangle::Channel_Triangle(float freq) {
		value = .0f;
		delta = 2.0f / ((float) AUDIO_SAMPLE_RATE / freq / 2);
	}
	//-------------------------------------------------------------------------
	// ● 填充缓冲区
	//-------------------------------------------------------------------------
	void Channel_Triangle::fill(float* buf, unsigned long n) {
		while (n) {
			float v = next();
			FEED_AUDIO_DATA(buf, v);
			n--;
		}
	}
	//-------------------------------------------------------------------------
	// ● 计算下一个值使输出呈三角波形
	//-------------------------------------------------------------------------
	float Channel_Triangle::next() {
		value += delta;
		if (value > 1.0f) {
			value = 2.0f - value;
			delta = -delta;
		} else if (value < -1.0f) {
			value = -2.0f - value;
			delta = -delta;
		}
		return value;
	}
}
