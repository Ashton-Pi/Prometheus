#pragma once
#include "entities.h"
#include "SDK.h"
#include "singleton.hpp"

class misc
	: public singleton<misc>
{
public:
	void OnCreateMove(CInput::CUserCmd *cmd, C_BaseEntity *local);
	void logsrun();
	void blockbot(CInput::CUserCmd * m_pcmd);
	void ChatSpammer();
	static void AutoStrafe(CInput::CUserCmd *cmd, C_BaseEntity *local, QAngle oldangles);
	
	static Vector RotatePoint(Vector EntityPos, Vector LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck)
	{
		float r_1, r_2;
		float x_1, y_1;

		r_1 = -(EntityPos.y - LocalPlayerPos.y);
		r_2 = EntityPos.x - LocalPlayerPos.x;
		float Yaw = angle - 90.0f;

		float yawToRadian = Yaw * (float)(M_PI / 180.0F);
		x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
		y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

		*viewCheck = y_1 < 0;

		x_1 *= zoom;
		y_1 *= zoom;

		int sizX = sizeX / 2;
		int sizY = sizeY / 2;

		x_1 += sizX;
		y_1 += sizY;

		if (x_1 < 5)
			x_1 = 5;

		if (x_1 > sizeX - 5)
			x_1 = sizeX - 5;

		if (y_1 < 5)
			y_1 = 5;

		if (y_1 > sizeY - 5)
			y_1 = sizeY - 5;


		x_1 += posX;
		y_1 += posY;


		return Vector(x_1, y_1, 0);
	}
	
};
template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

inline float bitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}


inline float FloatNegate(float f)
{
	return bitsToFloat(FloatBits(f) ^ 0x80000000);
}

inline void SetName(const char* new_name)
{
	static auto name = g_CVar->FindVar("name");

	name->SetValue(new_name);
	*reinterpret_cast<int*>(uintptr_t(&name->fnChangeCallback) + 0xC) = 0;
}
inline void setclantag(const char* tag)
{
	static auto ClanTagOffset = U::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", "xxxxxxxxx");
	if (ClanTagOffset)
	{
		auto tag_ = std::string(tag);
		if (strlen(tag) > 0) {
			auto newline = tag_.find("\\n");
			auto tab = tag_.find("\\t");
			if (newline != std::string::npos) {
				tag_.replace(newline, newline + 2, "\n");
			}
			if (tab != std::string::npos) {
				tag_.replace(tab, tab + 2, "\t");
			}
		}
		static auto dankesttSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(ClanTagOffset);
		dankesttSetClanTag(tag_.data(), tag_.data());
	}
}
inline void RankReveal(CInput::CUserCmd* cmd)
{
	if (cmd->buttons & IN_SCORE && g_Options.Misc.ServerRankRevealAll)
	{
		static auto ServerRankRevealAll = (bool(__cdecl*)(int*))((PDWORD)U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????"));
		if (g_Options.Misc.ServerRankRevealAll)
		{
			static int fArray[3] = { 0,0,0 };
			ServerRankRevealAll(fArray);
		}
	}
}