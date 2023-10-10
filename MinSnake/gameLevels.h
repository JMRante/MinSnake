#pragma once
#include <vector>
#include "gameState.h"

// 023C40 C3979F 0AD3FF 2,60,64 195,151,159 10,211,255
// 38686A A3B4A2 E1C35F 56,104,106 163,180,162 225,195,95
// 91818A EBDCCB B2A3B5 145,129,138 235,220,203 178,163,181
// 14281D F1F5F2 355834 20,40,29 241,245,242 53,88,52
// 37000A 7E007B B3C2F2 55,0,10 126,0,123 179,194,242
// 
// 53131E B5D6B2 FFFACC 83,19,30 181,214,178 255,250,204
// 736CED FEF9FF D4C1EC 115,108,237 254,249,255 212,193,236
// 686963 DB5461 E3F2FD 104,105,99 219,84,97 227,242,253
// 4A314D 1A090D ACE894 74,49,77 26,9,13 172,232,148
// 1C2321 7D98A1 A9B4C2 28,35,33 125,152,161 169,180,194
//
// 58355E CFFFB0 E03616 88,53,94 207,255,176 224,54,22
// A30B37 FCFCFF C6C8EE 163,11,55 252,252,255 198,200,238
// 227C9D FFCB77 FE6D73 34,124,157 255,203,119 254,109,115
// 1F2232 BC9EC1 E3BAC6 31,34,50 188,158,193 227,186,198
// 45462A DC851F FFA737 69,70,42 220,133,31 255,167,55
//
// 2D080A 130303 F5853F 45,8,10 19,3,3 245,133,63
// 040F0F 2D3A3A FCFFFC 4,15,15 45,58,58 252,255,252
// 533745 9D9171 AB4E68 83,55,69 157,145,113 171,78,104
// 2D3142 EAE8FF B0D7FF 45,49,66 234,232,255 176,215,255
// 475B5A A3A9AA 52D1DC 71,91,90 163,169,170 82,209,220

vector<GameState> levels = {
	{
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		},
		{ 2, 60, 64, 255 },
		{ 195, 151, 159, 255 },
		{ 10, 211, 255, 255 },
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	},
	{
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		},
		{ 2, 60, 64, 255 },
		{ 195, 151, 159, 255 },
		{ 10, 211, 255, 255 },
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	},
	{
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
			1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
			1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		},
		{ 2, 60, 64, 255 },
		{ 195, 151, 159, 255 },
		{ 10, 211, 255, 255 },
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	},
	{
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		},
		{ 2, 60, 64, 255 },
		{ 195, 151, 159, 255 },
		{ 10, 211, 255, 255 },
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	},
	{
		{
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		},
		{ 2, 60, 64, 255 },
		{ 195, 151, 159, 255 },
		{ 10, 211, 255, 255 },
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	}
};