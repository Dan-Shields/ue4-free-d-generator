// Copyright Epic Games, Inc. All Rights Reserved.

#include "FreeDGeneratorBPLibrary.h"
#include "FreeDGenerator.h"

UFreeDGeneratorBPLibrary::UFreeDGeneratorBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

TArray<uint8> UFreeDGeneratorBPLibrary::CreateFreeDPacket(FVector position, FRotator rotation) {
	TArray<uint8> arr = TArray<uint8>();
	arr.SetNumZeroed(29);

	// msg type
	arr[0] = 0xD1; // 11010001

	// camera id
	arr[1] = 0xaa; // 10101010

	// Pan
	// See appendix B of the vinten radamac FreeD manual
	// The FreeD protocol wants a 24 bit signed int, we use the top 24 bits of a 32bit int by multiplying by 256 (lowest byte = 0x00)
	int32 pan = rotation.Yaw * 32768 * 256;

	// shift each byte of the above int to uint bytes
	arr[2] = pan >> 24;
	arr[3] = pan >> 16;
	arr[4] = pan >> 8;

	int32 tilt = rotation.Pitch * 32768 * 256;

	// Tilt
	arr[5] = tilt >> 24;
	arr[6] = tilt >> 16;
	arr[7] = tilt >> 8;

	int32 roll = rotation.Roll * 32768 * 256;

	// Roll
	arr[8] = roll >> 24;
	arr[9] = roll >> 16;
	arr[10] = roll >> 8;

	// FreeD specifies positions should be signed ints with an increment of 1/64mm
	int32 xPos = position.X * 1000 * 64 * 256;

	// X Pos
	arr[11] = xPos >> 24;
	arr[12] = xPos >> 16;
	arr[13] = xPos >> 8;

	int32 yPos = position.Y * 1000 * 64 * 256;

	// Y Pos
	arr[14] = yPos >> 24;
	arr[15] = yPos >> 16;
	arr[16] = yPos >> 8;

	int32 zPos = position.Z * 1000 * 64 * 256;

	// Z pos
	arr[17] = zPos >> 24;
	arr[18] = zPos >> 16;
	arr[19] = zPos >> 8;

	// Zoom
	arr[20] = 0x00;
	arr[21] = 0x00;
	arr[22] = 0x00;

	// Focus
	arr[23] = 0x00;
	arr[24] = 0x00;
	arr[25] = 0x00;

	// bytes 26 & 27 are spare

	// checksm
	char chk = 0x40;
	for (int i = 0; i < 28; i++) {
		chk -= arr[i];
	}
	arr[28] = chk;

	return arr;
}
