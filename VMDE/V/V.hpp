//=============================================================================
// ■ V.hpp
//-----------------------------------------------------------------------------
//   注意：这个目录里的很多文件都是模板类，它们有单独的头文件。
//=============================================================================

namespace V {
	//-------------------------------------------------------------------------
	// ● 模板类
	//-------------------------------------------------------------------------
	#include "VMath.hpp"
	#include "VRingBuffer.hpp"
	//-------------------------------------------------------------------------
	// ● VBinaryFileReader
	//-------------------------------------------------------------------------
	class VBinaryFileReader {
	private:
		FILE* f;
	public:
		VBinaryFileReader(const char* filename);
		~VBinaryFileReader();
		int8_t read_i8();
		int32_t read_i32();
		int64_t read_i64();
		uint8_t read_u8();
		uint32_t read_u32();
		uint64_t read_u64();
		float read_float();
		double read_double();
		template <class T> T read_directly() {
			T r;
			fread(&r, sizeof(T), 1, f);
			return r;
		}
	};
}

// 自杀式命名空间
using namespace V;
