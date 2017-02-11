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
	//-------------------------------------------------------------------------
	// ● VBinaryFileWriter
	//-------------------------------------------------------------------------
	class VBinaryFileWriter {
	private:
		FILE* f;
	public:
		VBinaryFileWriter(const char* filename);
		~VBinaryFileWriter();
		template <class T> void write_directly(T value) {
			fwrite(&value, sizeof(T), 1, f);
		}
		void write_i8(int8_t v);
		void write_i32(int32_t v);
		void write_i64(int64_t v);
		void write_u8(uint8_t v);
		void write_u32(uint32_t v);
		void write_u64(uint64_t v);
		void write_float(float v);
		void write_double(double v);
	};
}

// 自杀式命名空间
using namespace V;
