// CustomToolTipCtrl.cpp : implementation file
//
#include "stdafx.h"
#include "pch.h"
#include "SymbolizerProject.h"
#include "CustomToolTipCtrl.h"
#include "sqlite3.h"
#include <bitset>
#include <vector>
#include<sstream>


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
// CCustomToolTipCtrl

IMPLEMENT_DYNAMIC(CCustomToolTipCtrl, CBCGPToolTipCtrl)

CCustomToolTipCtrl::CCustomToolTipCtrl()
{
	
}

CCustomToolTipCtrl::~CCustomToolTipCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomToolTipCtrl, CBCGPToolTipCtrl)
	ON_NOTIFY_REFLECT(TTN_SHOW, &CCustomToolTipCtrl::OnTtnTooltipShow)
END_MESSAGE_MAP()



// CCustomToolTipCtrl message handlers




void CCustomToolTipCtrl::OnTtnTooltipShow(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	m_nCurrID = CWnd::FromHandle((HWND)pNMHDR->idFrom)->GetDlgCtrlID();
	switch (m_nCurrID)
	{
	case IDC_CHECK_POLYGON_DEFAULT:
		m_strDescription = tooltip_polygon_default.c_str();
		break;
	case IDC_MFCCOLORBUTTON_POLYGON_FILL:
		m_strDescription = tooltip_polygon_fill.c_str();
		break;
	case IDC_EDIT_POLYGON_FILL_OPACITY:
		m_strDescription = tooltip_polygon_fill_opacity.c_str();
		break;
	case IDC_EDIT_POLYGON_GAMMA:
		m_strDescription = tooltip_polygon_gamma.c_str();
		break;
	case IDC_COMBO_POLYGON_GAMMA_METHOD:
		m_strDescription = tooltip_polygon_gamma_method.c_str();
		break;
	case IDC_CHECK_POLYGON_CLIP:
		m_strDescription = tooltip_polygon_clip.c_str();
		break;
	case IDC_EDIT_POLYGON_SIMPLIFY:
		m_strDescription = tooltip_polygon_simplify.c_str();
		break;
	case IDC_COMBO_POLYGON_SYMPLIFY_ALGORITHM:
		m_strDescription = tooltip_polygon_simplify_algorithm.c_str();
		break;
	case IDC_COMBO_POLYGON_GEOMETRY_TRANSFORM:
		m_strDescription = tooltip_polygon_geometry_transform.c_str();
		break;
	case IDC_EDIT_POLYGON_SMOOTH:
		m_strDescription = tooltip_polygon_smooth.c_str();
		break;
	case IDC_COMBO_POLYGON_COMPOP:
		m_strDescription = tooltip_polygon_compop.c_str();
	case IDC_CHECK_POLYGON_PATTERN_DEFAULT:
		m_strDescription = tooltip_polygonpattern_default.c_str();
		break;
	case IDC_EDIT_POLYGON_PATTERN_FILE:
		m_strDescription = tooltip_polygonpattern_file.c_str();
		break;
	case IDC_COMBO_POLYGON_PATTERN_ALIGNMENT:
		m_strDescription = tooltip_polygonpattern_alignment.c_str();
		break;
	case IDC_EDIT_POLYGON_PATTERN_GAMMA:
		m_strDescription = tooltip_polygonpattern_gamma.c_str();
		break;
	case IDC_EDIT_POLYGON_PATTERN_OPACITY:
		m_strDescription = tooltip_polygonpattern_opacity.c_str();
		break;
	case IDC_CHECK_POLYGON_PATTERN_CLIP:
		m_strDescription = tooltip_polygonpattern_clip.c_str();
		break;
	case IDC_EDIT_SIMPLIFY_POLYGON_PATTERN:
		m_strDescription = tooltip_polygonpattern_simplify.c_str();
		break;
	case IDC_COMBO_POLYGON_PATTERN_SIMPLIFY_ALGORITHM:
		m_strDescription = tooltip_polygonpattern_simplify_algorithm.c_str();
		break;
	case IDC_EDIT_SMOOTH_POLYGON_PATTERN:
		m_strDescription = tooltip_polygonpattern_smooth.c_str();
		break;
	case IDC_COMBO_POLYGON_PATTERN_GEOMETRY_TRANSFORM:
		m_strDescription = tooltip_polygonpattern_geometry_transform.c_str();
		break;
	case IDC_COMBO_POLYGON_PATTERN_TRANSFORM:
		m_strDescription = tooltip_polygonpattern_transform.c_str();
		break;
	case IDC_COMBO_POLYGON_PATTERN_COMPOP:
		m_strDescription = tooltip_polygonpattern_compop.c_str();
		break;
	
	case IDC_EDIT_MARKER_SPACING:
		m_strDescription = tooltip_marker_spacing.c_str();
		break;
	case IDC_COMBO_MARKER_COMPOP:
		m_strDescription = tooltip_marker_compop.c_str();
		break;
	case IDC_EDIT_MARKER_FILE:
		m_strDescription = tooltip_marker_file.c_str();
		break;
	case IDC_MFCCOLORBUTTON_MARKER_FILL:
		m_strDescription = tooltip_marker_fill.c_str();
		break;
	case IDC_EDIT_MARKER_OPACITY:
		m_strDescription = tooltip_marker_opacity.c_str();
		break;
	case IDC_COMBO_MARKER_GEOMETRY_TRANSFORM:
		m_strDescription = tooltip_marker_geometry_transform.c_str();
		break;
	case IDC_COMBO_MARKER_TRANSFORM:
		m_strDescription = tooltip_marker_transform.c_str();
		break;
	case IDC_EDIT_MARKER_FILL_OPACITY:
		m_strDescription = tooltip_marker_fill_opacity.c_str();

		break;
	case IDC_EDIT_MARKER_SMOOTH:
		m_strDescription = tooltip_marker_smooth.c_str();
		break;
	
	case IDC_EDIT_MARKER_OFFSET:
		m_strDescription = tooltip_marker_offset.c_str();
		break;
	case IDC_CHECK_MARKER_DEFAULT:
		m_strDescription = tooltip_marker_default.c_str();
		break;
	case IDC_COMBO_MARKER_MARKER_TYPE:
		m_strDescription = tooltip_marker_type.c_str();
		break;
	case IDC_COMBO_MARKER_MULTI_POLICY:
		m_strDescription = tooltip_marker_multi_policy.c_str();
		break;
	case IDC_CHECK_MARKER_CLIP:
		m_strDescription = tooltip_marker_clip.c_str();
		break;
	case IDC_COMBO_MARKER_PLACEMENT:
		m_strDescription = tooltip_marker_placement.c_str();
		break;
	case IDC_EDIT_MARKER_SIMPLIFY:
		m_strDescription = tooltip_marker_simplify.c_str();
		break;
	case IDC_CHECK_MARKER_IGNORE_PLACEMENT:
		m_strDescription = tooltip_marker_ignore_placement.c_str();
		break;
	case IDC_CHECK_MARKER_ALLOW_OVERLAP:
		m_strDescription = tooltip_marker_allow_overlap.c_str();
		break;
	case IDC_CHECK_MARKER_AVOID_EDGES:
		m_strDescription = tooltip_marker_avoid_edges.c_str();
		break;
	case IDC_COMBO_MARKER_SIMPLIFY_ALGORITHM:
		m_strDescription = tooltip_marker_simplify_algorithm.c_str();
		break;
	case IDC_COMBO_MARKER_DIRECTION:
		m_strDescription = tooltip_marker_direction.c_str();
		break;
	case IDC_MFCCOLORBUTTON_MARKER_STROKE:
		m_strDescription = tooltip_marker_stroke.c_str();
		break;
	case IDC_EDIT_MARKER_MAX_ERROR:
		m_strDescription = tooltip_marker_max_error.c_str();
		break;
	case IDC_EDIT_MARKER_WIDTH:
		m_strDescription = tooltip_marker_width.c_str();
		break;
	case IDC_EDIT_MARKER_HEIGHT:
		m_strDescription = tooltip_marker_height.c_str();
		break;
	case IDC_EDIT_MARKER_STROKE_OPACITY:
		m_strDescription = CString(tooltip_marker_stroke_opacity.c_str());
		break;
	case IDC_EDIT_MARKER_STROKE_WIDTH:
		m_strDescription = CString(tooltip_marker_stroke_width.c_str());
		break;
	case IDC_EDIT_CSV_FILE:
		m_strDescription = CString(tooltip_csv_file.c_str());
		break;
	case IDC_EDIT_CSV_BASE:
		m_strDescription = CString(tooltip_csv_base.c_str());
		break;
	case IDC_EDIT_CSV_ENCODING:
		m_strDescription = CString(tooltip_csv_encoding.c_str());
		break;
	case IDC_EDIT_CSV_ROW_LIMIT:
		m_strDescription = CString(tooltip_csv_row_limit.c_str());
		break;
	case IDC_CHECK_CSV_STRICT:
		m_strDescription = CString(tooltip_csv_strict.c_str());
		break;
	case IDC_EDIT_CSV_FILE_SIZE_MAX:
		m_strDescription = CString(tooltip_csv_file_size_max.c_str());
		break;
	case IDC_EDIT_CSV_QUOTE:
		m_strDescription = CString(tooltip_csv_quote.c_str());
		break;
	case IDC_EDIT_CSV_HEADERS:
		m_strDescription = CString(tooltip_csv_headers.c_str());
		break;
	case IDC_EDIT_CSV_SEPARATER:
		m_strDescription = CString(tooltip_csv_headers.c_str());
		break;
	case IDC_EDIT_CSV_ESCAPE:
		m_strDescription = CString(tooltip_csv_headers.c_str());
		break;
	case IDC_EDIT_GDAL_FILE:
		m_strDescription = tooltip_gdal_file.c_str();
		break;
	case IDC_EDIT_GDAL_BASE:
		m_strDescription = tooltip_gdal_base.c_str();
		break;
	case IDC_EDIT_GDAL_ENCODING:
		m_strDescription = tooltip_gdal_encoding.c_str();
		break;
	case IDC_EDIT_GDAL_MAX_IMAGE_AREA:
		m_strDescription = tooltip_gdal_max_image_area.c_str();
		break;
	case IDC_EDIT_GDAL_BAND:
		m_strDescription = tooltip_gdal_band.c_str();
		break;
	case IDC_EDIT_GDAL_NODATA:
		m_strDescription = tooltip_gdal_nodata.c_str();
		break;
	case IDC_EDIT_GDAL_NODATA_TOLERANCE:
		m_strDescription = tooltip_gdal_nodata_tolerance.c_str();
		break;
	case IDC_CHECK_GDAL_SHARE:
		m_strDescription = tooltip_gdal_shared.c_str();
		break;
	case IDC_EDIT_GEOJSON_FILE:
		m_strDescription = tooltip_geojson_file.c_str();
		break;
	case IDC_EDIT_GEOJSON_BASE:
		m_strDescription = tooltip_geojson_base.c_str();
		break;
	case IDC_EDIT_GEOJSON_ENCODING:
		m_strDescription = tooltip_geojson_encoding.c_str();
		break;
	case IDC_EDIT_GEOJSON_INLINE:
		m_strDescription = tooltip_geojson_inline.c_str();
		break;
	case IDC_EDIT_OCCI_ENCODING:
		m_strDescription = tooltip_occi_encoding.c_str();
		break;
	default:
		m_strDescription.Empty();
	}
	CBCGPToolTipCtrl::OnShow(pNMHDR, pResult);
}

int CCustomToolTipCtrl::CreateDatabaseTooltip()
{
	/// <summary>
	/// The function is used to create a tooltip database in SQLite3.
	/// </summary>
	/// <returns>0 if create the database successful</returns>
	sqlite3* db;
	std::string sql_string = "CREATE TABLE IF NOT EXISTS TOOLTIP("
		"TooltipCode TEXT PRIMARY KEY  NOT NULL, "
		"TooltipText BLOB );";
	int exit = 0;
	exit = sqlite3_open("tooltip.db", &db);
	char* messaggeError;
	exit = sqlite3_exec(db, sql_string.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK)
	{
		AfxMessageBox(_T("Error when create table"));
		return -1;
	}

	for (int i = 0; i < 11; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_polygon_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_polygon_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	
	for (int i = 0; i < 12; i++)
	{
		sqlite3_stmt* stmt = NULL;

		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_polygonpattern_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_polygonpattern_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	for (int i = 0; i < 27; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_marker_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_marker_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1 , &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_csv_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_csv_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_gdal_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_gdal_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_geojson_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_geojson_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	for (int i = 0; i < 1; i++)
	{
		sqlite3_stmt* stmt = NULL;
		std::string query = "INSERT INTO TOOLTIP VALUES(\"" + m_occi_tooltip[i].T_Code +
			"\", ?);";
		std::string content = AddTagHTML2String(m_occi_tooltip[i].T_Content, "div");
		int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			AfxMessageBox(_T("Error when insert value"));
			return -1;
			break;
		}
		else
		{
			rc = sqlite3_bind_blob(stmt, 1, content.c_str(), sizeof(char) * content.length(), SQLITE_STATIC);
			const char* result = sqlite3_errmsg(db);

			rc = sqlite3_step(stmt);
		}
	}
	sqlite3_close(db);
	return 0;
}

std::string CCustomToolTipCtrl::ConvertBinary2String(std::string str)
{
	/// <summary>
	/// The function is use to convert binary to string.
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	std::string result;
	for (int i = 0; i < str.length(); i++)
	{
		result = result + std::bitset<8>(str[i]).to_string();
	}
	return std::string(result);
}

std::string CCustomToolTipCtrl::AddTagHTML2String(std::string str, std::string tag)
{
	/// <summary>
	/// The function is used to add new html tag to the text and replace
	/// endline key to "<br/>"
	/// </summary>
	/// <param name="str">The text is add new tag</param>
	/// <param name="tag">The new tag</param>
	/// <returns>The new html text</returns>
	std::string result;
	std::string endline_str = "\n";
	result =  ReplaceString(str, "\n", "<br/>");

	result = "<" + tag + ">" + result + "</" + tag + ">";
	return std::string(result);
}
BOOL CCustomToolTipCtrl::ReadTooltipSqlite(CString path)
{
	sqlite3* db;
	int rc;
	char* zErrMsg = 0;
	char* sql;
	sqlite3_stmt* stmt;

	/* Open database */
	rc = sqlite3_open((CT2A)path, &db);
	if (rc) {
		AfxMessageBox(L"Can't open database tooltip");
		return(0);
	}

	/* Create SQL statement */
	sql = "SELECT * from SYMBOLIZER";

	// compile sql statement to binary
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		AfxMessageBox(CString("ERROR: while compiling sql: ") + CString(sqlite3_errmsg(db)));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return FALSE;
	}

	// execute sql statement, and while there are rows returned, print ID
	int ret_code = 0;
	while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		std::string value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		value.replace(value.begin(), value.begin() + 5, "");
		value.replace(value.end() - 6, value.end(), "");
		size_t pos = value.find('|');
		std::string str_Doc = value.substr(0, pos);
		str_Doc = SplitStr(str_Doc, 50);
		m_MapTooltip_Doc[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = str_Doc;
		if (pos >= value.size())
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = "";
		else
		{
			value.erase(0, pos + 1);
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = value;
		}
		//AfxMessageBox(CString("TEST: ID = ") + CString(sqlite3_column_text(stmt, 0)) + CString(sqlite3_column_text(stmt, 1)));
	}
	if (ret_code != SQLITE_DONE)
	{
		//this error handling could be done better, but it works
		AfxMessageBox(CString("ERROR: while performing sql: ") + CString(sqlite3_errmsg(db)));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Create SQL statement */
	sql = "SELECT * from DATASOURCES";

	// compile sql statement to binary
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		AfxMessageBox(CString("ERROR: while compiling sql: ") + CString(sqlite3_errmsg(db)));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return FALSE;
	}

	// execute sql statement, and while there are rows returned, print ID
	ret_code = 0;
	while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		std::string value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		value.replace(value.begin(), value.begin() + 5, "");
		value.replace(value.end() - 6, value.end(), "");
		size_t pos = value.find('|');
		std::string str_Doc = value.substr(0, pos);
		str_Doc = SplitStr(str_Doc, 50);
		m_MapTooltip_Doc[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = str_Doc;
		if (pos >= value.size())
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = "";
		else
		{
			value.erase(0, pos + 1);
			m_MapTooltip_Default[std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)))] = value;
		}
		//AfxMessageBox(CString("TEST: ID = ") + CString(sqlite3_column_text(stmt, 0)) + CString(sqlite3_column_text(stmt, 1)));
	}
	if (ret_code != SQLITE_DONE)
	{
		//this error handling could be done better, but it works
		AfxMessageBox(CString("ERROR: while performing sql: ") + CString(sqlite3_errmsg(db)));
	}

	sqlite3_close(db);
	return 0;

}
BOOL CCustomToolTipCtrl::WriteTooltipSqlite(CString path)
{
	sqlite3* db;
	int rc;
	char* zErrMsg = 0;
	char* sql;
	FILE* fp;

	/* Open database */
	rc = sqlite3_open((CT2A)path, &db);
	if (rc) {
		AfxMessageBox(L"Can't open database tooltip");
		return(0);
	}

	/* Create SQL statement */
	sql = "CREATE TABLE SYMBOLIZER("  \
		"TOOLTIPCode TEXT PRIMARY KEY NOT NULL,"
		"TooltipContent BLOB);";
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		AfxMessageBox(CString(_T("SQL error: ") + CString(zErrMsg)));
		sqlite3_free(zErrMsg);
	}

	fopen_s(&fp, "reference.json", "r");

	if (fp != NULL) {
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document res_object;
		res_object.ParseStream(is);
		fclose(fp);
		rapidjson::Value& symbolizers = res_object["symbolizers"];
		assert(symbolizers.IsObject());
		//const rapidjson::Value& shield = symbolizers["shield"];

		//assert(shield.IsObject());
		std::string Name_Symbolizers[] = { "line", "line-pattern", "raster", "point", "dot" };
		for (auto name_sym : Name_Symbolizers)
		{
			const rapidjson::Value& shield = symbolizers[name_sym.c_str()];
			for (rapidjson::Value::ConstMemberIterator itr = shield.MemberBegin(); itr != shield.MemberEnd(); ++itr)
			{   //iterate through object   
				const rapidjson::Value& Attribute = shield[itr->name.GetString()]; //make object value
				assert(Attribute.IsObject());
				std::string str_name = itr->name.GetString();

				const rapidjson::Value& doc = Attribute["doc"];
				assert(doc.IsString());
				std::string str_doc = doc.GetString();

				/*std::string str_default_value;
				const rapidjson::Value& default_value = Attribute["default-value"];
				if (default_value.IsString()) {
					assert(default_value.IsString());
					str_default_value = default_value.GetString();

				}
				else if (default_value.IsFloat()) {
					assert(default_value.IsFloat());
					float f = default_value.GetFloat();
					std::ostringstream ss;
					ss << f;
					str_default_value = std::string(ss.str());

				}
				else if (default_value.IsInt()) {
					assert(default_value.IsInt());
					int  d = default_value.GetInt();
					std::ostringstream ss;
					ss << d;
					str_default_value = std::string(ss.str());

				}
				else if (default_value.IsBool()) {
					assert(default_value.IsBool());
					bool  b = default_value.GetBool();
					const char* str_bool = b ? "true" : "false";
					str_default_value = std::string(str_bool);

				}
				else {
					str_default_value = std::string(" ");
				}*/

				std::string TooltipContent;
				auto it = Attribute.FindMember("default-meaning");
				if (it != Attribute.MemberEnd())
				{


					const rapidjson::Value& default_meaning = Attribute["default-meaning"];
					assert(default_meaning.IsString());
					std::string str_default_meaning = default_meaning.GetString();

					/*std::string str_type;
					const rapidjson::Value& m_type = Attribute["type"];
					if (m_type.IsString()) {
						assert(m_type.IsString());
						str_type = m_type.GetString();
					}
					else {
						str_type = std::string("[select]");
					}*/

					TooltipContent = "<div>" + str_doc + " | Default meaning: " + str_default_meaning + "</div>";
				}
				else
					TooltipContent = "<div>" + str_doc + "</div>";

				std::string str_TOOLTIPCode = "'" + name_sym + "symbolizer." + str_name + "'";
				//TooltipContent = strToBinary(TooltipContent);
				std::string insertQuery = "INSERT INTO SYMBOLIZER (TOOLTIPCode, TooltipContent) VALUES(" + str_TOOLTIPCode + ", ?);";

				sqlite3_stmt* insertStmt = NULL;
				int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, NULL);
				if (rc != SQLITE_OK) {
					MessageBox(CString(sqlite3_errmsg(db)));
				}
				else {
					rc = sqlite3_bind_blob(insertStmt, 1, TooltipContent.c_str(), TooltipContent.size(), SQLITE_STATIC);
					if (rc != SQLITE_OK) {
						MessageBox(CString(sqlite3_errmsg(db)));
					}
					else {
						if (sqlite3_step(insertStmt) != SQLITE_DONE) {
							MessageBox(CString(sqlite3_errmsg(db)));
						}
					}
				}

			}
		}
	}

	/* Create SQL statement */
	sql = "CREATE TABLE DATASOURCES("  \
		"TOOLTIPCode TEXT PRIMARY KEY NOT NULL,"
		"TooltipContent BLOB);";
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		AfxMessageBox(CString(_T("SQL error: ") + CString(zErrMsg)));
		sqlite3_free(zErrMsg);
	}

	fopen_s(&fp, "datasources.json", "r");


	if (fp != NULL) {
		char readBuffer[65536];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		rapidjson::Document res_object;
		res_object.ParseStream(is);
		fclose(fp);
		rapidjson::Value& symbolizers = res_object["datasources"];
		assert(symbolizers.IsObject());
		//const rapidjson::Value& shield = symbolizers["shield"];

		//assert(shield.IsObject());
		std::string Name_Symbolizers[] = { "ogr", "osm", "postgis", "python" };
		for (auto name_sym : Name_Symbolizers)
		{
			const rapidjson::Value& shield = symbolizers[name_sym.c_str()];
			for (rapidjson::Value::ConstMemberIterator itr = shield.MemberBegin(); itr != shield.MemberEnd(); ++itr)
			{   //iterate through object   
				const rapidjson::Value& Attribute = shield[itr->name.GetString()]; //make object value
				assert(Attribute.IsObject());
				std::string str_name = itr->name.GetString();

				const rapidjson::Value& doc = Attribute["doc"];
				assert(doc.IsString());
				std::string str_doc = doc.GetString();
				if (str_doc == "")
					continue;
				std::string TooltipContent;
				auto it = Attribute.FindMember("default-meaning");
				if (it != Attribute.MemberEnd())
				{


					const rapidjson::Value& default_meaning = Attribute["default-meaning"];
					assert(default_meaning.IsString());
					std::string str_default_meaning = default_meaning.GetString();
					if (str_default_meaning != "")
						TooltipContent = "<div>" + str_doc + " | Default meaning: " + str_default_meaning + "</div>";
					else
						TooltipContent = "<div>" + str_doc + "</div>";
				}
				else
					TooltipContent = "<div>" + str_doc + "</div>";


				std::string str_TOOLTIPCode = "'" + name_sym + "datasources." + str_name + "'";
				//TooltipContent = strToBinary(TooltipContent);
				std::string insertQuery = "INSERT INTO DATASOURCES (TOOLTIPCode, TooltipContent) VALUES(" + str_TOOLTIPCode + ", ?);";

				sqlite3_stmt* insertStmt = NULL;
				int rc = sqlite3_prepare_v2(db, insertQuery.c_str(), -1, &insertStmt, NULL);
				if (rc != SQLITE_OK) {
					MessageBox(CString(sqlite3_errmsg(db)));
				}
				else {
					rc = sqlite3_bind_blob(insertStmt, 1, TooltipContent.c_str(), TooltipContent.size(), SQLITE_STATIC);
					if (rc != SQLITE_OK) {
						MessageBox(CString(sqlite3_errmsg(db)));
					}
					else {
						if (sqlite3_step(insertStmt) != SQLITE_DONE) {
							MessageBox(CString(sqlite3_errmsg(db)));
						}
					}
				}

			}
		}
	}

	//"TooltipDefault BLOB);";

	/* Execute SQL statement */



	/*sqlite3_stmt* stmt = NULL;

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.default', ?)", -1, &stmt, NULL);
	std::string buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke', ?)", -1, &stmt, NULL);
	buffer = "<div>The color of a drawn line.| default-meaning: black and fully opaque (alpha = 1), same as rgb(0,0,0) or rgba(0,0,0,1).<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-width', ?)", -1, &stmt, NULL);
	buffer = "<div>The width of a line in pixels.| default-meaning: The line will be rendered 1 pixel wide.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The opacity of a line.| default-meaning: Color is fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-linejoin',  ?)", -1, &stmt, NULL);
	buffer = "<div>The behavior of lines when joining.| default-meaning: The line joins will be rendered using a miter look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-linecap',  ?)", -1, &stmt, NULL);
	buffer = "<div>The display of line endings.| default-meaning: The line endings will be rendered using a butt look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-gamma',  ?)", -1, &stmt, NULL);
	buffer = "<div>Level of antialiasing of stroke line.| default-meaning: Fully antialiased.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-gamma-method',  ?)", -1, &stmt, NULL);
	buffer = "<div>An Antigrain Geometry specific rendering hint to control the quality of antialiasing. Under the hood in Mapnik this "
		"\nmethod is used in combination with the `gamma` value (which defaults to 1). The methods are in the AGG source at"
		"\n https://github.com/mapnik/mapnik/blob/master/deps/agg/include/agg_gamma_functions."
		"| default-meaning: pow(x,gamma) is used to calculate pixel gamma, which produces slightly smoother line and polygon antialiasing than the `linear` method, while other methods are usually only used to disable AA.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-dasharray',  ?)", -1, &stmt, NULL);
	buffer = "<div>A pair of length values [a,b], where (a) is the dash length and (b) is the gap length respectively. "
		"\nMore than two values are supported for more complex patterns.| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-dashoffset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Valid parameter but not currently used in renderers (only exists for experimental svg support in Mapnik which is not yet enabled)."
		"| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.stroke-miterlimit',  ?)", -1, &stmt, NULL);
	buffer = "<div>The limit on the ratio of the miter length to the stroke-width. Used to automatically convert miter joins "
		"\nto bevel joins for sharp angles to avoid the miter extending beyond the thickness of the stroking path. "
		"\nNormally will not need to be set, but a larger value can sometimes help avoid jaggy artifacts."
		"| default-meaning: Will auto-convert miters to bevel line joins when theta is less than 29 degrees as per the SVG spec: `miterLength / stroke-width = 1 / sin ( theta / 2 )`.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.clip',  ?)", -1, &stmt, NULL);
	buffer = "<div>Turning on clipping can help performance in the case that the boundaries of the geometry extent "
		"\noutside of tile extents. But clipping can result in undesirable rendering artifacts in rare cases."
		"| default-meaning: The geometry will not be clipped to map bounds before rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.simplify',  ?)", -1, &stmt, NULL);
	buffer = "<div>Simplify geometries by the given tolerance.| default-meaning: geometry will not be simplified.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.simplify-algorithm',  ?)", -1, &stmt, NULL);
	buffer = "<div>Simplify geometries by the given algorithm.| default-meaning: The geometry will be simplified using the radial distance algorithm.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.smooth',  ?)", -1, &stmt, NULL);
	buffer = "<div>Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. "
		"\nValues greater than 1 will produce wild, looping geometries.| default-meaning: No smoothing.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.offset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, "
		"\nnegative values move it right (relative to the directionality of the line).| default-meaning: Will not be offset.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.rasterizer',  ?)", -1, &stmt, NULL);
	buffer = "<div>Exposes an alternate AGG rendering method that sacrifices some accuracy for speed."
		"| default-meaning: The line will be rendered using the highest quality method rather than the fastest.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.geometry-transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line geometry with specified function.| default-meaning: The geometry will not be transformed.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('LineSymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should behave relative to symbolizers atop or below it."
		"| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.line-pattern',  ?)", -1, &stmt, NULL);
	buffer = "<div>Sets the way how pattern is rendered. The `warp` options warps the pattern in "
		"\ndirection of the geometry. The `repeat` option can be used to repeat pattern "
		"\nin an area given by options `stroke-pattern-width`, `stroke-pattern-linecap`, "
		"\n`line-pattern-join`, `line-pattern-miterlimit`, `line-pattern-dasharray`.| default-meaning: The pattern will be warped along a linear geometry.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.file',  ?)", -1, &stmt, NULL);
	buffer = "<div>An image file to be repeated and warped along a line. Accepted formats: svg, jpg, png, tiff, and webp.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.clip',  ?)", -1, &stmt, NULL);
	buffer = "<div>Turning on clipping can help performance in the case that the boundaries "
		"\nof the geometry extent outside of tile extents. But clipping can result "
		"\nin undesirable rendering artifacts in rare cases.| default-meaning: The geometry will not be clipped to map bounds before rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>Apply an opacity level to the image used for the pattern.| default-meaning: The image is rendered without modifications.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.simplify',  ?)", -1, &stmt, NULL);
	buffer = "<div>geometries are simplified by the given tolerance.| default-meaning: geometry will not be simplified.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.simplify-algorithm',  ?)", -1, &stmt, NULL);
	buffer = "<div>geometries are simplified by the given algorithm.| default-meaning: The geometry will be simplified using the radial distance algorithm.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.smooth',  ?)", -1, &stmt, NULL);
	buffer = "<div>Smooths out geometry angles. 0 is no smoothing, 1 is fully smoothed. "
		"\nValues greater than 1 will produce wild, looping geometries.| default-meaning: No smoothing.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.offset',  ?)", -1, &stmt, NULL);
	buffer = "<div>Offsets a line a number of pixels parallel to its actual path. Positive values move the line left, "
		"\nnegative values move it right (relative to the directionality of the line).| default-meaning: The line will not be offset.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.geometry-transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line geometry with specified function.| default-meaning: The geometry will not be transformed.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform line pattern instance with specified function.| default-meaning: No transformation.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should "
		"\nbehave relative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.alignment',  ?)", -1, &stmt, NULL);
	buffer = "<div>Specify whether to align pattern fills to the feature`s geometry (local) or to the map (global)."
		"| default-meaning: Patterns will be aligned to the map when being repeated. This is ideal for seamless patterns in tiled rendering.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-width',  ?)", -1, &stmt, NULL);
	buffer = "<div>The width of a line in pixels. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line will be rendered 1 pixel wide.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-linecap',  ?)", -1, &stmt, NULL);
	buffer = "<div>The display of line endings. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line endings will be rendered using a butt look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-linejoin',  ?)", -1, &stmt, NULL);
	buffer = "<div>The behavior of lines when joining. Used for rendering line pattern of type `repeat`."
		"| default-meaning: The line joins will be rendered using a miter look.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-miterlimit',  ?)", -1, &stmt, NULL);
	buffer = "<div>The limit on the ratio of the miter length to the stroke-width. "
		"\nUsed to automatically convert miter joins to bevel joins for "
		"\nsharp angles to avoid the miter extending beyond the thickness "
		"\nof the stroking path. Normally will not need to be set, but a "
		"\nlarger value can sometimes help avoid jaggy artifacts. Used for "
		"\nrendering line pattern of type `repeat`.| default-meaning: Will auto-convert miters to bevel line joins when theta is less than 29 degrees as per the SVG spec: `miterLength / stroke-width = 1 / sin ( theta / 2 )`.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('line-patternsymbolizer.stroke-dasharray',  ?)", -1, &stmt, NULL);
	buffer = "<div>A pair of length values [a,b], where (a) is the dash length and (b) is the "
		"\ngap length respectively. More than two values are supported for more complex "
		"\npatterns. Used for rendering line pattern of type `repeat`.| default-meaning: The line will be drawn without dashes.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The opacity of the raster symbolizer on top of other symbolizers.| default-meaning: Color is fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.filter-factor',  ?)", -1, &stmt, NULL);
	buffer = "<div>This is used by the Raster or Gdal datasources to pre-downscale "
		"\nimages using overviews. Higher numbers can sometimes cause much "
		"\nbetter scaled image output, at the cost of speed.| default-meaning: Allow the datasource to choose appropriate downscaling.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.scaling',  ?)", -1, &stmt, NULL);
	buffer = "<div>The scaling algorithm used to making different resolution versions of this "
		"\nraster layer. Bilinear is a good compromise between speed and accuracy, "
		"\nwhile lanczos gives the highest quality.| default-meaning: Nearest neighboor resampling will be used to scale the image to the target size of the map.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.mesh-size',  ?)", -1, &stmt, NULL);
	buffer = "<div>A reduced resolution mesh is used for raster reprojection, and the total "
		"\nimage size is divided by the mesh-size to determine the quality of that "
		"\nmesh. Values for mesh-size larger than the default will result in faster "
		"\nreprojection but might lead to distortion.| default-meaning: Reprojection mesh will be 1/16 of the resolution of the source image.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer should behave "
		"\nrelative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default-mode',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be either `discrete`, `linear` or `exact`. "
		"\nIf it is not specified then the default is `linear`.| default-meaning: A linear interpolation is used to generate colors between the two nearest stops.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.default-color',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be any color. Sets the color that is applied to "
		"\nall values outside of the range of the colorizer-stops. "
		"\nIf not supplied pixels will be fully transparent.| default-meaning: Pixels that are not colored by the colorizer stops will be transparent.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.epsilon',  ?)", -1, &stmt, NULL);
	buffer = "<div>This can be any positive floating point value and will be used as "
		"\na tolerance in floating point comparisions. The higher the value "
		"\nthe more likely a stop will match and color data.| default-meaning: Pixels must very closely match the stop filter otherwise they will not be colored.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('rastersymbolizer.stop',  ?)", -1, &stmt, NULL);
	buffer = "<div>Assigns raster data values to colors. Stops must be listed in ascending order, "
		"\nand contain at a minimum the value and the associated color. You can also "
		"\ninclude the color-mode as a third argument, like `stop(100,#fff,exact)`.| default-meaning: No colorization will happen without supplying stops.<div>";;
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a line symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.file',  ?)", -1, &stmt, NULL);
	buffer = "<div>Image file to represent a point. Accepted formats: svg, jpg, png, tiff, and webp."
		"| default-meaning: A 4x4 black square will be rendered.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.allow-overlap',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control whether overlapping points are shown or hidden.| default-meaning: Do not allow points to overlap with each other - overlapping markers will not be shown.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.ignore-placement',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control whether the placement of the feature will prevent the placement of other features."
		"| default-meaning: do not store the bbox of this geometry in the collision detector cache.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>A value from 0 to 1 to control the opacity of the point.| default-meaning: Fully opaque.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.placement',  ?)", -1, &stmt, NULL);
	buffer = "<div>Control how this point should be placed. Centroid calculates the geometric center of a polygon, "
		"\nwhich can be outside of it, while interior always places inside of a polygon."
		"| default-meaning: The centroid of the geometry will be used to place the point.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.transform',  ?)", -1, &stmt, NULL);
	buffer = "<div>Transform point instance with specified function. Ignores map scale factor.| default-meaning: No transformation.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('pointsysmbolizer.comp_op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this symbolizer "
		"\nshould behave relative to symbolizers atop or below it.| default-meaning: Add the current symbolizer on top of other symbolizer.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.default',  ?)", -1, &stmt, NULL);
	buffer = "<div>Allows omitting a dot symbolizer rule or emitting it with default values.| default-meaning: <div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.fill',  ?)", -1, &stmt, NULL);
	buffer = "<div>The color of the area of the dot.| default-meaning: The dot fill color is gray.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.opacity',  ?)", -1, &stmt, NULL);
	buffer = "<div>The overall opacity of the dot.| default-meaning: The opacity of the dot.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.width',  ?)", -1, &stmt, NULL);
	buffer = "<div>The width of the dot in pixels.| default-meaning: The marker width is 1 pixel.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.height',  ?)", -1, &stmt, NULL);
	buffer = "<div>The height of the dot in pixels.| default-meaning: The marker height is 1 pixels.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);

	rc = sqlite3_prepare_v2(db, "INSERT INTO TOOLTIP VALUES('dotsymbolizer.comp-op',  ?)", -1, &stmt, NULL);
	buffer = "<div>Composite operation. This defines how this layer should behave relative to layers atop or below it."
		"| default-meaning: Add the current layer on top of other layers.<div>";
	rc = sqlite3_bind_blob(stmt, 1, buffer.c_str(), buffer.size(), SQLITE_STATIC);
	sqlite3_step(stmt);



	if (rc != SQLITE_DONE)
		AfxMessageBox(CString(sqlite3_errmsg(db)));*/

	sqlite3_close(db);
	return 0;
}
void CCustomToolTipCtrl::ReadDatabaseTooltip()
{
	/// <summary>
	/// The function is used to read the database tooltip.
	/// </summary>
	sqlite3* DB;
	sqlite3_stmt* stmt;
	char* messageError;
	int exit = sqlite3_open("tooltip.db", &DB);
	if (exit == SQLITE_OK)
	{
		sqlite3_stmt* stmt;
		const char* sql = "SELECT * FROM TOOLTIP";
		std::vector<std::string> codes;
		std::vector<std::string> contents;
		if (sqlite3_prepare_v2(DB, sql, strlen(sql), &stmt, 0) == SQLITE_OK)
		{
			int result = 0;
			while (true)
			{
				result = sqlite3_step(stmt);
				if (result == SQLITE_ROW)
				{
					std::string code = std::string((const char*)sqlite3_column_text(stmt, 0));
					std::string s_data = std::string (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
					contents.push_back(s_data);
					codes.push_back(code);
				}
				else
				{
					break;
				}
			}
		}
	}
	
}

std::string CCustomToolTipCtrl::ReplaceString(std::string str, std::string toReplace, std::string replaceStr)
{
	/// <summary>
	/// The function is used to replace a substring in a string with a new substring
	/// </summary>
	/// <param name="str">The string</param>
	/// <param name="toReplace">the substring needs replacing</param>
	/// <param name="replaceStr">the new substring</param>
	/// <returns>The new string</returns>
	size_t pos = str.find(toReplace);
	std::string result = str;
	// Repeat till end is reached
	while (pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		result = result.replace(pos, toReplace.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = result.find(toReplace, pos + replaceStr.size());
	}
	return result;
}
