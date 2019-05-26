#pragma once
#include "../Define/Stdafx.h"

extern bool bShow;
bool isOKK = 0;
float sliders;
bool EspTab = false;
bool AimTab = false;
bool OtherTab = false;
bool Info = false;

#pragma execution_character_set("utf-8")
bool show_app_TeleportManager = false;
#define Create_Thread(Function) CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Function, 0, 0, 0));

std::vector<std::string> split(const std::string &s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

static void ShowHelpMarker(const char* desc)
{
	ImGui::Text(XorString("(?)"));
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

static void ShowHelpMarkerToText(const char* caption, const char* desc)
{
	ImGui::Text(caption);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

int iTab;
void styler()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 3;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 3;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 20;
	style.GrabRounding = 1;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void RenderWindow()
{
	if (!bShow)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	styler();
	static ImVec4 color = ImColor(18, 221, 233, 255);
	ImVec4* colors = style.Colors;

	static bool alpha_preview = true;
	static bool alpha_half_preview = false;
	static bool options_menu = true;
	static bool hdr = false;

	ImGuiWindowFlags Flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
	ImGui::BeginMainMenuBar(), &bShow;
	{
		if (ImGui::BeginMenu(XorString(u8"�������� ����")))
		{
			ImGui::MenuItem((XorString(u8"������")), "", &EspTab);
			ImGui::MenuItem((XorString(u8"���")), "", &AimTab);
			ImGui::MenuItem((XorString(u8"�������������")), "", &OtherTab);
			ImGui::Separator();
			if (ImGui::MenuItem(XorString(u8"������� ��� �������")))
			{
				EspTab = false;
				AimTab = false;
				OtherTab = false;
			}
			ImGui::EndMenu();
		}
		ShowHelpMarkerToText(XorString(u8"����������"), XorString(u8"���������� �� ����������� ������� � ������ ��������� vk.com/rghack1 ��������-���������� ���� �� ������: HOME"));
		ImGui::EndMainMenuBar();
	}

	if (EspTab)
	{
		ImGui::Begin((XorString(u8"������")), nullptr, Flags);
		{
			static bool alpha_preview = true;
			static bool alpha_half_preview = false;
			static bool options_menu = true;
			static bool hdr = false;

			int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
			ImGui::Checkbox(XorString(u8"��� �������"), &Settings::ESP::EspSkeletenabled);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"��� �������"), &Settings::ESP::Esp2dBox);
			ImGui::Checkbox(XorString(u8"��� ����"), &Settings::ESP::EspNikname);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"��� ����"), &Settings::ESP::EspGranade);
			ImGui::PushItemWidth(150);
			ImGui::Separator();
			ImGui::ColorEdit4(XorString("�������##1"), (float*)&Settings::ESP::ColorSkeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);
			ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), XorString("���� ��������"));
			ImGui::SameLine(300);
			ImGui::ColorEdit4(XorString("�����##1"), (float*)&Settings::ESP::Color2Dboxx, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);
			ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), XorString("���� 2D Box"));
			ImGui::ColorEdit4(XorString("����##1"), (float*)&Settings::ESP::ColorNikname, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);
			ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), XorString("���� �����"));
			ImGui::SameLine(300);
			ImGui::PushItemWidth(150);
			const char* szColorSilhouettes = XorString(u8"Ƹ���� \0��������� \0���������� \0������� \0������� \0����� \0\0");
			ImGui::Combo(XorString(u8"���� ��������"), &Settings::ESP::SilhouettesColors, szColorSilhouettes);
			ImGui::NextColumn();
		}
		ImGui::End();
	}

	if (AimTab)
	{
		ImGui::Begin((XorString(u8"���")), nullptr, Flags);
		{
			ImGui::Checkbox(XorString(u8"�������� ���� ���"), &Settings::Aimbot::enabled);
			if (Settings::Aimbot::enabled)
			{
				ImGui::SameLine(300);
				ImGui::PushItemWidth(150);
				ImGui::Separator();
				ImGui::PushItemWidth(150);
				const char* szBone = XorString(u8"������ \0���� \0��� \0�� \0\0");
				ImGui::Combo(XorString(u8"����� �����"), &Settings::Aimbot::bones, szBone);
				ImGui::Checkbox(XorString(u8"�������� �� ������"), &Settings::Aimbot::turets);
				ImGui::SameLine(300);
				ImGui::Checkbox(XorString(u8"���������� ���� [ Capslock ]"), &Settings::Aimbot::capslock);
				ImGui::Separator();
				ImGui::Checkbox(XorString(u8"�������� ������"), &Settings::Aimbot::Fov::enabled);
				if (Settings::Aimbot::Fov::enabled)
				{
					ImGui::SliderFloat(XorString(u8"��������� �������"), &Settings::Aimbot::Fov::value, 0.f, 1000.f);
				}
			}
			ImGui::End();
		}
	}

	if (OtherTab)
	{
		ImGui::Begin((XorString(u8"�������������")), nullptr, Flags);
		{
			ImGui::PushItemWidth(200);
			ImGui::NextColumn();
			ImGui::Checkbox(XorString(u8"���� ������"), &Settings::Weapone::norecoil);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"���� �������"), &Settings::Weapone::noacuraty);
			ImGui::Checkbox(XorString(u8"���� ������"), &Settings::Weapone::noshoters);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"���� ����������� ������"), &Settings::Weapone::nosway);
			ImGui::Checkbox(XorString(u8"����������� �������"), &Settings::Weapone::unlimammo);
			ImGui::Separator();
			ImGui::Checkbox(XorString(u8"������� ������"), &Settings::Player::longslide);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"������ ��� ���������"), &Settings::Player::adjuster);
			ImGui::Checkbox(XorString(u8"�������� ������"), &Settings::Player::rotateshl);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"������ ������ �� ����������"), &Settings::Player::pickupwea);
			ImGui::Checkbox(XorString(u8"����-���"), &Settings::Player::afk);
			ImGui::SameLine(300);
			ImGui::Checkbox(XorString(u8"���� [V] (PVE)"), &Settings::Player::GrowthView);
			if (Settings::Player::GrowthView)
			{
				ImGui::SliderFloat(XorString(u8"��������� �����"), &Settings::Player::GrowthOptions, 0.f, 10.f);
			}
		}
		ImGui::End();
	}
	ImGui::Render();
}