#pragma once

#include <iostream>

using namespace std;
class S_Marker
{
public:
	bool marker_default = false;
	bool marker_clip = false;
	std::string marker_file = "";
	float marker_opacity = 1;
	float marker_fill_opacity = 1;
	COLORREF marker_stroke = RGB(0, 0, 0);
	float marker_stroke_width = 0.5;
	float marker_stroke_opacity = 1;
	std::string marker_placement = "point";
	std::string marker_multi_policy = "each";
	std::string marker_type = "ellipse";
	float marker_width = 10;
	float marker_height = 10;
	COLORREF marker_fill = RGB(0, 0, 255);
	bool allow_overlap = false;
	bool avoid_edges = false;
	bool ignore_placement = false;
	float marker_spacing = 100;
	float marker_max_error =0.2;
	std::string marker_transform = "none";
	float marker_simplify = 0.0;
	std::string marker_simplify_algorithm = "radial-distance";
	float marker_smooth = 0;
	std::string marker_geomtry_transform = "none";
	float marker_offset = 0;
	std::string marker_compop = "src - over";
	std::string marker_direction = "right";


};

