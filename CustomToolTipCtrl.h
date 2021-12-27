#pragma once

// CCustomToolTipCtrl
#include <iostream>
#include <map>
struct TooltipInfo
{
public:
	std::string T_Content;
	std::string T_Code;
	TooltipInfo(std::string code, std::string content)
	{
		T_Code = code; T_Content = content;
	}
};
//std::string ConvertCString2String(CString& cstr)
//{
//	std::string str = CW2A(cstr);
//	return str;
//}
class CCustomToolTipCtrl : public CBCGPToolTipCtrl
{
	DECLARE_DYNAMIC(CCustomToolTipCtrl)

public:
	CCustomToolTipCtrl();
	virtual ~CCustomToolTipCtrl();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	int						m_nCurrID;
	std::map<std::string, std::string>	m_MapTooltip_Doc;
	std::map<std::string, std::string>	m_MapTooltip_Default;
public:
	afx_msg void OnTtnTooltipShow(NMHDR* pNMHDR, LRESULT* pResult);
	int CreateDatabaseTooltip();
	BOOL ReadTooltipSqlite(CString path);
	std::string tooltip_polygon_default = "Allows omitting a polygon symbolizer"
		" rule or emitting it with default values."
		"\ncss: polygon"
		"\ntype[2]: auto or none";
	std::string tooltip_polygon_fill ="Fill color to assign to a polygon."
		"\n\ndefault-meaning: Gray and fully opaque (alpha = 1),"
		" same as rgb(128,128,128) or rgba(128,128,128,1)."
		"\n\ndefault-value: rgba(128,128,128,1)"
		"\ntype: color"
		"\ncss: polygon-fill";
	std::string tooltip_polygon_fill_opacity = "The opacity of the polygon."
		"\n\ndefault-meaning: Color is fully opaque."
		"\ntype: float"
		"\ndefault-value: 1";
	std::string tooltip_polygon_gamma = "Level of antialiasing of polygon edges."
		"\n\ndefault-meaning: Fully antialiased."
		"\ndefault-value: 1"
		"\ntype: float";
	std::string tooltip_polygon_gamma_method = 
		"An Antigrain Geometry specific rendering"
		" hint to control the quality of antialiasing."
		" Under the hood in Mapnik this method is"
		" used in combination with the 'gamma' value (which defaults to 1)."
		" The methods are in the AGG source at"
		" https://github.com/mapnik/mapnik/blob/master/deps/agg/include/agg_gamma_functions."
		" \n\ndefault-meaning: pow(x,gamma) is used to calculate pixel gamma,"
		" which produces slightly smoother line and polygon antialiasing than the 'linear' method,"
		" while other methods are usually only used to disable AA."
		"\ndefault-value: power"
		"\ntype[5]: 0: power,1: linear, 2: none, 3: threshold, 4: multiply";
	std::string tooltip_polygon_clip = "Turning on clipping can help performance "
		"in the case that the boundaries of the geometry extend outside of tile extents."
		" But clipping can result in undesirable rendering artifacts in rare cases."
		"\n\ndefault-meaning: The geometry will not be clipped to map bounds before rendering."
		"\ntype: boolean"
		"\ndefault-value: false";
	std::string tooltip_polygon_simplify ="Simplify geometries by the given tolerance."
		"\ncss: polygon-simplify"
		"\n\ndefault-meaning: geometry will not be simplified."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_polygon_simplify_algorithm = "Simplify geometries by the given algorithm."
		"\n\ndefault-meaning: The geometry will be simplified using the radial distance algorithm."
		"\ntype: 0	:	radial-distance, 1:	zhao - saalfeld, 2: visvalingam - whyatt,3 : douglas - peucker"
		"\ndefault-value: radial-distance";
	std::string tooltip_polygon_geometry_transform = "Transform polygon geometry with specified function."
		"\n\ndefault-meaning: The geometry will not be transformed."
		"\ntype: functions"
		"\ndefault-value: none";
	std::string tooltip_polygon_smooth ="Smooths out geometry angles."
		" 0 is no smoothing, 1 is fully smoothed."
		" Values greater than 1 will produce wild, looping geometries."
		"\n\ndefault-meaning: No smoothing."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_polygon_compop ="Composite operation."
		" This defines how this symbolizer should behave relative to"
		" symbolizers atop or below it."
		"\n\ndefault-meaning: Add the current symbolizer"
		" on top of other symbolizer."
		"\ntype[37]"
		"\ndefault-value: src-over";
	std::string tooltip_polygonpattern_default = "Allows omitting a polygon pattern"
		" symbolizer rule or emitting it with default values."
		"\n\ncss: polygon-pattern";
	std::string tooltip_polygonpattern_file = "Image to use as a repeated pattern fill within a polygon."
		" Accepted formats: svg, jpg, png, tiff, and webp."
		"\ntype: uri"
		"\ndefault-value: none"
		"\n\ncss: polygon-pattern-file";
	std::string tooltip_polygonpattern_alignment = "Specify whether to align pattern fills to "
		"the layer's geometry (local) or to the map (global)."
		"\n\ndefault-meaning: Patterns will be aligned to the map"
		" (or tile boundaries) when being repeated across polygons."
		" This is ideal for seamless patterns in tiled rendering."
		"\n\ntype[2]: global or local"
		"\ndefault-value: global"
		"\n\ncss: polygon-pattern-alignment";
	std::string tooltip_polygonpattern_gamma = "Level of antialiasing of polygon pattern edges."
		"\n\ndefault-meaning: Fully antialiased."
		"\ncss: polygon-pattern-gamma"
		"\ntype: float"
		"\nrange: 0-1"
		"\ndefault-value: 1";
	std::string tooltip_polygonpattern_opacity = "Apply an opacity level to the image used for the pattern."
		"\n\ndefault-meaning: The image is rendered without modifications."
		"\ncss: polygon-pattern-opacity"
		"\ntype: float"
		"\ndefault-value: 1";
	std::string tooltip_polygonpattern_clip = "Turning on clipping can help performance in the case that the boundaries of the geometry extent outside of tile extents."
		" But clipping can result in undesirable rendering artifacts in rare cases."
		"\n\ndefault-meaning: The geometry will not be clipped to"
		" map bounds before rendering."
		"\ncss: polygon-pattern-clip"
		"\ntype: boolean"
		"\ndefault-value: false";
	std::string tooltip_polygonpattern_simplify ="geometries are simplified by the given tolerance."
		"\n\ndefault-meaning: geometry will not be simplified."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_polygonpattern_simplify_algorithm = "geometries are simplified by the given algorithm."
		"\n\ndefault-meaning: The geometry will be simplified using "
		"the radial distance algorithm."
		"\ncss: polygon-pattern-simplify-algorithm"
		"\ntype: "
		"\n\t[0]: radial-distance"
		"\n\t[1]: zhao-saalfeld"
		"\n\t[2]: visvalingam-whyatt"
		"\n\t[3]: douglas-peucker"
		"\ndefault-value: radial-distance";
	std::string tooltip_polygonpattern_smooth = "Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed."
		" Values greater than 1 will produce wild, looping geometries."
		"\n\ndefault-meaning: No smoothing."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_polygonpattern_geometry_transform = "Transform polygon geometry with specified function "
		"and apply pattern to transformed geometry."
		"\n\ndefault-meaning: The geometry will not be transformed."
		"\ntype: functions"
		"\ndefault-value: none";
	std::string tooltip_polygonpattern_transform = "Transform polygon pattern instance with specified function."
		"\n\ndefault-meaning: No transformation."
		"\ntype: functions"
		"\ndefault-value: none";
	std::string tooltip_polygonpattern_compop = "Composite operation."
		" This defines how this symbolizer should behave relative to symbolizers atop or below it."
		"\ndefault-meaning: Add the current symbolizer on top of other symbolizer."
		"\ndefault-value: src - over";
	std::string tooltip_marker_spacing = "Space between repeated markers in pixels."
		" If the spacing is less than the marker size or larger than"
		" the line segment length then no marker will be placed."
		"Any value less than 1 will be ignored and the default will be used instead."
		"\n\ndefault-meaning: In the case of marker-placement:"
		"line then draw a marker every 100 pixels along a line.";
	std::string tooltip_marker_compop = "Composite Operation. This defines how this symbolizer should behave relative"
		"to symbolizers atop or below it."
		"\n\ndefault-meaning: Add the current symbolizer on top of other symbolizer."
		"\ndefault-value: src - over";
	std::string tooltip_marker_file = "A file that this marker shows at each placement."
		" If no file is given, the marker will show an ellipse."
		" Accepted formats: svg, jpg, png, tiff, and webp."
		"\n\ndefault-meaning: An ellipse or circle, if width equals height."
		"\ndefault-value: none";
		
	std::string tooltip_marker_fill = "The color of the area of the marker."
		" This property will also set the `fill` of elements"
		" in an SVG loaded from a file."
		"\n\ndefault-meaning: The marker fill color is blue."
		"\ndefault-value: blue";
	std::string tooltip_marker_opacity = "The overall opacity of the marker, if set,"
		" overrides both the opacity of the fill and"
		" the opacity of the stroke."
		"\n\ndefault-meaning: The stroke-opacity and fill-opacity of the marker.";
	std::string tooltip_marker_geometry_transform = "Transform marker geometry with specified function."
		"\n\ndefault-meaning: The geometry will not be transformed.";
	std::string tooltip_marker_transform = "Transform marker instance with specified function."
		" Ignores map scale factor."
		"\n\ndefault-meaning: No transformation."
		"\ntype: functions"
		"\ndefault-value: none";
	std::string tooltip_marker_fill_opacity = "The fill opacity of the marker."
		" This property will also set the `fill-opacity` of elements "
		"in an SVG loaded from a file."
		"\n\ndefault-meaning: Color is fully opaque."
		"\ntype: float"
		"\ndefault-value: 1";
	std::string tooltip_marker_smooth = "Smooths out geometry angles."
		" 0 is no smoothing, 1 is fully smoothed."
		" Values greater than 1 will produce wild, looping geometries."
		"\ndefault-meaning: No smoothing."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_marker_offset = "Offsets a marker from a line a number of pixels parallel to its actual path."
		" Positive values move the marker left,"
		" negative values move it right"
		" (relative to the directionality of the line)"
		"\n\ndefault-meaning: Will not be offset."
		"\ntype: float"
		"\ndefault-value: 0";
	std::string tooltip_marker_default = "Allows omitting a marker symbolizer rule or emitting it with default values.";
	std::string tooltip_marker_type = "The default marker-type. If a SVG file is not given as the marker-file parameter,"
		" the renderer provides either an arrow or an ellipse (a circle if height is equal to width)."
		"\n\ndefault-meaning : The marker shape is an ellipse.";
	std::string tooltip_marker_multi_policy = "A special setting to allow the user to control rendering behavior for 'multi-geometries' (when a feature contains multiple geometries). This setting does not apply to markers placed along lines."
		" The 'each' policy is default and means all geometries will get a marker. The 'whole' policy means that the aggregate centroid between all geometries will be used. The 'largest' policy means that only the largest (by bounding box areas) feature will get a rendered marker (this is how text labeling behaves by default)."
		"\n\nIf a feature contains multiple geometries and the placement type is either point or interior then a marker will be rendered for each.";
	std::string tooltip_marker_clip ="Turning on clipping can help performance"
		" in the case that"
		" the boundaries of the geometry extent outside of tile extents."
		" But clipping can result in undesirable rendering artifacts in rare cases."
		"\n\ndefault-meaning: The geometry will not be clipped to map bounds before rendering."
		"\ntype: boolean"
		"\ndefault-value: false";
	std::string tooltip_marker_placement = "Attempt to place markers on a point, in the center of a polygon,"
		" or if markers-placement:line, then multiple times along a line."
		" 'interior' placement can be used to ensure that points placed on polygons are forced to be inside the polygon interior. The 'vertex-first' and"
		" 'vertex-last' options can be used to place markers at the first or last vertex of lines or polygons."
		"\n\ndefault-meaning: Place markers at the center point (centroid) of the geometry.";
	std::string tooltip_marker_simplify = "geometries are simplified by the given tolerance."
		"\n\ndefault-meaning: Geometry will not be simplified."
		"\ntype: functions"
		"\n\ndefault-value: none";
	std::string tooltip_marker_ignore_placement = "Value to control whether the placement of the feature "
		"will prevent the placement of other features."
		"\n\n default-meaning: do not store the bbox of this geometry"
		" in the collision detector cache.";
	std::string tooltip_marker_allow_overlap = "Control whether overlapping markers are shown or hidden."
		"\n\ndefault-meaning: Do not allow markers to overlap with each other - overlapping markers will not be shown.";
	std::string tooltip_marker_avoid_edges = "Avoid placing markers that intersect with tile boundaries."
		"\n\ndefault-meaning: Markers will be potentially placed near tile edges and"
		" therefore may look cut off unless they are rendered on each adjacent tile.";
	std::string tooltip_marker_simplify_algorithm = "geometries are simplified by the given algorithm."
		"\ndefault-meaning: The geometry will be simplified using the radial distance algorithm. "
		"type[4]:\n\t 0	: radial-distance"
		"\n\t1 : zhao - saalfeld"
		"\n\t2 : visvalingam - whyatt"
		"\n\t3 : douglas - peucker";
	std::string tooltip_marker_direction = "How markers should be placed along lines."
		" With the \"auto\" setting when marker is upside down the marker is automatically rotated by 180 degrees to keep it upright."
		" The \"auto-down\" value places marker in the opposite orientation to \"auto\"."
		" The \"left\" or \"right\" settings can be used to force marker to always be placed along a line in a given direction and therefore disables rotating if marker appears upside down. The \"left-only\" or \"right-only\" properties also force a given direction but will discard upside down markers rather than trying to flip it."
		" The \"up\" and \"down\" settings don't adjust marker's orientation to the line direction."
		"\ndefault-meaning: Markers are oriented to the right in the line direction."
		"\ntype[8]:\n\t0 : auto \n\t1 : auto-down"
		"\n\t2 : left"
		"\n\t3 : right"
		"\n\t4 : left - only"
		"\n\t5 : right - only"
		"\n\t6 : up"
		"\n\t7 : down";
	
	std::string tooltip_marker_stroke = "The color of the stroke around the marker."
		" This property will also set the `stroke` of elements in an SVG loaded from a file."
		"\n\ndefault-meaning: The marker will be drawn with a black outline."
		"\ndefault-value: black"
		"\ntype: color";
	std::string tooltip_marker_max_error = "N/A: not intended to be changed."
		"\n\ndefault-meaning: N/A: not intended to be changed.";
	std::string tooltip_marker_width = "The width of the marker, if using one of the default types."
		"\ndefault-meaning: The marker width is 10 pixels.";
	std::string tooltip_marker_height = "The height of the marker, if using one of the default types. "
		"\ndefault-meaning: The marker height is 10 pixels.";
	std::string tooltip_marker_stroke_opacity = "The opacity of a line."
		"\n\ndefault-meaning: Color is fully opaque."
		" This property will also set the `stroke-opacity` of elements in an SVG loaded from a file."
		"\ntype: float"
		"\ndefault-value: 1.0";
	std::string tooltip_marker_stroke_width = "The width of the stroke around the marker, in pixels."
		" This is positioned on the boundary, so high values can cover the area itself."
		" This property will also set the `stroke-width` of elements in an SVG loaded from a file."
		"\ndefault-meaning: The marker will be drawn with an outline of .5 pixels wide."
		"\ndefault-value: 0.5"
		"\ntype: float";

	std::map<UINT, TooltipInfo> m_map_tooltip;
	std::string tooltip_csv_file = "Path to the file for the datasource\n"
		"required: true";
	std::string tooltip_csv_base = "A base path used to complete a full path to a file."
		"\ndefault-meaning: Only the `file` option will be used to attempt to load data from the filesystem";
	std::string tooltip_csv_encoding = "The encoding value for the datasource attributes"
		"\ndefault-meaning: UTF8 will be the assumed encoding for string attribute values";
	std::string tooltip_csv_row_limit = "Max amount of features to read from the datasource"
		"\ndefault-meaning: All features will be read from the datasource (unless row_limit is > 1)";
	std::string tooltip_csv_escape = "The escape character to use for parsing data"
		"\ndefault-meaning: A backslash will be used as the assumed character that the data"
		" uses for escaping other characters"
		"\ndefault-value: A single backslash (aka. reverse solidus): \\\\";
	std::string tooltip_csv_quote = "The quote character to use for parsing data"
		"\ndefault-meaning: A backslash will be used as the assumed character "
		"that the data uses for escaping other characters"
		"\ndefault-value: A quotation mark (aka. double quote): \"";
	std::string tooltip_csv_separator = "The separator character to use for parsing data"
		"\ndefault-meaning: A comma will be used unless more tabs (\t), pipes (|), or semicolons (;)"
		" are detected than commas in the header row (in that order of preference)"
		"\ndefault-value: Basic autodetection is used to determine the best default value "
		"if the user does not manually supply a separator.";
	std::string tooltip_csv_headers = "A comma separated list of header names that can be set to add headers to data that lacks them"
		"\ndefault-meaning: Headers will be parsed from the first line of the data unless this option is set";
	std::string tooltip_csv_file_size_max = "The maximum filesize in MB that will be accepted"
		"\ndefault-meaning: A file that is larger that 20 MB will not be accepted and an error will be throw unless the user manually passes this option with a larger value "
		"(useful only in cases where your machine has a lot of memory)";
	std::string tooltip_csv_strict = "Control if the datasource should throw on invalid rows"
		"\ndefault-meaning: Unless this option is set to true the datasource will skip invalid rows"
		" and attempt to parse as much data as possible";


	std::string tooltip_gdal_file = "Path to the file for the datasource";
	std::string tooltip_gdal_base = "A base path used to complete a full path to a file.\n"
		"\ndefault-meaning: Only the `file` option will be used to attempt to load data from the filesystem.";
	std::string tooltip_gdal_encoding = "The encoding value for the datasource attributes."
		"\ndefault-meaning: UTF8 will be the assumed encoding for string attribute values";
	std::string tooltip_gdal_max_image_area = "Maximum memory limitation for image will be simply based on the maximum area we allow for an image."
		" The true memory footprint therefore will vary based on the type of imagery that exists."
		" This is not the maximum size of an image on disk but rather the maximum size we will load into mapnik from GDAL."
		" `max_im_area` based on 50 mb limit for RGBA"
		"\ndefault-meaning: 50Mb"
		"\ndefault-value: 13107200";
	std::string tooltip_gdal_band = "A particular raster band to work with."
		"\ndefault-meaning: No particular raster band set, working with all bands."
		"\ndefault-value: 0";
	std::string tooltip_gdal_nodata = "Overrides nodata value from the raster."
		"\ndefault-meaning: Nodata value from the raster is used."
		"\ndefault-value: 0";
	std::string tooltip_gdal_nodata_tolerance = "Make pixels in this tolerance around nodata value transparent."
		"\ndefault-meaning: The tolerance is effectively zero."
		"\ndefault-value	:	1e-12";
	std::string tooltip_gdal_shared = "Allows to share the GDAL dataset handle with other GDAL datasources with the same file path."
		"\ndefault-meaning: The datasource will use unique dataset instance."
		"\ndefault-value: false";


	std::string tooltip_geojson_file = "Path to the file for the datasource";
	std::string tooltip_geojson_base = "A base path used to complete a full path to a file."
		"\ndefault-meaning: Only the `file` option will be used to attempt to load data from the filesystem."
		"\nrequired: false";
	std::string tooltip_geojson_encoding = "The encoding value for the datasource attributes."
		"\ndefault-meaning: UTF8 will be the assumed encoding for string attribute values"
		"\ndefault-value: utf-8";
	std::string tooltip_geojson_inline = "Raw tabular data to be read instead of reading data from a file."
		"\ndefault-meaning: Unless this option is provided data will be read from the `file` option";

	std::string tooltip_occi_encoding = "The encoding value for the datasource attributes"
		"\ndefault-meaning: UTF8 will be the assumed encoding for string attribute values";
	TooltipInfo m_polygon_tooltip[11] = { 
		TooltipInfo("polygonsymbolizer.default", tooltip_polygon_default),
		TooltipInfo("polygonsymbolizer.fill", tooltip_polygon_fill),
		TooltipInfo("polygonsymbolizer.fill_opacity", tooltip_polygon_fill_opacity),
		TooltipInfo("polygonsymbolizer.gamma", tooltip_polygon_gamma),
		TooltipInfo("polygonsymbolizer.gamma_method", tooltip_polygon_gamma_method),
		TooltipInfo("polygonsymbolizer.clip",tooltip_polygon_clip),
		TooltipInfo("polygonsymbolizer.simplify", tooltip_polygon_simplify),
		TooltipInfo("polygonsymbolizer.simplify_algorithm", tooltip_polygon_simplify_algorithm),
		TooltipInfo("polygonsymbolizer.geometry_transform", tooltip_polygon_geometry_transform),
		TooltipInfo("polygonsymbolizer.smooth", tooltip_polygon_smooth),
		TooltipInfo("polygonsymbolizer.compop", tooltip_polygon_compop),
	};
	TooltipInfo m_polygonpattern_tooltip[12] =
	{
		TooltipInfo("polygonpatternsymbolizer.default", tooltip_polygonpattern_default),
		TooltipInfo("polygonpatternsymbolizer.file", tooltip_polygonpattern_file),
		TooltipInfo("polygonpatternsymbolizer.alignment", tooltip_polygonpattern_alignment),
		TooltipInfo("polygonpatternsymbolizer.gamma", tooltip_polygonpattern_gamma),
		TooltipInfo("polygonpatternsymbolizer.clip", tooltip_polygonpattern_clip),
		TooltipInfo("polygonpatternsymbolizer.simplify", tooltip_polygonpattern_simplify),
		TooltipInfo("polygonpatternsymbolizer.simplify_algorithm", tooltip_polygonpattern_simplify_algorithm),
		TooltipInfo("polygonpatternsymbolizer.smooth", tooltip_polygonpattern_smooth),
		TooltipInfo("polygonpatternsymbolizer.geomtry_transform", tooltip_polygonpattern_geometry_transform),
		TooltipInfo("polygonpatternsymbolizer.compop", tooltip_polygonpattern_compop),
		TooltipInfo("polygonpatternsymbolizer.transform", tooltip_polygonpattern_transform),
		TooltipInfo("polygonpatternsymbolizer.opacity", tooltip_polygonpattern_opacity),
	};
	TooltipInfo m_marker_tooltip[27] =
	{
		TooltipInfo("markersymbolizer.default", tooltip_marker_default ),
		TooltipInfo("markersymbolizer.file", tooltip_marker_file),
		TooltipInfo("markersymbolizer.opacity", tooltip_marker_opacity),
		TooltipInfo("markersymbolizer.fill_opacity", tooltip_marker_fill_opacity),
		TooltipInfo("markersymbolizer.stroke", tooltip_marker_stroke),
		TooltipInfo("markersymbolizer.stroke_width", tooltip_marker_stroke_width),
		TooltipInfo("markersymbolizer.stroke_opacity", tooltip_marker_stroke_opacity),
		TooltipInfo("markersymbolizer.placement", tooltip_marker_placement),
		TooltipInfo("markersymbolizer.multi_policy", tooltip_marker_multi_policy),
		TooltipInfo("markersymbolizer.marker_type", tooltip_marker_type),
		TooltipInfo("markersymbolizer.width", tooltip_marker_width),
		TooltipInfo("markersymbolizer.height", tooltip_marker_height),
		TooltipInfo("markersymbolizer.fill", tooltip_marker_fill),
		TooltipInfo("markersymbolizer.allow_overlap", tooltip_marker_allow_overlap),
		TooltipInfo("markersymbolizer.avoid_edges", tooltip_marker_avoid_edges),
		TooltipInfo("markersymbolizer.ignore_placement", tooltip_marker_ignore_placement),
		TooltipInfo("markersymbolizer.spacing", tooltip_marker_spacing),
		TooltipInfo("markersymbolizer.max_error", tooltip_marker_max_error),
		TooltipInfo("markersymbolizer.transform", tooltip_marker_transform),
		TooltipInfo("markersymbolizer.clip", tooltip_marker_clip),
		TooltipInfo("markersymbolizer.simplify", tooltip_marker_simplify),
		TooltipInfo("markersymbolizer.simplify_algorithm", tooltip_marker_simplify_algorithm),
		TooltipInfo("markersymbolizer.smooth", tooltip_marker_smooth),
		TooltipInfo("markersymbolizer.geometry_transform", tooltip_marker_geometry_transform),
		TooltipInfo("markersymbolizer.offset", tooltip_marker_offset),
		TooltipInfo("markersymbolizer.comp_op", tooltip_marker_compop),
		TooltipInfo("markersymbolizer.direction", tooltip_marker_direction),
	};
	TooltipInfo m_csv_tooltip[10] = {
	TooltipInfo("datasourcecsv.file", tooltip_csv_file),
	TooltipInfo("datasourcecsv.base", tooltip_csv_base),
	TooltipInfo("datasourcecsv.encoding", tooltip_csv_encoding),
	TooltipInfo("datasourcecsv.row_limit", tooltip_csv_row_limit),
	TooltipInfo("datasourcecsv.escape", tooltip_csv_escape),
	TooltipInfo("datasourcecsv.quote", tooltip_csv_quote),
	TooltipInfo("datasourcecsv.separator", tooltip_csv_separator),
	TooltipInfo("datasourcecsv.headers", tooltip_csv_headers),
	TooltipInfo("datasourcecsv.file_size_max", tooltip_csv_file_size_max),
	TooltipInfo("datasourcecsv.strict", tooltip_csv_strict),
	};
	TooltipInfo m_gdal_tooltip[8] = {
	TooltipInfo("datasourcegdal.file", tooltip_gdal_file),
	TooltipInfo("datasourcegdal.base", tooltip_gdal_base),
	TooltipInfo("datasourcegdal.encoding", tooltip_gdal_encoding),
	TooltipInfo("datasourcegdal.band", tooltip_gdal_band),
	TooltipInfo("datasourcegdal.max_image_area", tooltip_gdal_max_image_area),
	TooltipInfo("datasourcegdal.shared", tooltip_gdal_shared),
	TooltipInfo("datasourcegdal.nodata", tooltip_gdal_nodata),
	TooltipInfo("datasourcegdal.nodata_tolerance", tooltip_gdal_nodata_tolerance),
	};
	TooltipInfo m_geojson_tooltip[4] = {
	TooltipInfo("datasourcegeojson.file", tooltip_geojson_file),
	TooltipInfo("datasourcegeojson.base", tooltip_geojson_base),
	TooltipInfo("datasourcegeojson.encoding", tooltip_geojson_encoding),
	TooltipInfo("datasourcegeojson.inline", tooltip_geojson_inline),
	
	};
	TooltipInfo m_occi_tooltip[1] = {
	TooltipInfo("datasourceocci.encoding", tooltip_occi_encoding),
	};
	std::string ConvertBinary2String(std::string);
	std::string AddTagHTML2String(std::string str, std::string tag);
	void ReadDatabaseTooltip();
	BOOL WriteTooltipSqlite(CString path);
	std::string ReplaceString(std::string str, std::string toReplace, std::string replaceStr);
};